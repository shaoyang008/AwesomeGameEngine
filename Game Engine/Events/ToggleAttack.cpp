#include "ToggleAttack.h"



ToggleAttack::ToggleAttack(bool toggle): Event(EVENT_TYPE::TOGGLE_ATTACK), _toggle(toggle)
{
}


ToggleAttack::~ToggleAttack()
{
}
