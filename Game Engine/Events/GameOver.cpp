#include "GameOver.h"



GameOver::GameOver(): Event(EVENT_TYPE::GAME_OVER), _victory(false)
{
}

GameOver::GameOver(bool victory) : Event(EVENT_TYPE::GAME_OVER), _victory(victory)
{
}

GameOver::~GameOver()
{
}
