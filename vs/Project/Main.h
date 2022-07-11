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

	const enum ButtonState {
		PLAY,
		EXIT
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
		// Special Update
		void UpdatePhysics();

		void DestroyPreMenu();
		void DestroyMenu();
		void DestroyInGame();
		void DestroyPause();

		Sprite* CreatePlayer();
		Sprite* CreateLaser();
		Sprite* CreateEnemy();

		void Shoot();

		// Util
		float simpleLerp(float v0, float v1, float t);

	private:
// Control Variable
	// Game States
		GameState gameState = GameState::PREMENU;
		bool stateSwitchFlag = false;

		ButtonState btnState = ButtonState::PLAY;

	// Score
		float scoreTimer;
		int score = 0;

	// Character
		// Flags
		GameObjectState playerState;
		Orientation playerOrient;
		bool isMoving;
		bool isFalling;

		// Shooting
		float maxShootSpeed = 240;
		float shootCounter = 0;

		// Kinematics
		vec2 lastPlayerPos;
		vec2 playerPos;
		float playerRot;

		//Physics
		float acceleration = 0;
		float momentum = 0;

	// Enemy
		list<list<int>> spawnPointList;

	// Graphics
		// Background
		Texture* backgroundTextureLogo;
		Texture* backgroundTexturePlain;
		Sprite* backgroundLogo = NULL;
		Sprite* backgroundPlain = NULL;

		Texture* pauseOverlayTexture;
		Sprite* pauseOverlay = NULL;

		// Platform
		Texture* platformTexture;
		Texture* floorTexture;
		Sprite* floor = NULL;
		 
		// UI
		Texture* btnNormalTexture;
		Texture* btnActiveTexture;
		Sprite* btnPlayNormal = NULL;
		Sprite* btnPlayActive = NULL;
		Sprite* btnExitNormal = NULL;
		Sprite* btnExitActive = NULL;

		// Text
		Text* preMenuText = NULL;
		Text* playMenuText = NULL;
		Text* exitMenuText = NULL;
		Text* scoreText = NULL;
		Text* pauseText = NULL;
	 
		// Bounding Box Debug
		Texture* dot = NULL;

		Sprite* dotSprite1 = NULL;
		Sprite* dotSprite2 = NULL;
		Sprite* dotSprite3 = NULL;
		Sprite* dotSprite4 = NULL;

		Sprite* dotSprite5 = NULL;
		Sprite* dotSprite6 = NULL;
		Sprite* dotSprite7 = NULL;
		Sprite* dotSprite8 = NULL;

		BoundingBox* playerBB = NULL;
		BoundingBox* floorBB = NULL;

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