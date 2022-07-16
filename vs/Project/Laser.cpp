#include "Laser.h"

using namespace Engine;

Laser::Laser(Texture* texture, Shader* defaultShader, Quad* defaultQuad,
	vec2 spawnPoint, Orientation orient, float velocity)
{
	state = GameObjectState::ALIVE;
	this->laser = new Sprite(texture, defaultShader, defaultQuad);
	laser->SetNumXFrames(4);
	laser->SetNumYFrames(1);
	laser->SetAnimationDuration(60);
	laser->AddAnimation("pulse", 0, 3);
	laser->SetScale(1);
	laser->PlayAnim("pulse");
	laser->SetBoundingBoxSize(laser->GetScaleWidth(), laser->GetScaleHeight());

	if (orient == Orientation::RIGHT) {
		laser->SetPosition(spawnPoint.x + 70, spawnPoint.y + 21);
	}
	else if (orient == Orientation::LEFT) {
		laser->SetPosition(spawnPoint.x - 70, spawnPoint.y + 21);
		laser->SetFlipHorizontal(1);
	}

	this->orient = orient;
	this->velocity = velocity;
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

	vec2 pos = laser->GetPosition();

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

void Laser::SetState(GameObjectState state)
{
	this->state = state;
}

Sprite* Laser::GetSpriteComponent() {
	return laser;
}

Laser* Laser::GetLaserComponent() {
	return this;
}

GameObjectState Laser::GetLifecycleState()
{
	return state;
}

bool Laser::IsDead()
{
	return Engine::GameObjectState::DEAD == state;;
}