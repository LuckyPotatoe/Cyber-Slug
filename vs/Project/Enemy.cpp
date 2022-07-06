#include "Enemy.h"

using namespace Engine;

Enemy::Enemy(Sprite* sprite)
{
	this->enemy = sprite;
	state = CharacterState::GROUND;
}

Enemy::~Enemy()
{
	delete enemy;
}

void Enemy::SpawnPlayer(float x, float y) {
	enemy->SetPosition(x, y);
}

void Enemy::Shoot() {

}