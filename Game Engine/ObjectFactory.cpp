#include "ObjectFactory.h"



ObjectFactory::ObjectFactory()
{
}


ObjectFactory::~ObjectFactory()
{
}

GameObject * ObjectFactory::CreateObject(json data)
{
	GameObject * newObj = new GameObject;
	std::cout << data << std::endl;
	json components = data["Components"];
	std::cout << components << std::endl;
	for (json::iterator it = components.begin(); it != components.end(); ++it) {
		Component * component = 0;
		if (it.key() == "Transform") {
			std::cout << "Adding " << it.key() << std::endl;
			Transform * tComponent = new Transform;
			tComponent->Serialize(it.value());
			component = tComponent;
		}
		else if (it.key() == "Sprite") {
			std::cout << "Adding " << it.key() << std::endl;
			Sprite * sComponent = new Sprite;
			sComponent->Serialize(it.value());
			component = sComponent;
		}
		else if (it.key() == "Controller") {
			std::cout << "Adding " << it.key() << std::endl;
			Controller * cComponent = new Controller;
			cComponent->Serialize(it.value());
			component = cComponent;
		}
		else if (it.key() == "Patrol") {
			std::cout << "Adding " << it.key() << std::endl;
			Patrol * pComponent = new Patrol;
			pComponent->Serialize(it.value());
			component = pComponent;
		}
		if (component) { newObj->AddComponent(component); }
	}
	return newObj;
}