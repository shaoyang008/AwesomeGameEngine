#include "RenderManager.h"
#include "GameStateManager.h"

extern GameStateManager *pMgr;

RenderManager::RenderManager(): _window(0), _renderer(0), _shader(0), _viewer(0), _renderMode(0)
{

}


RenderManager::~RenderManager()
{
	SDL_GL_DeleteContext(_glcontext);
	SDL_DestroyRenderer(_renderer);
}

void RenderManager::Initialize(SDL_Window *window)
{
	_window = window;
	_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_GetWindowSize(_window, &_width, &_height);

	if (_renderer == nullptr) {
		std::cerr << "SDL2 Renderer couldn't be created. Error: "
			<< SDL_GetError()
			<< std::endl;
		exit(1);
	}

	// Create a OpenGL context on SDL2
	_glcontext = SDL_GL_CreateContext(window);

	// Load GL extensions using glad
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		std::cerr << "Failed to initialize the OpenGL context." << std::endl;
		exit(1);
	}

	// Loaded OpenGL successfully.
	std::cout << "OpenGL version loaded: " << GLVersion.major << "." << GLVersion.minor << std::endl;

	// Shader program
	_shader = new ShaderProgram;

	_shader->CompileShader("Shaders/lighting.vert", GL_VERTEX_SHADER);
	_shader->CompileShader("Shaders/lighting.frag", GL_FRAGMENT_SHADER);

	glBindAttribLocation(_shader->_programId, 0, "vertex");
	glBindAttribLocation(_shader->_programId, 1, "texcoord");
	glBindAttribLocation(_shader->_programId, 2, "normal");
	_shader->LinkShader();

	// 2D shader program
	_shader2d = new ShaderProgram;
	_shader2d->CompileShader("Shaders/sprite.vert", GL_VERTEX_SHADER);
	_shader2d->CompileShader("Shaders/sprite.frag", GL_FRAGMENT_SHADER);

	glBindAttribLocation(_shader2d->_programId, 0, "vertex");
	_shader2d->LinkShader();

	Init2D();

	glEnable(GL_DEPTH_TEST);

	// Wire frame mode
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void RenderManager::Draw()
{
	glViewport(0, 0, _width, _height);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(_shader->_programId);
	glDisable(GL_BLEND);

	// Pass environment light to shader
	GLuint loc;
	loc = glGetUniformLocation(_shader->_programId, "Light");
	glUniform3fv(loc, 1, &(_light->_light[0]));
	loc = glGetUniformLocation(_shader->_programId, "Ambient");
	glUniform3fv(loc, 1, &(_light->_ambient[0]));
	loc = glGetUniformLocation(_shader->_programId, "Angle");
	glUniform1f(loc, _light->_angle * PI / 180.0f);

	Matrix4 WorldProj, WorldView, WorldInverse;
	WorldProj = Perspective(_camera->_ry * _width / _height, _camera->_ry, _camera->_front, _camera->_back);
	WorldView = LookAt(_camera->_position + _camera->_targetPosition, _camera->_targetPosition, vec3(0, 1, 0));
	WorldView.Inverse(WorldInverse);

	loc = glGetUniformLocation(_shader->_programId, "lightPos");
	glUniform3fv(loc, 1, &(_light->_lightPos[0]));

	loc = glGetUniformLocation(_shader->_programId, "WorldProj");
	glUniformMatrix4fv(loc, 1, GL_TRUE, WorldProj.Pntr());
	loc = glGetUniformLocation(_shader->_programId, "WorldView");
	glUniformMatrix4fv(loc, 1, GL_TRUE, WorldView.Pntr());
	loc = glGetUniformLocation(_shader->_programId, "WorldInverse");
	glUniformMatrix4fv(loc, 1, GL_TRUE, WorldInverse.Pntr());

	loc = glGetUniformLocation(_shader->_programId, "renderMode");
	glUniform1i(loc, _renderMode);

	if (_renderMode == 0 || _renderMode == 2) {
		for (int i = 0; i < pMgr->_gameObjectManager->_objects.size(); ++i) {
			loc = glGetUniformLocation(_shader->_programId, "ortho");
			glUniform1i(loc, (pMgr->_gameObjectManager->_objects[i]->GetTag() == "GUI"));

			Model * m = dynamic_cast<Model*>(pMgr->_gameObjectManager->_objects[i]->GetComponent(COMPONENT_TYPE::MODEL));
			if (m) m->Draw(_shader);
		}
	}
	if (_renderMode == 1 || _renderMode == 2) {
		DrawDebug();
	}

	glUseProgram(0);


	// 2D drawing
	if (_renderMode == 0) {
		Draw2D();
	}

	// Swap buffers
	SDL_GL_SwapWindow(_window);
}

void RenderManager::Draw2D()
{
	// 2D drawing
	GLuint loc;
	glUseProgram(_shader2d->_programId);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Matrix4 WorldOrtho;
	WorldOrtho = Orthographic(_width, _height);
	loc = glGetUniformLocation(_shader2d->_programId, "WorldOrtho");
	glUniformMatrix4fv(loc, 1, GL_TRUE, WorldOrtho.Pntr());

	for (int i = 0; i < pMgr->_gameObjectManager->_objects.size(); ++i) {
		Sprite * sprite = dynamic_cast<Sprite*>(pMgr->_gameObjectManager->_objects[i]->GetComponent(COMPONENT_TYPE::SPRITE));
		if (sprite) {
			sprite->UseSprite(_shader2d);

			glBindVertexArray(this->quadVAO);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindVertexArray(0);

			sprite->Unuse();
		}
	}
	glUseProgram(0);
}

void RenderManager::DrawDebug()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (int i = 0; i < pMgr->_gameObjectManager->_objects.size(); ++i) {
		Collider * c = dynamic_cast<Collider*>(pMgr->_gameObjectManager->_objects[i]->GetComponent(COMPONENT_TYPE::COLLIDER));
		if (c) c->Draw(_shader);
	}
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void RenderManager::ResizeWindow()
{
	SDL_GetWindowSize(_window, &_width, &_height);
}

bool RenderManager::SetCamera(std::string viewer_tag)
{
	GameObject * new_viewer = pMgr->_gameObjectManager->_tagObjects.FindValueByKey(viewer_tag);
	if (!new_viewer) {
		std::cout << "Camera not set" << std::endl;
		return false;
	}
	_viewer = new_viewer;
	_camera = dynamic_cast<Camera*>(_viewer->GetComponent(COMPONENT_TYPE::CAMERA));
	_light = dynamic_cast<Light*>(_viewer->GetComponent(COMPONENT_TYPE::LIGHT));
	return true;
}

void RenderManager::SwitchMode()
{
	/*
	0: default mode, render only models
	1: debug mode, render only colliders
	2: debug mode, render both
	*/
	_renderMode = (_renderMode + 1) % 3;
	std::cout << "Current mode: " << _renderMode << std::endl;
}

void RenderManager::Init2D()
{
	// Configure VAO/VBO
	GLuint VBO;
	GLfloat vertices[] = {
		// Pos      // Tex
		0.0f, 100.0f, 0.0f, 1.0f,
		100.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 100.0f, 0.0f, 1.0f,
		100.0f, 100.0f, 1.0f, 1.0f,
		100.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &this->quadVAO);
	glBindVertexArray(this->quadVAO);

	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);;
}