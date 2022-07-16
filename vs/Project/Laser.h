#pragma once

#include "Consts.h"
#include "Sprite.h"

extern float animationFrameFac;
extern float characterSpeedFac;

namespace Engine {
	class Laser {
	public:
		Laser(Texture* texture, Shader* defaultShader, Quad* defaultQuad,
			vec2 spawnPoint, Orientation orient, float velocity);
		~Laser();
		void Update(float deltaTime);
		void Draw();

		void SetState(GameObjectState state);
		Sprite* GetSpriteComponent();
		Laser* GetLaserComponent();
		GameObjectState GetLifecycleState();
		bool IsDead();
	private:
		Sprite* laser = NULL;
		GameObjectState state;
		Orientation orient = Orientation::RIGHT;

		float velocity;
	};
}