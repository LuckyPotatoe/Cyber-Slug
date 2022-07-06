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
extern float spriteScaleFac;

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

		Sprite* CreateLaser();
		Sprite* CreateEnemy();
	private:
		GameState state = GameState::PREMENU;
		bool initFlag = false;

	// Graphics
		// UI
		Texture* logoTexture;
		Sprite* logo;

		Texture* menuTexture;
		Sprite* playButton;
		Sprite* exitButton;

		// Text
		Text* preMenuText;
		Text* playText;
		Text* exitText;
	 
		// Background
		Texture* backgroundTexture;
		Sprite* background;

		// Platform
		//Texture* floorTexture = new Texture("");
		//Sprite* floor = new Sprite(floorTexture, defaultSpriteShader, defaultQuad);

		// Character
		Texture* playerTexture;
		Sprite* player;

		// TODO: Put this in main?
		vec2 playerPos;
		float playerRot;

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