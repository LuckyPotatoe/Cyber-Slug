#pragma once

#include "Consts.h"
#include "Sprite.h"

extern float animationFrameFac;
extern float spriteScaleFac;

namespace Engine {
	class Enemy
	{
	public:
		Enemy(Sprite* sprite);
		~Enemy();
		void Update(float deltaTime);
		void Draw();

		// Util functions
		void SetSpawn(float x, float y);
		void SetState(GameObjectState state);
		vec2 GetPosition();
		float GetRot();
		float GetWidth();
		float GetHeight();
		GameObjectState GetState();
		bool IsDead();

		// Gameplay functions
		void Shoot();
	private:
		Sprite* enemy = NULL;
		GameObjectState state;
	};
}