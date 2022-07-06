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

		// Core functions
		void SpawnPlayer(float x, float y);
		void Shoot();
	private:
		Sprite* enemy = NULL;
		CharacterState state;
	};
}