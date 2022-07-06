#pragma once

#include "Consts.h"
#include "Sprite.h"

extern float animationFrameFac;
extern float characterSpeedFac;

namespace Engine {
	class Laser {
	public:
		Laser(Sprite* sprite);
		~Laser();
		void Update(float deltaTime);
		void Draw();

		void SetSpawn(float x, float y);
		float GetX();
		float GetY();
		float GetRot();
		float GetWidth();
		float GetHeight();
		GameObjectState GetState();
		bool IsDead();
	private:
		Sprite* laser = NULL;
		GameObjectState state;
	};
}