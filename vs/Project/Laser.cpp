#include "Laser.h"

using namespace Engine;

Laser::Laser(Sprite* sprite)
{
	this->laserPrefab = sprite;
	laserPrefab->SetNumXFrames(4);
	laserPrefab->SetNumYFrames(1);
	laserPrefab->SetAnimationDuration(60 * animationFrameFac);
	laserPrefab->AddAnimation("pulse", 0, 3);
	laserPrefab->SetScale(spriteScaleFac);
}

Laser::~Laser()
{
}

Laser* InstantiateLaser() {
	Laser* laser = new Laser(laserPrefab);

	return laser;
}

void Laser::LaserSpawn(float x, float y) {
	Laser* laser = InstantiateLaser();
}