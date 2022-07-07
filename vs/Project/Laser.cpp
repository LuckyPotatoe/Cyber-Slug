#include "Laser.h"

using namespace Engine;

Laser::Laser(Sprite* sprite, Orientation orient)
{
	state = GameObjectState::ALIVE;
	this->laser = sprite;
	this->orient = orient;
}

Laser::~Laser()
{
	delete laser;
}

void Laser::Update(float deltaTime)
{
	if (state == GameObjectState::DEAD) {
		return;
	}

	vec2 pos = GetPosition();
	float velocity = 50;

	if (orient == Orientation::RIGHT) {
		laser->SetPosition(pos.x + velocity, pos.y);
	}
	else if (orient == Orientation::LEFT) {
		laser->SetPosition(pos.x - velocity, pos.y);
	}

	laser->Update(deltaTime);
}

void Laser::Draw()
{
	// Self-destruct
	if (state == GameObjectState::ALIVE) {
		laser->Draw();
	}
	else {
		return;
	}
}

void Laser::SetSpawn(float x, float y) {
	laser->SetPosition(x, y);
}

void Engine::Laser::SetState(GameObjectState state)
{
	this->state = state;
}

float Laser::GetWidth()
{
	return laser->GetScaleWidth();
}

float Laser::GetHeight()
{
	return laser->GetScaleHeight();
}

GameObjectState Laser::GetState()
{
	return state;
}

bool Laser::IsDead()
{
	return Engine::GameObjectState::DEAD == state;;
}

vec2 Laser::GetPosition()
{
	return laser->GetPosition();
}

float Laser::GetRot()
{
	return laser->GetRotation();
}