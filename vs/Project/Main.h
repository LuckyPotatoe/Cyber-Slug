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

extern float animationFrameFac;

extern float characterSpeedFac;
extern float characterScaleFac;

namespace Engine {
	const enum GameState {
		PREMENU,
		MENU,
		GAME,
		PAUSE
	};

	class Main :
		public Engine::Game
	{
	public:
		Main(Setting* setting);
		~Main();
		virtual void Init();
		virtual void Update();
		virtual void Render();

		void InitPreMenu();
		void InitMenu();
		void InitInGame();
		void InitPause();
		
		void UpdatePreMenu();
		void UpdateMenu();
		void UpdateInGame();
		void UpdatePause();

		void DestroyPreMenu();
		void DestroyMenu();
		void DestroyInGame();
		void DestroyPause();

		Sprite* CreateLaser();
		Sprite* CreateEnemy();
	private:
	// States
		GameState state = GameState::PREMENU;
		bool stateSwitchFlag = false;

	// Control Variable
		float maxShootSpeed = 240;
		float shootCounter = 0;

		// TODO: Put this in main?
		vec2 playerPos;
		float playerRot;
		Orientation playerOrient;

	// Graphics
		// UI
		Texture* logoTexture;
		Sprite* logo = NULL;

		Texture* menuTexture;
		Sprite* playButton = NULL;
		Sprite* exitButton = NULL;

		// Text
		Text* preMenuText = NULL;
		Text* playText = NULL;
		Text* exitText = NULL;
	 
		// Background
		Texture* backgroundTexture;
		Sprite* background = NULL;

		// Platform
		//Texture* floorTexture = new Texture("");
		//Sprite* floor = new Sprite(floorTexture, defaultSpriteShader, defaultQuad);

		// Bounding Box
		Texture* dot = NULL;

		Sprite* dotSprite1 = NULL;
		Sprite* dotSprite2 = NULL;
		Sprite* dotSprite3 = NULL;
		Sprite* dotSprite4 = NULL;

		BoundingBox* playerBB = NULL;

		// Character
		Texture* playerTexture;
		Sprite* player = NULL;

		//Enemy
		Texture* enemyTexture;
		list<Sprite*> enemyList;

		//Laser
		Texture* laserTexture;
		list<Laser*> laserList;

	// Sound
		// Music
		Music* mainMusic;
		bool isMusicRunning = true;
		
		// SFX
		Sound* sfxShoot;
	};
}