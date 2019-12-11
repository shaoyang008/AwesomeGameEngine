#include "SlideShow.h"
#include "../Events/SlideControl.h"
#include "../Events/GameOver.h"


SlideShow::SlideShow(): Component(COMPONENT_TYPE::SLIDE_SHOW), _currentSlide(0), _size(0), _ownerSprite(0)
{
}


SlideShow::~SlideShow()
{
}

void SlideShow::Update()
{
}

void SlideShow::Serialize(json data)
{
	_size = data["Size"].get<int>();

	for (int i = _slides.size(); i < _size; ++i) {
		_slides.push_back(new Material);

		std::string path = "Resources/Images/" + data["Slides"][i].get<std::string>();
		std::cout << path << std::endl;
		_slides[i]->LoadMap(path);
	}
}

void SlideShow::Initialize()
{
	_ownerSprite = dynamic_cast<Sprite*>(_owner->GetComponent(COMPONENT_TYPE::SPRITE));
	if (!_ownerSprite) {
		_ownerSprite = new Sprite;
		_owner->AddComponent(_ownerSprite);
	}

	_ownerSprite->SetTexture(0);
	_ownerSprite->_posX = -300;
	_ownerSprite->_posY = -400;
	_ownerSprite->_scaleX = 6;
	_ownerSprite->_scaleY = 8;
}

void SlideShow::HandleEvent(Event * e)
{
	if (e->GetType() == EVENT_TYPE::SLIDE_CONTROL) {
		SlideControl * sc = dynamic_cast<SlideControl*>(e);
		switch (sc->_control) {
			case SlideControl::NEXT:
				++_currentSlide;
				break;
			case SlideControl::SHOW:
				if (_currentSlide < _size) {
					_ownerSprite->SetTexture(_slides[_currentSlide]);
				}
				break;
			case SlideControl::CLOSE:
				_ownerSprite->SetTexture(0);
				break;
			default:
				break;
		}
	}
	else if (e->GetType() == EVENT_TYPE::GAME_START) {
		_ownerSprite->SetTexture(_slides[0]);
		_currentSlide = 1;
	}
	else if (e->GetType() == EVENT_TYPE::GAME_OVER) {
		if (dynamic_cast<GameOver*>(e)->_victory) {
			_ownerSprite->SetTexture(_slides[_size - 1]);
		}
		else {
			_ownerSprite->SetTexture(_slides[_size - 2]);
		}
	}
}
