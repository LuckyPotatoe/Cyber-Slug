#include "Laser.h"

using namespace Engine;

Laser::Laser(Sprite* sprite)
{
	this->laser = sprite;
	state = GameObjectState::ALIVE;
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

	float xPos = GetX();
	float yPos = GetY();
	float velocity = 50;

	// TODO: Laser behaviour
	laser->SetPosition(xPos + velocity, yPos);
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

float Laser::GetX()
{
	return laser->GetPosition().x;
}

float Laser::GetY()
{
	return laser->GetPosition().y;
}

float Laser::GetRot()
{
	return laser->GetRotation();
}