#pragma once

#include "Consts.h"
#include "Sprite.h"

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
		Sprite* sprite = NULL;
	};
}