#include "HealthBar.h"
#include "../GameObject.h"
#include "../Events/GameOver.h"
#include "../GameStateManager.h"

extern GameStateManager * pMgr;

#define FALLING_SPEED 40

HealthBar::HealthBar() : Component(COMPONENT_TYPE::HEALTH_BAR), _health(0), _posX(-800), _posY(-600)
{
}


HealthBar::~HealthBar()
{
}

void HealthBar::Update()
{
	if (_health == 0) {
		Transform * transform = dynamic_cast<Transform*>(_owner->GetComponent(COMPONENT_TYPE::TRANSFORM));
		if (transform->_rotateX < 80) {
			transform->_rotateX += FALLING_SPEED * pMgr->_framerateManager->_frameTime / 1000.0f;;
		}
		else {
			transform->_rotateX = 80;
			--_health;
		}
	}
}

void HealthBar::Initialize()
{
	_hearts.clear();
	for (int i = 0; i < _health; ++i) {
		GameObject * heart = pMgr->_gameObjectManager->GetObject("image");
		_hearts.push_back(heart);
	}

	for (int i = 0; i < _hearts.size(); ++i) {
		Sprite * sprite = dynamic_cast<Sprite*>(_hearts[i]->GetComponent(COMPONENT_TYPE::SPRITE));
		Material * heart_img = new Material;
		heart_img->LoadMap("Resources/Images/heart.png");
		sprite->SetTexture(heart_img);

		sprite->_posX = _posX + (i % 20) * 50;
		sprite->_posY = _posY - (i / 20) * 50;

		sprite->_scaleX = 0.5;
		sprite->_scaleY = 0.5;
	}
}

void HealthBar::Serialize(json data)
{
	_health = data["Health"].get<int>();

	_posX = data["PositionX"].get<int>();
	_posY = data["PositionY"].get<int>();
}

void HealthBar::HandleEvent(Event * e)
{
	//TODO : receive hit event and minus health
	//       when health is 0, send game over event
	if (e->GetType() == EVENT_TYPE::PLAYER_HIT) {
		if (_health > 0) {
			--_health;
			_hearts[_health]->Deactivate();
			std::cout << _owner->GetTag() << " health left: " << _health << std::endl;
			if (_health == 0) {
				std::cout << "Player Died!!" << std::endl;
				Event * e_new = new GameOver;
				pMgr->_eventManager->Enque(e_new);
			}
		}
	}
	else if (e->GetType() == EVENT_TYPE::ENEMY_HIT) {
		if (_health > 0) {
			--_health;
			_hearts[_health]->Deactivate();
			std::cout << _owner->GetTag() << " health left: " << _health << std::endl;
			if (_health == 0) {
				std::cout << "Boss Died!!" << std::endl;
				Event * e_new = new GameOver(true);
				pMgr->_eventManager->Enque(e_new);
			}
		}
	}
}

