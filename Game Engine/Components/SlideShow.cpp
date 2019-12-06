#include "SlideShow.h"
#include "../Events/SlideControl.h"


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

	for (int i = 0; i < _size; ++i) {
		_slides.push_back(new Material);

		std::string path = "Resources/" + data["Slides"][i].get<std::string>();
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
	_ownerSprite->_posY = -300;
	_ownerSprite->_scaleX = 6;
	_ownerSprite->_scaleY = 6;
}

void SlideShow::HandleEvent(Event * e)
{
	if (e->GetType() == EVENT_TYPE::SLIDE_CONTROL) {
		SlideControl * sc = dynamic_cast<SlideControl*>(e);
		switch (sc->_control) {
			case SlideControl::NEXT:
				++_currentSlide;
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
}
