#include "Enemy.h"

using namespace Engine;

Enemy::Enemy(Sprite* sprite)
{
	this->enemy = sprite;
	state = GameObjectState::ALIVE;
}

Enemy::~Enemy()
{
	delete enemy;
}

void Enemy::Update(float deltaTime)
{
	if (state == GameObjectState::DEAD) {
		return;
	}

	vec2 pos = GetPosition();
	float velocity = 50;

	//TODO: Enemy behaviour

	enemy->Update(deltaTime);
}

void Enemy::Draw()
{
	if (state == GameObjectState::ALIVE) {
		enemy->Draw();
	}
	else {
		return;
	}
}

void Enemy::Shoot() {

}

void Enemy::SetSpawn(float x, float y) 
{
	enemy->SetPosition(x, y);
}

void Enemy::SetState(GameObjectState state)
{
	this->state = state;
}

float Enemy::GetWidth()
{
	return enemy->GetScaleWidth();
}

float Enemy::GetHeight()
{
	return enemy->GetScaleHeight();
}

GameObjectState Enemy::GetState()
{
	return state;
}

bool Enemy::IsDead()
{
	return state == GameObjectState::DEAD;
}

vec2 Enemy::GetPosition()
{
	return enemy->GetPosition();
}

float Enemy::GetRot()
{
	return enemy->GetRotation();
}