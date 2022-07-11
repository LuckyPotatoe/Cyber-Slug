#pragma once

namespace Engine {
	const enum class GameObjectState {
		ALIVE,
		DEAD
	};

	const enum Orientation {
		RIGHT,
		LEFT
	};

	const float gravity = 9.81f;

	const float animationFrameFac = 1.8f;

	const float characterScaleFac = 3.0f;
	const float characterSpeedFac = 3.3f;
}