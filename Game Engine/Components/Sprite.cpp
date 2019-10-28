#include "Sprite.h"
#include "../GameStateManager.h"

extern GameStateManager *pMgr;

Sprite::Sprite(): Component(COMPONENT_TYPE::SPRITE), pSurface(NULL)
{
}


Sprite::~Sprite()
{
}

void Sprite::Update() {

}

void Sprite::Serialize(std::string data)
{
	std::string path = "Resources/" + data;
	if (!pMgr->pRM->RegisterSurface(path)) {
		printf("Could not load resource: %s\nReason: %s", path, SDL_GetError());
		return;
	}
	pSurface = pMgr->pRM->GetSurfaceByPath(path);
}
