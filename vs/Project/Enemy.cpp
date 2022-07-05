#include "Enemy.h"

using namespace Engine;

Enemy::Enemy(Sprite* sprite)
{
	this->sprite = sprite;
	sprite->SetNumXFrames(6);
	sprite->SetNumYFrames(6);
	sprite->SetAnimationDuration(60 * animationFrameFac);
	sprite->AddAnimation("idle", 0, 3);
	sprite->AddAnimation("idle_aim", 6, 9);
	sprite->AddAnimation("run", 12, 17);
	sprite->AddAnimation("run_aim", 18, 23);
	sprite->AddAnimation("jump", 24, 27);
	sprite->AddAnimation("jump_aim", 30, 33);
}

Enemy::~Enemy()
{
	delete sprite;
}

void Enemy::SpawnPlayer(float x, float y) {
	sprite->SetPosition(x, y);
}

void Enemy::Shoot() {

}