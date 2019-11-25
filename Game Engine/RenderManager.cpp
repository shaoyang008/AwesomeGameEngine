#include "RenderManager.h"
#include "GameStateManager.h"
#include "Components/Model.h"

extern GameStateManager *pMgr;

RenderManager::RenderManager(): _window(0), _renderer(0), _shader(0), _viewer(0), _renderMode(0)
{
	_lightPos[0] = 0.0;
	_lightPos[1] = 0.0;
	_lightPos[2] = 20.0;
	_light[0] = 3.0;
	_light[1] = 3.0;
	_light[2] = 3.0;
	_ambient[0] = 0.2;
	_ambient[1] = 0.2;
	_ambient[2] = 0.2;
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

	glEnable(GL_DEPTH_TEST);

	// Wire frame mode
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	Collider::InitializeUnitBox();
}

void RenderManager::Draw()
{
	glViewport(0, 0, _width, _height);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(_shader->_programId);

	// Pass environment light to shader
	GLuint loc;
	loc = glGetUniformLocation(_shader->_programId, "Light");
	glUniform3fv(loc, 1, &(_light[0]));
	loc = glGetUniformLocation(_shader->_programId, "Ambient");
	glUniform3fv(loc, 1, &(_ambient[0]));

	Camera * camera = dynamic_cast<Camera*>(_viewer->GetComponent(COMPONENT_TYPE::CAMERA));
	Matrix4 WorldProj, WorldView, WorldInverse;
	WorldProj = Perspective(camera->_ry * _width / _height, camera->_ry, camera->_front, camera->_back);
	WorldView = LookAt(camera->_position + camera->_targetPosition, camera->_targetPosition, vec3(0, 1, 0));
	WorldView.Inverse(WorldInverse);

	loc = glGetUniformLocation(_shader->_programId, "lightPos");
	glUniform3fv(loc, 1, &(_lightPos[0]));

	loc = glGetUniformLocation(_shader->_programId, "WorldProj");
	glUniformMatrix4fv(loc, 1, GL_TRUE, WorldProj.Pntr());
	loc = glGetUniformLocation(_shader->_programId, "WorldView");
	glUniformMatrix4fv(loc, 1, GL_TRUE, WorldView.Pntr());
	loc = glGetUniformLocation(_shader->_programId, "WorldInverse");
	glUniformMatrix4fv(loc, 1, GL_TRUE, WorldInverse.Pntr());

	if (_renderMode == 0 || _renderMode == 2) {
		for (int i = 0; i < pMgr->_gameObjectManager->_objects.size(); ++i) {
			Model * m = dynamic_cast<Model*>(pMgr->_gameObjectManager->_objects[i]->GetComponent(COMPONENT_TYPE::MODEL));
			if (m) m->Draw(_shader);
		}
	}
	if (_renderMode == 1 || _renderMode == 2) {
		for (int i = 0; i < pMgr->_gameObjectManager->_objects.size(); ++i) {
			Collider * c = dynamic_cast<Collider*>(pMgr->_gameObjectManager->_objects[i]->GetComponent(COMPONENT_TYPE::COLLIDER));
			if (c) c->Draw(_shader);
		}
	}

	glUseProgram(0);

	// Swap buffers
	SDL_GL_SwapWindow(_window);
}

bool RenderManager::SetCamera(std::string camera_tag)
{
	GameObject * new_camera = pMgr->_gameObjectManager->_tagObjects.FindValueByKey(camera_tag);
	if (!new_camera) {
		std::cout << "Camera not set" << std::endl;
		return false;
	}
	_viewer = new_camera;
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
