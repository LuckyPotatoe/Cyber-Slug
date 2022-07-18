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

extern float maxYVel;

extern float animationFrameFac;

extern float characterSpeedFac;
extern float characterScaleFac;

namespace Engine {
	const enum GameState {
		PREMENU,
		MENU,
		GAME,
		PAUSE,
		GAMEOVER
	};

	const enum AnimationState {
		IDLE,
		IDLE_AIM,
		RUN,
		RUN_AIM,
		JUMP,
		JUMP_AIM
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
		// InitPause() functions moved to Init(), it's not a lot, might as well.
		// InitGameover() functions moved to Init(), it's not a lot, might as well.
		// Special Init
		void InitPhysics();

		void UpdatePreMenu();
		void UpdateMenu();
		void UpdateInGame();
		void UpdatePause();
		void UpdateGameover();
		// Special Update
		void UpdatePhysics();

		void DestroyPreMenu();
		void DestroyMenu();
		void DestroyInGame();
		// DestroyPause() does not exist to save I/O calls
		// DestroyGameover() does not exist to save I/O calls

		Sprite* CreatePlayer();

		void PlayerShoot();
		void PlayerJump();

		// Util
		float simpleLerp(float v0, float v1, float t);

	private:
// Control Variable
	// Game States
		GameState gameState = GameState::PREMENU;
		bool stateSwitchFlag = false;
		bool isPhysicsInit = false;

		ButtonState btnState = ButtonState::PLAY;

	// Score
		float scoreTimer;
		int score = 0;

	// Character
		// Flags
		GameObjectState playerState;
		Orientation playerOrient;
		AnimationState animState = AnimationState::IDLE;
		bool isFalling;

		// Animation
		float idleAimWait = 0;
		float runWait = 0;
		float runAimWait = 0;
		bool isKeyPressedOnce = false;

		float runAimWaitMax = 60 * 9;
		bool isRunAim = false;
		
		// Shooting
		float playerMaxShootSpeed = 60 * 7;
		float playerShootCounter = 0;
		float enemyMaxShootSpeed = 60 * 14;

		// Kinematics
		float gravity;

		vec2 lastPlayerPos;
		float xMov, yMov;
		vec2 playerPos;

		float yVelocity;


	// Enemy
		vector<vec2> spawnerVector;

		// Spawner
		int TTS; // Time to spawn

		int enemyPool; // Maximum number of enemy allowed, will be incrementally added as the score gets higher.
		int spawnedEnemy; // Number of enemy spawned.
		int enemyAlive;
		int enemyDead;

	// Graphics
		// Background
		Texture* backgroundTextureLogo;
		Texture* backgroundTexturePlain;
		Sprite* backgroundLogo = NULL;
		Sprite* backgroundPlain = NULL;

		Texture* pauseOverlayTexture;
		Sprite* pauseOverlay = NULL;

		// Platform
		list<Sprite*> platformList;
		Texture* platformTexture;
		Texture* floorTexture;
		Sprite* floor = NULL;
		Sprite* platform1 = NULL;
		Sprite* platform2 = NULL;
		Sprite* platform3 = NULL;
		 
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
		Text* gameoverText = NULL;
		Text* gameoverText2 = NULL;
	 
		// Bounding Box Debug
		Texture* dot = NULL;

		Sprite* playerBBMarker1 = NULL;
		Sprite* playerBBMarker2 = NULL;
		Sprite* playerBBMarker3 = NULL;
		Sprite* playerBBMarker4 = NULL;

		Sprite* floorBBMarker1 = NULL;
		Sprite* floorBBMarker2 = NULL;
		Sprite* floorBBMarker3 = NULL;
		Sprite* floorBBMarker4 = NULL;
		
		Sprite* plt1BBMarker1 = NULL;
		Sprite* plt1BBMarker2 = NULL;
		Sprite* plt1BBMarker3 = NULL;
		Sprite* plt1BBMarker4 = NULL;
		
		Sprite* plt2BBMarker1 = NULL;
		Sprite* plt2BBMarker2 = NULL;
		Sprite* plt2BBMarker3 = NULL;
		Sprite* plt2BBMarker4 = NULL;
		
		Sprite* plt3BBMarker1 = NULL;
		Sprite* plt3BBMarker2 = NULL;
		Sprite* plt3BBMarker3 = NULL;
		Sprite* plt3BBMarker4 = NULL;

		BoundingBox* playerBB = NULL;
		BoundingBox* floorBB = NULL;
		BoundingBox* platform1BB = NULL;
		BoundingBox* platform2BB = NULL;
		BoundingBox* platform3BB = NULL;

		// Character
		Texture* playerTexture;
		Sprite* player = NULL;

		//Enemy
		Texture* enemyTexture;
		list<Enemy*> enemyList;

		//Laser
		Texture* playerLaserTexture;
		Texture* enemyLaserTexture;
		list<Laser*> playerLaserList;
		list<Laser*> enemyLaserList;

	// Sound
		// BGM
		Music* mainMusic;
		bool isMusicRunning = true;
		
		// SFX Flags
		bool playLandSFX;

		// SFX
		Sound* sfxPlayerShoot;
		Sound* sfxEnemyShoot;
		Sound* sfxJump;
		Sound* sfxLand;
		Sound* sfxHit;
	};
}