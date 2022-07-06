#pragma once

namespace Engine {
	const enum class CharacterState{
		GROUND,
		AIR,
		DEAD
	};

	const enum class GameObjectState {
		ALIVE,
		DEAD
	};

	const float gravity = 9.81f;

	const float animationFrameFac = 1.8f;
	const float spriteScaleFac = 3.0f;
	const float characterSpeedFac = 3.3f;
}