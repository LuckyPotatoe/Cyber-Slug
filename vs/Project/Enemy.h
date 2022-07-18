#pragma once

#include "Sprite.h"
#include "Sound.h"

#include "Consts.h"

extern float maxYVel;
extern float animationFrameFac;
extern float spriteScaleFac;
extern float characterSpeedFac;

using namespace std;

#include <list>

namespace Engine {
	const enum EnemyState {
		WAITING,
		PATROL,
		CHASE
	};

	class Enemy
	{
	public:
		Enemy(Texture* texture, Shader* defaultShader, Quad* defaultQuad, vec2 spawnPoint, Orientation orient);
		~Enemy();
		void Update(float deltaTime, list<Sprite*> &platformList, Sound* sfxLand);
		void Draw();

		void InitPhysics();
		void UpdatePhysics(float deltaTime, list<Sprite*> platformList, Sound* sfxLand);

		// Behaviour functions
		void Waiting();
		void Patrol();

		// Util functions
		GameObjectState GetLifecycleState();
		void SetLifecycleState(GameObjectState state);

		EnemyState GetBehaviourState();
		void SetBehaviourState(EnemyState state);

		
		float GetShootCounter();
		void SetShootCounter(float amount);
		
		float GetShootMood();
		void SetShootMood(float amount);
		
		float GetYVelocity();
		void SetYVelocity(float amount);

		bool GetIsFalling();
		void SetIsFalling(bool factor);

		Sprite* GetSpriteComponent();
		Orientation GetOrient();
		bool GetIsDead();
		vec2 GetPos();
		vec2 GetLastPos();
	private:
		bool isPhysicsInit = false;

		Sprite* enemy = NULL;
		Orientation orient;
		vec2 lastPos;
		vec2 pos;

		// Kinematics
		float xMov, yMov;
		float yVelocity;
		float gravity;
		bool isFalling;

		// AI
		EnemyState behaviourState;
		GameObjectState lifecycleState;
		float behaviourFactor;
		float patrolMood;
		float behaviourCounter;

		float shootMood;
		float shootCounter = 0;

		bool playLandSFX;
	};
}