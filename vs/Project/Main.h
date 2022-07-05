#pragma once

// Engine
#include "Game.h"
#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"
#include "Music.h"
#include "Sound.h"
#include "Text.h"

// Main
#include "Consts.h"
#include "Enemy.h"
#include "Laser.h"

namespace Engine {
	class Main :
		public Engine::Game
	{
	public:
		Main(Setting* setting);
		~Main();
		void BulletSpawn();
		virtual void Init();
		virtual void Update();
		virtual void Render();
	private:
	// Graphics
		// Background
		Texture* backgroundTexture;
		Sprite* background;

		// Platform
		Texture* floorTexture;
		Sprite* floor;

		// Character
		Texture* playerTexture;
		Sprite* player;

		vec2 playerPos;
		float playerRot;

		//Bullets
		Texture* laserTexture = new Texture("bullet_trail.png");
		Sprite* laserPrefab = new Sprite(laserTexture, defaultSpriteShader, defaultQuad);
		
		list<Sprite*> laserList;

		// Text
		Text* mainText;

	// Sound
		// Music
		Music* mainMusic;
		bool isMusicRunning = true;
		
		// SFX
		Sound* sfxShoot;
	};
}