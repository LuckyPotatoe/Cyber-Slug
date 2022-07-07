#pragma once

#include "Consts.h"
#include "Sprite.h"

extern float animationFrameFac;
extern float characterSpeedFac;

namespace Engine {
	class Laser {
	public:
		Laser(Sprite* sprite, Orientation orient);
		~Laser();
		void Update(float deltaTime);
		void Draw();

		void SetSpawn(float x, float y);
		void SetState(GameObjectState state);
		vec2 GetPosition();
		float GetRot();
		float GetWidth();
		float GetHeight();
		GameObjectState GetState();
		bool IsDead();
	private:
		Sprite* laser = NULL;
		GameObjectState state;
		Orientation orient = Orientation::RIGHT;
	};
}