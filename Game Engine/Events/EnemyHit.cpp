#include "EnemyHit.h"



EnemyHit::EnemyHit(): Event(EVENT_TYPE::ENEMY_HIT), _specialAtk(false)
{
}

EnemyHit::EnemyHit(bool special) : Event(EVENT_TYPE::ENEMY_HIT), _specialAtk(special)
{
}


EnemyHit::~EnemyHit()
{
}
