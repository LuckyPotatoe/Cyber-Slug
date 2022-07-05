#pragma once

#include "Consts.h"
#include "Sprite.h"

namespace Engine {
	class Laser {
	public:
		Laser(Sprite* sprite);
		~Laser();
		
		void LaserSpawn(float x, float y);
	protected:
		Laser* InstantiateLaser();
	private:
		Sprite* laserPrefab = NULL;
	};
}