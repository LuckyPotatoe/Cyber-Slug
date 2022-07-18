#include "Enemy.h"

using namespace Engine;

Enemy::Enemy(Texture* texture, Shader* defaultShader, Quad* defaultQuad,
	vec2 spawnPoint, Orientation orient)
{
	lifecycleState = GameObjectState::ALIVE;
	this->orient = orient;

	this->enemy = new Sprite(texture, defaultShader, defaultQuad);
	enemy->SetNumXFrames(6);
	enemy->SetNumYFrames(6);
	enemy->SetAnimationDuration(60 * animationFrameFac);
	enemy->AddAnimation("idle", 0, 3);
	enemy->AddAnimation("idle_aim", 6, 9);
	enemy->AddAnimation("run", 12, 17);
	enemy->AddAnimation("run_aim", 18, 23);
	enemy->AddAnimation("jump", 24, 27);
	enemy->AddAnimation("jump_aim", 30, 33);
	enemy->SetScale(characterScaleFac);
	enemy->SetBoundingBoxSize(enemy->GetScaleWidth() / 1.7, enemy->GetScaleHeight());

	enemy->SetPosition(spawnPoint.x, spawnPoint.y);

	if (orient == Orientation::RIGHT) {
		// pass
	}
	else if (orient == Orientation::LEFT) {
		enemy->SetFlipHorizontal(1);
	}
}

Enemy::~Enemy()
{
	delete enemy;
}

void Enemy::Update(float deltaTime, list<Sprite*> &platformList, Sound* sfxLand)
{
	if (lifecycleState == GameObjectState::DEAD) {
		return;
	}

	if (isPhysicsInit) {
		lastPos = pos;
	}

	pos = enemy->GetPosition();
	xMov = pos.x, yMov = pos.y;

	if (isPhysicsInit == false) {
		InitPhysics();
	}

	//TODO: Enemy behaviour
	if (behaviourCounter > 600) {
		behaviourFactor = rand() % 2;

		if (behaviourFactor == 0) {
			Waiting();
		}
		else if (behaviourFactor == 1) {
			Patrol();
		}
		behaviourCounter = 0;
	}
	else {
		behaviourCounter += deltaTime;
	}

	UpdatePhysics(deltaTime, platformList, sfxLand);

	enemy->Update(deltaTime);
}

void Enemy::Draw()
{
	if (lifecycleState == GameObjectState::ALIVE) {
		enemy->Draw();
	}
	else {
		return;
	}
}

void Enemy::InitPhysics() {
	lastPos = vec2(pos.x, pos.y + 1);
	gravity = 0.16f;

	isFalling = true;

	playLandSFX = true;

	isPhysicsInit = true;
}

void Enemy::UpdatePhysics(float deltaTime, list<Sprite*> platformList, Sound* sfxLand) {
	// Hard world border
	if (pos.x < 0) {
		xMov = pos.x + 1;
	}
	else if (pos.x > 1024 - 34) {
		xMov = pos.x - 1;
	}
	
	// State update
	if (isFalling) {
		if (yVelocity > maxYVel) {
			yVelocity -= gravity;
		}
		else {
			yVelocity = maxYVel;
		}
	}
	else if (isFalling == false) {
		yVelocity = 0;
		yMov = pos.y;
	}

	yMov += yVelocity * deltaTime;
	enemy->SetPosition(xMov, yMov);

	if (isFalling) {
		for (Sprite* platform : platformList) {
			// Character col checks.
			if (platform->GetBoundingBox()->CollideWith(enemy->GetBoundingBox()))
			{
				// Anti-slide and floor correction
				enemy->SetPosition(pos.x, pos.y);

				// and set jump to false and yVelovity to 0
				yVelocity = 0;
				isFalling = false;
				if (playLandSFX) {
					sfxLand->Play(false);
					playLandSFX = false;
				}
				break;
			}
		}
	}
	// TODO: Figure out how to play sfxLand properly.
	// When enemy walk off from platform, update the isFalling status.
	else {
		for (Sprite* platform : platformList) {
			if (lastPos.x != pos.x) {
				if (platform->GetBoundingBox()->CollideWith(enemy->GetBoundingBox()) == false)
				{
					isFalling = true;
					break;
				}
			}
			else {
				break;
			}
		}
	}

	if (lastPos.y > pos.y) {
		isFalling = true;
	}
}

void Enemy::Waiting()
{
	enemy->PlayAnim("idle");
}

void Enemy::Patrol()
{
	patrolMood = rand() % 2;

	if (patrolMood == 0) {
		orient = Orientation::RIGHT;
		xMov += 20;
		enemy->PlayAnim("run");
		enemy->SetFlipHorizontal(0);
		enemy->SetPosition(xMov, yMov);
	}
	else if (patrolMood == 1) {
		orient = Orientation::LEFT;
		xMov -= 20;
		enemy->PlayAnim("run");
		enemy->SetFlipHorizontal(1);
		enemy->SetPosition(xMov, yMov);
	}
}

GameObjectState Enemy::GetLifecycleState()
{
	return lifecycleState;
}

void Enemy::SetLifecycleState(GameObjectState state)
{
	this->lifecycleState = state;
}

EnemyState Enemy::GetBehaviourState()
{
	return behaviourState;
}

void Enemy::SetBehaviourState(EnemyState state)
{
	this->behaviourState = state;
}

float Engine::Enemy::GetShootCounter()
{
	return shootCounter;
}

void Enemy::SetShootCounter(float amount) {
	this->shootCounter = amount;
}

float Enemy::GetShootMood() {
	return shootMood;
}

void Enemy::SetShootMood(float amount) {
	this->shootMood = amount;
}

float Enemy::GetYVelocity() {
	return yVelocity;
}

void Enemy::SetYVelocity(float amount) {
	yVelocity = amount;
}

Sprite* Enemy::GetSpriteComponent() {
	return enemy;
}

Orientation Engine::Enemy::GetOrient()
{
	return orient;
}

bool Enemy::GetIsDead()
{
	return lifecycleState == GameObjectState::DEAD;
}

bool Enemy::GetIsFalling() {
	return isFalling;
}

void Enemy::SetIsFalling(bool factor) {
	isFalling = factor;
}

vec2 Enemy::GetPos() {
	return pos;
}

vec2 Enemy::GetLastPos() {
	return lastPos;
}