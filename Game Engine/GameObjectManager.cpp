#include "GameObjectManager.h"



GameObjectManager::GameObjectManager(): _tagObjects(BinaryTree<std::string, GameObject*>()), _factory(new ObjectFactory)
{
}


GameObjectManager::~GameObjectManager()
{
	// for(delete all game objects
	for (int i = 0; i < _objects.size(); ++i) {
		delete _objects[i];
	}
}

void GameObjectManager::Update()
{
	for (int i = 0; i < _objects.size(); ++i) {
		_objects[i]->Update();
	}
}

void GameObjectManager::LoadObject(std::string model)
{
	std::string model_path = "./Models/" + model + ".txt";
	std::ifstream model_file;
	model_file.open(model_path);

	json model_data;
	model_file >> model_data;

	GameObject * pObject = _factory->CreateObject(model_data);
	_objects.push_back(pObject);
	
	// TODO: clean method
	if (model_data.find("Tag") != model_data.end()) {	_tagObjects.InsertNode(model_data["Tag"], pObject); }

	model_file.close();
}

GameObject * GameObjectManager::CreateObject(OBJECT_TYPE type, std::string tag)
{
	GameObject *pObject = new GameObject(tag);
	Sprite *pSprite = new Sprite;
	pObject->AddComponent(pSprite);

	if (type == OBJECT_TYPE::IMAGE) {
		Transform *pTransform = new Transform;
		pObject->AddComponent(pTransform);
	}
	else if (type == OBJECT_TYPE::PLAYER) {
		Transform *pTransform = new Transform;
		pObject->AddComponent(pTransform);

		Controller *pController = new Controller;
		pObject->AddComponent(pController);
	}
	else if (type == OBJECT_TYPE::ENEMY_1) {
		Transform *pTransform = new Transform;
		pObject->AddComponent(pTransform);
	}

	_objects.push_back(pObject);
	_tagObjects.InsertNode(tag, pObject);
	return _objects.back();
}
