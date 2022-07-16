#include "Main.h"

using namespace Engine;

Main::Main(Setting* setting) :Game(setting)
{

}

Main::~Main()
{

}

void Main::Init()
{
// Input Handling
	inputManager->AddInputMapping("right", SDLK_d);
	inputManager->AddInputMapping("left", SDLK_a);
	inputManager->AddInputMapping("up", SDLK_w);
	inputManager->AddInputMapping("down", SDLK_s);
	inputManager->AddInputMapping("space", SDLK_SPACE);
	inputManager->AddInputMapping("enter", SDLK_KP_ENTER);
	inputManager->AddInputMapping("escape", SDLK_ESCAPE);

	inputManager->AddInputMapping("mute", SDLK_m);
	inputManager->AddInputMapping("debug", SDLK_TAB);

// Pause
	pauseOverlayTexture = new Texture("pause_overlay.png");
	pauseOverlay = new Sprite(pauseOverlayTexture, defaultSpriteShader, defaultQuad);
	
	pauseText = new Text("Abaddon Bold.ttf", 30, defaultTextShader);
	pauseText->SetText("PAUSED");
	pauseText->SetPosition(setting->screenWidth / 2, setting->screenHeight / 2);

// Gameover
	gameoverText = new Text("Abaddon Bold.ttf", 30, defaultTextShader);
	gameoverText2 = new Text("Abaddon Bold.ttf", 24, defaultTextShader);
	gameoverText->SetText("Simulation over... you're dead.");
	gameoverText2->SetText("Press space to play again.");
	gameoverText->SetPosition(setting->screenWidth / 2, setting->screenHeight / 2);
	gameoverText2->SetPosition(setting->screenWidth / 2, (setting->screenHeight / 2) - 40);

	InitPreMenu();
}

void Main::Update()
{
// GameState Switch
	if (stateSwitchFlag) {
		if (gameState == GameState::MENU) {
			InitMenu();
			stateSwitchFlag = false;
		}
		else if (gameState == GameState::GAME) {
			InitInGame();
			stateSwitchFlag = false;
		}
	}

// State Update
	if (gameState == GameState::PREMENU) {
		UpdatePreMenu();
	}
	else if (gameState == GameState::MENU) {
		UpdateMenu();
	}
	else if (gameState == GameState::GAME) {
		UpdateInGame();
	}
	else if (gameState == GameState::PAUSE) {
		UpdatePause();
	}
	else if (gameState == GameState::GAMEOVER) {
		UpdateGameover();
	}
}

void Main::Render()
{
	if (gameState == GameState::PREMENU) {
		if (backgroundLogo != NULL || preMenuText != NULL) {
			backgroundLogo->Draw();
			preMenuText->Draw();
		}	
	}
	else if (gameState == GameState::MENU) {
		if (backgroundLogo != NULL) {
			backgroundLogo->Draw();
		}

		//Button
		if (btnState == ButtonState::PLAY && btnPlayActive != NULL && btnExitNormal != NULL)
		{
			btnPlayActive->Draw();
			btnExitNormal->Draw();
		}
		else if (btnState == ButtonState::EXIT && btnPlayNormal != NULL && btnExitActive != NULL)
		{
			btnPlayNormal->Draw();
			btnExitActive->Draw();
		}

		//Text
		if (playMenuText != NULL && exitMenuText != NULL) {
			playMenuText->Draw();
			exitMenuText->Draw();
		}
	}
	else if (gameState == GameState::GAME) {
		if (backgroundPlain != NULL) {
			backgroundPlain->Draw();
		}

		if (scoreText != NULL) {
			scoreText->Draw();
		}

		if (player != NULL) {
			player->Draw();
		}

		if (playerBBMarker1 != NULL) {
			playerBBMarker1->Draw();
			playerBBMarker2->Draw();
			playerBBMarker3->Draw();
			playerBBMarker4->Draw();

			floorBBMarker1->Draw();
			floorBBMarker2->Draw();
			floorBBMarker3->Draw();
			floorBBMarker4->Draw();

			plt1BBMarker1->Draw();
			plt1BBMarker2->Draw();
			plt1BBMarker3->Draw();
			plt1BBMarker4->Draw();

			plt2BBMarker1->Draw();
			plt2BBMarker2->Draw();
			plt2BBMarker3->Draw();
			plt2BBMarker4->Draw();

			plt3BBMarker1->Draw();
			plt3BBMarker2->Draw();
			plt3BBMarker3->Draw();
			plt3BBMarker4->Draw();
		}

		for (Enemy* enemy : enemyList) {
			if (enemy != NULL) {
				enemy->Draw();
			}
		}

		for (Laser* laser : playerLaserList) {
			if (laser != NULL) {
				laser->Draw();
			}
		}

		for (Laser* laser : enemyLaserList) {
			if (laser != NULL) {
				laser->Draw();
			}
		}
	}
	else if (gameState == GameState::PAUSE) {
		if (backgroundPlain != NULL) {
			backgroundPlain->Draw();
		}

		if (scoreText != NULL) {
			scoreText->Draw();
		}

		if (player != NULL) {
			player->Draw();
		}

		if (playerBBMarker1 != NULL) {
			playerBBMarker1->Draw();
			playerBBMarker2->Draw();
			playerBBMarker3->Draw();
			playerBBMarker4->Draw();

			floorBBMarker1->Draw();
			floorBBMarker2->Draw();
			floorBBMarker3->Draw();
			floorBBMarker4->Draw();
			
			plt1BBMarker1->Draw();
			plt1BBMarker2->Draw();
			plt1BBMarker3->Draw();
			plt1BBMarker4->Draw();
			
			plt2BBMarker1->Draw();
			plt2BBMarker2->Draw();
			plt2BBMarker3->Draw();
			plt2BBMarker4->Draw();
			
			plt3BBMarker1->Draw();
			plt3BBMarker2->Draw();
			plt3BBMarker3->Draw();
			plt3BBMarker4->Draw();
		}

		for (Enemy* enemy : enemyList) {
			if (enemy != NULL) {
				enemy->Draw();
			}
		}

		for (Laser* laser : playerLaserList) {
			if (laser != NULL) {
				laser->Draw();
			}
		}

		for (Laser* laser : enemyLaserList) {
			if (laser != NULL) {
				laser->Draw();
			}
		}

		if (pauseOverlay != NULL && pauseText != NULL) {
			pauseOverlay->Draw();
			pauseText->Draw();
		}
	}
	else if (gameState == GameState::GAMEOVER) {
		if (backgroundPlain != NULL) {
			backgroundPlain->Draw();
		}

		if (scoreText != NULL) {
			scoreText->Draw();
		}

		if (player != NULL) {
			player->Draw();
		}

		if (playerBBMarker1 != NULL) {
			playerBBMarker1->Draw();
			playerBBMarker2->Draw();
			playerBBMarker3->Draw();
			playerBBMarker4->Draw();

			floorBBMarker1->Draw();
			floorBBMarker2->Draw();
			floorBBMarker3->Draw();
			floorBBMarker4->Draw();

			plt1BBMarker1->Draw();
			plt1BBMarker2->Draw();
			plt1BBMarker3->Draw();
			plt1BBMarker4->Draw();

			plt2BBMarker1->Draw();
			plt2BBMarker2->Draw();
			plt2BBMarker3->Draw();
			plt2BBMarker4->Draw();

			plt3BBMarker1->Draw();
			plt3BBMarker2->Draw();
			plt3BBMarker3->Draw();
			plt3BBMarker4->Draw();
		}

		for (Enemy* enemy : enemyList) {
			if (enemy != NULL) {
				enemy->Draw();
			}
		}

		for (Laser* laser : playerLaserList) {
			if (laser != NULL) {
				laser->Draw();
			}
		}

		for (Laser* laser : enemyLaserList) {
			if (laser != NULL) {
				laser->Draw();
			}
		}

		if (pauseOverlay != NULL && gameoverText != NULL && gameoverText2 != NULL) {
			pauseOverlay->Draw();
			gameoverText->Draw();
			gameoverText2->Draw();
		}
	}
}

void Main::InitPreMenu()
{
	backgroundTextureLogo = new Texture("background_logo.png");
	backgroundLogo = new Sprite(backgroundTextureLogo, defaultSpriteShader, defaultQuad);

	preMenuText = new Text("Abaddon Bold.ttf", 30, defaultTextShader);
	preMenuText->SetColor(255, 255, 255);
	preMenuText->SetText("Press space key to continue...");

	preMenuText->SetPosition(100, 100);
	preMenuText->SetScale(1);
}

void Main::InitMenu()
{
	//Button Play
	btnNormalTexture = new Texture("button_normal.png");
	btnPlayNormal = new Sprite(btnNormalTexture, defaultSpriteShader, defaultQuad);
	btnPlayNormal->SetPosition(setting->screenWidth / 2 - 70, setting->screenHeight / 2 - 10);

	btnExitNormal = new Sprite(btnNormalTexture, defaultSpriteShader, defaultQuad);
	btnExitNormal->SetPosition(setting->screenWidth / 2 - 70, setting->screenHeight / 2 - 65);

	//Button Active
	btnActiveTexture = new Texture("button_active.png");
	btnPlayActive = new Sprite(btnActiveTexture, defaultSpriteShader, defaultQuad);
	btnPlayActive->SetPosition(setting->screenWidth / 2 - 70, setting->screenHeight / 2 - 10);

	btnExitActive = new Sprite(btnActiveTexture, defaultSpriteShader, defaultQuad);
	btnExitActive->SetPosition(setting->screenWidth / 2 - 70, setting->screenHeight / 2 - 65);

	//Button Text
	playMenuText = new Text("Abaddon Bold.ttf", 30, defaultTextShader);
	playMenuText->SetScale(1.0f);
	playMenuText->SetColor(255, 255, 255);
	playMenuText->SetText("PLAY");
	playMenuText->SetPosition(setting->screenWidth / 2 - 37, setting->screenHeight / 2 + 3);

	exitMenuText = new Text("Abaddon Bold.ttf", 30, defaultTextShader);
	exitMenuText->SetScale(1.0f);
	exitMenuText->SetColor(255, 255, 255);
	exitMenuText->SetText("EXIT");
	exitMenuText->SetPosition(setting->screenWidth / 2 - 37, setting->screenHeight / 2 - 53);

	//Button State
	if (btnState == ButtonState::PLAY)
	{
		playMenuText->SetColor(0, 255, 0);
	}

	// BGM
	mainMusic = new Music("music_main.wav");
	mainMusic->SetVolume(7);
	mainMusic->Play(true);
}

void Main::InitInGame()
{
	// UNDONE: Reset the down leftmost and rightmost to floor ouside the screen.
	// This is temporary since enemy can't walk yet. Mind the Y!
	spawnerVector = {
		// High center falldown
		{vec2((setting->screenWidth / 2) - 34, setting->screenHeight + 25)},
		// High quarter left
		{vec2((setting->screenWidth / 4), setting->screenHeight + 25)},
		// High quarter right
		{vec2((setting->screenWidth / 4) * 3 - 34, setting->screenHeight + 25)},
		// Down leftmost point
		{vec2(20, 100)},
		// down rightmost point
		{vec2((setting->screenWidth) - 100, 100)}
	};

	// Background
	// UNDONE Bring back texture
	backgroundTexturePlain = new Texture("background_plain.png");
	backgroundPlain = new Sprite(backgroundTexturePlain, defaultSpriteShader, defaultQuad);

	//Text
	scoreText = new Text("Abaddon Bold.ttf", 30, defaultTextShader);
	scoreText->SetText("Score: " + to_string(score));
	scoreText->SetPosition(50, setting->screenHeight - 50);

	// Stage
	dot = new Texture("dot.png");

	// TODO: Floor & Platform texture 
	floor = new Sprite(dot, defaultSpriteShader, defaultQuad);
	floor->SetBoundingBoxSize(setting->screenWidth * 2, 50);

	platform1 = new Sprite(dot, defaultSpriteShader, defaultQuad);
	platform1->SetPosition(setting->screenWidth / 3 - 134, setting->screenHeight / 4);
	platform1->SetBoundingBoxSize(200, 50);

	platform2 = new Sprite(dot, defaultSpriteShader, defaultQuad);
	platform2->SetPosition(setting->screenWidth / 2, setting->screenHeight / 2);
	platform2->SetBoundingBoxSize(200, 50);

	platform3 = new Sprite(dot, defaultSpriteShader, defaultQuad);
	platform3->SetPosition(setting->screenWidth - 200, setting->screenHeight / 4);
	platform3->SetBoundingBoxSize(200, 50);
	
	platformList.push_back(floor);
	platformList.push_back(platform1);
	platformList.push_back(platform2);
	platformList.push_back(platform3);

	// Graphic
	player = CreatePlayer();

	playerBBMarker1 = new Sprite(dot, defaultSpriteShader, defaultQuad);
	playerBBMarker2 = new Sprite(dot, defaultSpriteShader, defaultQuad);
	playerBBMarker3 = new Sprite(dot, defaultSpriteShader, defaultQuad);
	playerBBMarker4 = new Sprite(dot, defaultSpriteShader, defaultQuad);

	floorBBMarker1 = new Sprite(dot, defaultSpriteShader, defaultQuad);
	floorBBMarker2 = new Sprite(dot, defaultSpriteShader, defaultQuad);
	floorBBMarker3 = new Sprite(dot, defaultSpriteShader, defaultQuad);
	floorBBMarker4 = new Sprite(dot, defaultSpriteShader, defaultQuad);
	
	plt1BBMarker1 = new Sprite(dot, defaultSpriteShader, defaultQuad);
	plt1BBMarker2 = new Sprite(dot, defaultSpriteShader, defaultQuad);
	plt1BBMarker3 = new Sprite(dot, defaultSpriteShader, defaultQuad);
	plt1BBMarker4 = new Sprite(dot, defaultSpriteShader, defaultQuad);
	
	plt2BBMarker1 = new Sprite(dot, defaultSpriteShader, defaultQuad);
	plt2BBMarker2 = new Sprite(dot, defaultSpriteShader, defaultQuad);
	plt2BBMarker3 = new Sprite(dot, defaultSpriteShader, defaultQuad);
	plt2BBMarker4 = new Sprite(dot, defaultSpriteShader, defaultQuad);
	
	plt3BBMarker1 = new Sprite(dot, defaultSpriteShader, defaultQuad);
	plt3BBMarker2 = new Sprite(dot, defaultSpriteShader, defaultQuad);
	plt3BBMarker3 = new Sprite(dot, defaultSpriteShader, defaultQuad);
	plt3BBMarker4 = new Sprite(dot, defaultSpriteShader, defaultQuad);

	// Laser
	playerLaserTexture = new Texture("bullet_trail_player.png");
	enemyLaserTexture = new Texture("bullet_trail_enemy.png");

// Sound
	// SFX
	sfxPlayerShoot = new Sound("MiniShot2.wav");
	sfxEnemyShoot = new Sound("SingleShot2.wav");
	sfxJump = new Sound("StonesSlamToTheGround.wav");
	sfxLand = new Sound("HitTheGround.wav");
	sfxHit = new Sound("DirectAttack.wav");
	sfxPlayerShoot->SetVolume(8);
	sfxEnemyShoot->SetVolume(3);
	sfxJump->SetVolume(6);
	sfxLand->SetVolume(10);
	sfxHit->SetVolume(8);

	// Enemy
	enemyPool = 2;
	// TODO: Change texture to actual enemy texture
	enemyTexture = new Texture("character.png");
}

void Main::InitPhysics() {
	lastPlayerPos = vec2(playerPos.x, playerPos.y + 1);
	gravity = 0.16f;

	isFalling = true;
	playLandSFX = true;

	isPhysicsInit = true;
}

void Engine::Main::UpdatePreMenu()
{
	if (inputManager->IsKeyReleased("space")) {
		gameState = GameState::MENU;
		stateSwitchFlag = true;
		DestroyPreMenu();
	}
}

void Engine::Main::UpdateMenu()
{
	if (inputManager->IsKeyReleased("up"))
	{
		btnState = ButtonState::PLAY;
		playMenuText->SetColor(0, 255, 0);
		exitMenuText->SetColor(255, 255, 255);

	}
	else if (inputManager->IsKeyReleased("down"))
	{
		btnState = ButtonState::EXIT;
		exitMenuText->SetColor(255, 0, 0);
		playMenuText->SetColor(255, 255, 255);
	}

	//PLAY
	if (btnState == ButtonState::PLAY && (inputManager->IsKeyReleased("space") || inputManager->IsKeyReleased("enter")))
	{
		gameState = GameState::GAME;
		stateSwitchFlag = true;
		DestroyMenu();
	}

	//EXIT
	if (btnState == ButtonState::EXIT && (inputManager->IsKeyReleased("space") || inputManager->IsKeyReleased("enter")))
	{
		exit(0);
	}
}

void Engine::Main::UpdateInGame()
{
	scoreText->SetText("Score: " + to_string(score));

	// Score update per 3 frame-ish
	if (scoreTimer > 360) {
		score += 1;
		scoreTimer = 0;
	}
	else {
		scoreTimer += GetGameTime();
	}

	enemyPool = (scoreTimer / 20);

// Anim and GameObject update
	player->Update(GetGameTime());

	// Spawner
	if (enemyPool > 0) {
		if (TTS > 60 * 30) {
			int spawnerFac = rand() % 5;

			// High center
			if (spawnerFac == 0) {
				enemyList.push_back(new Enemy(enemyTexture, defaultSpriteShader, defaultQuad,
					spawnerVector.at(spawnerFac), Orientation::RIGHT));
			}
			// High quarter left
			else if (spawnerFac == 1) {
				enemyList.push_back(new Enemy(enemyTexture, defaultSpriteShader, defaultQuad,
					spawnerVector.at(spawnerFac), Orientation::RIGHT));
			}
			// High quarter right
			else if (spawnerFac == 2) {
				enemyList.push_back(new Enemy(enemyTexture, defaultSpriteShader, defaultQuad,
					spawnerVector.at(spawnerFac), Orientation::LEFT));
			}
			// Down leftmost
			else if (spawnerFac == 3) {
				enemyList.push_back(new Enemy(enemyTexture, defaultSpriteShader, defaultQuad,
					spawnerVector.at(spawnerFac), Orientation::RIGHT));
			}
			// Down rightmost
			else if (spawnerFac == 4) {
				enemyList.push_back(new Enemy(enemyTexture, defaultSpriteShader, defaultQuad,
					spawnerVector.at(spawnerFac), Orientation::LEFT));
			}

			enemyPool -= 1;
			spawnedEnemy += 1;
			TTS = 0;
		}
		else {
			TTS += GetGameTime();
		}
	}

	list<Laser*>::iterator playerLaserIt;
	for (playerLaserIt = playerLaserList.begin(); playerLaserIt != playerLaserList.end(); ++playerLaserIt) {
		Laser* laser = *playerLaserIt;

		if (laser->GetLifecycleState() == GameObjectState::ALIVE) {
			laser->Update(GetGameTime());
			Sprite* laserSprite = laser->GetSpriteComponent();

			if (laserSprite->GetPosition().x < -20 || laserSprite->GetPosition().x > setting->screenWidth) {
				laser->SetState(GameObjectState::DEAD);
			}

			for (Enemy* enemy : enemyList) {
				Sprite* enemySprite = enemy->GetSpriteComponent();

				if (laserSprite->GetBoundingBox()->CollideWith(enemySprite->GetBoundingBox())) {
					enemy->SetLifecycleState(GameObjectState::DEAD);
					score += 10;
					playerLaserIt = playerLaserList.erase(playerLaserIt);

					sfxHit->Play(false);
				}

				if (playerLaserIt == playerLaserList.end()) {
					break;
				}
			}

			for (Sprite* platform : platformList) {
				if (laserSprite->GetBoundingBox()->CollideWith(platform->GetBoundingBox())) {
					playerLaserIt = playerLaserList.erase(playerLaserIt);
				}

				if (playerLaserIt == playerLaserList.end()) {
					break;
				}
			}
		}
		else if (laser->GetLifecycleState() == GameObjectState::DEAD) {
			playerLaserIt = playerLaserList.erase(playerLaserIt);
		}

		if (playerLaserIt == playerLaserList.end()) {
			break;
		}
	}

	// TODO: Contact damage???
	list<Enemy*>::iterator enemyIt;
	for (enemyIt = enemyList.begin(); enemyIt != enemyList.end(); ++enemyIt) {
		Enemy* enemy = *enemyIt;
		if (enemy->GetLifecycleState() == GameObjectState::ALIVE) {
			enemy->Update(GetGameTime());

			enemy->SetShootMood(rand() % 2);

			if (enemy->GetShootMood() == 0) {
				// pass
			}
			else if (enemy->GetShootMood() == 1) {
				if (enemy->GetShootCounter() > enemyMaxShootSpeed) {
					enemyLaserList.push_back(new Laser(enemyLaserTexture, defaultSpriteShader, defaultQuad,
						enemy->GetSpriteComponent()->GetPosition(), enemy->GetOrient(), 5));
					enemy->GetSpriteComponent()->PlayAnim("idle_aim");
					sfxEnemyShoot->Play(false);
					enemy->SetShootCounter(0);
				}
				else {
					enemy->SetShootCounter(enemy->GetShootCounter() + GetGameTime());
				}
			}
		}
		else if (enemy->GetLifecycleState() == GameObjectState::DEAD) {
			enemyIt = enemyList.erase(enemyIt);
		}

		if (enemyIt == enemyList.end()) {
			break;
		}
	}

	list<Laser*>::iterator enemyLaserIt;
	for (enemyLaserIt = enemyLaserList.begin(); enemyLaserIt != enemyLaserList.end(); ++enemyLaserIt) {
		Laser* laser = *enemyLaserIt;
		laser->Update(GetGameTime());

		if (laser->GetLifecycleState() == GameObjectState::ALIVE) {
			Sprite* laserSprite = laser->GetSpriteComponent();

			if (laserSprite->GetPosition().x < -20 || laserSprite->GetPosition().x > setting->screenWidth) {
				laser->SetState(GameObjectState::DEAD);
			}

			if (laserSprite->GetBoundingBox()->CollideWith(player->GetBoundingBox()) == true) {
				sfxHit->Play(false);
				// Comment for godmode
				playerState = GameObjectState::DEAD;
				gameState = GameState::GAMEOVER;
			}
		}
		else if (laser->GetLifecycleState() == GameObjectState::DEAD) {
			enemyLaserIt = enemyLaserList.erase(enemyLaserIt);
		}

		if (enemyLaserIt == enemyLaserList.end()) {
			break;
		}
	}

	// Graphic
	// TODO State based animation, to avoid animation overriding.
	player->PlayAnim("idle");

//Input Handling
	if (isPhysicsInit) {
		lastPlayerPos = playerPos;
	}

	playerPos = player->GetPosition();
	
	/* Just name changes to improve readibility*/
	// Physics update
	xMov = playerPos.x, yMov = playerPos.y;

	if (isPhysicsInit == false) {
		InitPhysics();
	}

	if (inputManager->IsKeyPressed("right")) {
		playerOrient = Orientation::RIGHT;
		xMov += characterSpeedFac;
		player->SetFlipHorizontal(0);
		player->PlayAnim("run");
		if (inputManager->IsKeyReleased("space")) {
			player->PlayAnim("run_aim");
			PlayerShoot();
			if (inputManager->IsKeyPressed("up") && isFalling != true) {
				PlayerJump();

				player->PlayAnim("jump_aim");
			}
		}
		else if (inputManager->IsKeyPressed("up") && isFalling != true) {
			PlayerJump();

			player->PlayAnim("jump");
			if (inputManager->IsKeyReleased("space")) {
				player->PlayAnim("jump_aim");
				PlayerShoot();
			}
		}
	}
	else if (inputManager->IsKeyPressed("left")) {
		playerOrient = Orientation::LEFT;
		xMov -= characterSpeedFac;
		player->SetFlipHorizontal(1);
		player->PlayAnim("run");
		if (inputManager->IsKeyReleased("space")) {
			player->PlayAnim("run_aim");
			PlayerShoot();
			if (inputManager->IsKeyPressed("up") && isFalling != true) {
				PlayerJump();

				player->PlayAnim("jump_aim");
			}
		}
		else if (inputManager->IsKeyPressed("up") && isFalling != true) {
			PlayerJump();

			player->PlayAnim("jump");
			if (inputManager->IsKeyReleased("space")) {
				player->PlayAnim("jump_aim");
				PlayerShoot();
			}
		}
	} else if (inputManager->IsKeyReleased("space")) {
		player->PlayAnim("idle_aim");
		PlayerShoot();
	}
	else if (inputManager->IsKeyPressed("up") && isFalling != true) {
		player->PlayAnim("jump");

		PlayerJump();

		if (inputManager->IsKeyPressed("space")) {
			player->PlayAnim("jump_aim");
			PlayerShoot();
		}
	}

	UpdatePhysics();

	if (inputManager->IsKeyReleased("mute")) {
		if (isMusicRunning == true) {
			mainMusic->Stop();
			isMusicRunning = false;
		}
		else {
			mainMusic->Play(true);
			isMusicRunning = true;
		}
	}

	if (inputManager->IsKeyReleased("escape")) {
		gameState = GameState::PAUSE;
	}

	if (inputManager->IsKeyReleased("debug")) {
		cout << setting->screenWidth << ", " << setting->screenHeight;
	}

	playerBB = player->GetBoundingBox();

	playerBBMarker1->SetPosition(playerBB->GetVertices()[0].x - (0.5f * playerBBMarker1->GetScaleWidth()),
		playerBB->GetVertices()[0].y - (0.5f * playerBBMarker1->GetScaleHeight()));
	playerBBMarker2->SetPosition(playerBB->GetVertices()[1].x - (0.5f * playerBBMarker2->GetScaleWidth()),
		playerBB->GetVertices()[1].y - (0.5f * playerBBMarker2->GetScaleHeight()));
	playerBBMarker3->SetPosition(playerBB->GetVertices()[2].x - (0.5f * playerBBMarker3->GetScaleWidth()),
		playerBB->GetVertices()[2].y - (0.5f * playerBBMarker3->GetScaleHeight()));
	playerBBMarker4->SetPosition(playerBB->GetVertices()[3].x - (0.5f * playerBBMarker4->GetScaleWidth()),
		playerBB->GetVertices()[3].y - (0.5f * playerBBMarker4->GetScaleHeight()));

	floorBB = floor->GetBoundingBox();

	floorBBMarker1->SetPosition(floorBB->GetVertices()[0].x - (0.5f * floorBBMarker1->GetScaleWidth()),
		floorBB->GetVertices()[0].y - (0.5f * floorBBMarker1->GetScaleHeight()));
	floorBBMarker2->SetPosition(floorBB->GetVertices()[1].x - (0.5f * floorBBMarker2->GetScaleWidth()),
		floorBB->GetVertices()[1].y - (0.5f * floorBBMarker2->GetScaleHeight()));
	floorBBMarker3->SetPosition(floorBB->GetVertices()[2].x - (0.5f * floorBBMarker3->GetScaleWidth()),
		floorBB->GetVertices()[2].y - (0.5f * floorBBMarker3->GetScaleHeight()));
	floorBBMarker4->SetPosition(floorBB->GetVertices()[3].x - (0.5f * floorBBMarker4->GetScaleWidth()),
		floorBB->GetVertices()[3].y - (0.5f * floorBBMarker4->GetScaleHeight()));
	
	platform1BB = platform1->GetBoundingBox();

	plt1BBMarker1->SetPosition(platform1BB->GetVertices()[0].x - (0.5f * plt1BBMarker1->GetScaleWidth()),
		platform1BB->GetVertices()[0].y - (0.5f * plt1BBMarker1->GetScaleHeight()));
	plt1BBMarker2->SetPosition(platform1BB->GetVertices()[1].x - (0.5f * plt1BBMarker2->GetScaleWidth()),
		platform1BB->GetVertices()[1].y - (0.5f * plt1BBMarker2->GetScaleHeight()));
	plt1BBMarker3->SetPosition(platform1BB->GetVertices()[2].x - (0.5f * plt1BBMarker3->GetScaleWidth()),
		platform1BB->GetVertices()[2].y - (0.5f * plt1BBMarker3->GetScaleHeight()));
	plt1BBMarker4->SetPosition(platform1BB->GetVertices()[3].x - (0.5f * plt1BBMarker4->GetScaleWidth()),
		platform1BB->GetVertices()[3].y - (0.5f * plt1BBMarker4->GetScaleHeight()));
	
	platform2BB = platform2->GetBoundingBox();

	plt2BBMarker1->SetPosition(platform2BB->GetVertices()[0].x - (0.5f * plt2BBMarker1->GetScaleWidth()),
		platform2BB->GetVertices()[0].y - (0.5f * plt2BBMarker1->GetScaleHeight()));
	plt2BBMarker2->SetPosition(platform2BB->GetVertices()[1].x - (0.5f * plt2BBMarker2->GetScaleWidth()),
		platform2BB->GetVertices()[1].y - (0.5f * plt2BBMarker2->GetScaleHeight()));
	plt2BBMarker3->SetPosition(platform2BB->GetVertices()[2].x - (0.5f * plt2BBMarker3->GetScaleWidth()),
		platform2BB->GetVertices()[2].y - (0.5f * plt2BBMarker3->GetScaleHeight()));
	plt2BBMarker4->SetPosition(platform2BB->GetVertices()[3].x - (0.5f * plt2BBMarker4->GetScaleWidth()),
		platform2BB->GetVertices()[3].y - (0.5f * plt2BBMarker4->GetScaleHeight()));
	
	platform3BB = platform3->GetBoundingBox();

	plt3BBMarker1->SetPosition(platform3BB->GetVertices()[0].x - (0.5f * plt3BBMarker1->GetScaleWidth()),
		platform3BB->GetVertices()[0].y - (0.5f * plt3BBMarker1->GetScaleHeight()));
	plt3BBMarker2->SetPosition(platform3BB->GetVertices()[1].x - (0.5f * plt3BBMarker2->GetScaleWidth()),
		platform3BB->GetVertices()[1].y - (0.5f * plt3BBMarker2->GetScaleHeight()));
	plt3BBMarker3->SetPosition(platform3BB->GetVertices()[2].x - (0.5f * plt3BBMarker3->GetScaleWidth()),
		platform3BB->GetVertices()[2].y - (0.5f * plt3BBMarker3->GetScaleHeight()));
	plt3BBMarker4->SetPosition(platform3BB->GetVertices()[3].x - (0.5f * plt3BBMarker4->GetScaleWidth()),
		platform3BB->GetVertices()[3].y - (0.5f * plt3BBMarker4->GetScaleHeight()));
}

void Main::UpdatePause()
{
	if (inputManager->IsKeyReleased("escape")) {
		gameState = GameState::GAME;
	}
}

void Main::UpdateGameover() {
	if (inputManager->IsKeyReleased("space")) {
		gameState = GameState::GAME;
		stateSwitchFlag = true;
		DestroyInGame();
	}
}

void Main::UpdatePhysics()
{
	// Player Gravity
	if (isFalling) {
		if (yVelocity > maxYVel) {
			yVelocity -= gravity;
		}
		else {
			yVelocity = maxYVel;
		}
		cout << yVelocity << "\n";
	}
	else if (isFalling == false) {
		yVelocity = 0;
		yMov = playerPos.y;
	}

	yMov += yVelocity * GetGameTime();
	player->SetPosition(xMov, yMov);

	// Platform collision checks
	// TODO Horizontal collision checks
	if (isFalling) {
		for (Sprite* platform : platformList) {
			if (platform->GetBoundingBox()->CollideWith(player->GetBoundingBox()))
			{
				// Anti-slide and floor correction
				player->SetPosition(playerPos.x, playerPos.y);

				// and set jump to false and yVelovity to 0
				yVelocity = 0;
				isFalling = false;
				if (playLandSFX) {
					sfxLand->Play(false);
					playLandSFX = false;
				}				
				break;
			}
		}
	}
	// TODO: Do this for enemy??
	// TODO: Figure out how to play sfxLand properly.
	// When player walk off from platform, update the isFalling status.
	else {
		for (Sprite* platform : platformList) {
			if (lastPlayerPos.x != playerPos.x) {
				if (platform->GetBoundingBox()->CollideWith(player->GetBoundingBox()) == false)
				{
					isFalling = true;
					break;
				}
			}
			else {
				break;
			}
		}
	}

	for (Sprite* platform : platformList) {
		for (Enemy* enemy : enemyList) {
			if (enemy->GetIsFalling()) {
				Sprite* enemySprite = enemy->GetSpriteComponent();

				vec2 enemyPos = enemySprite->GetPosition();

				if (platform->GetBoundingBox()->CollideWith(enemySprite->GetBoundingBox()))
				{
					// HACK: Y pos correction, enemy shorter than player for some reason.
					enemySprite->SetPosition(enemyPos.x, enemyPos.y + 6);

					// TODO: Can enemy jump?
					enemy->SetYVelocity(0);
					enemy->SetIsFalling(false);
				}
			}
		}
	}

	if (lastPlayerPos.y > playerPos.y) {
		isFalling = true;
		//cout << isFalling << endl;
	}

}

void Main::DestroyPreMenu()
{
	delete preMenuText;
}

void Main::DestroyMenu()
{
	delete backgroundTextureLogo;
	delete backgroundLogo;
	delete btnNormalTexture;
	delete btnActiveTexture;
	delete btnPlayNormal;
	delete btnExitNormal;
	delete btnPlayActive;
	delete btnExitActive;
	delete playMenuText;
	delete exitMenuText;
}

void Main::DestroyInGame()
{
	// TODO: Proper Game destroy
}

Sprite* Main::CreatePlayer()
{
	playerTexture = new Texture("character.png");
	player = new Sprite(playerTexture, defaultSpriteShader, defaultQuad);
	player->SetNumXFrames(6);
	player->SetNumYFrames(6);
	player->SetAnimationDuration(60 * animationFrameFac);
	player->AddAnimation("idle", 0, 3);
	player->AddAnimation("idle_aim", 6, 9);
	player->AddAnimation("run", 12, 17);
	player->AddAnimation("run_aim", 18, 23);
	player->AddAnimation("jump", 24, 27);
	player->AddAnimation("jump_aim", 30, 33);
	player->SetPosition(50, setting->screenHeight + 50);
	player->SetScale(characterScaleFac);
	player->SetBoundingBoxSize(player->GetScaleWidth() / 1.7, player->GetScaleHeight());

	return player;
}
void Main::PlayerShoot()
{
	playerLaserList.push_back(new Laser(playerLaserTexture, defaultSpriteShader, defaultQuad,
		vec2(player->GetPosition()), playerOrient, 20));
	score -= 2;

	sfxPlayerShoot->Play(false);

	// Wrap this on for minimum time to shoot, but it's less fun :/
	/*if (playerShootCounter > playerMaxShootSpeed) {
		playerShootCounter = 0;
	}
	else {
		playerShootCounter += GetGameTime();
	}*/
}

void Main::PlayerJump() {
	float ratio = (GetGameTime() / 16.7f);
	gravity = 0.16f * ratio;
	yVelocity = 2.3f;

	isFalling = true;
	playLandSFX = true;

	sfxJump->Play(false);
}

float Main::simpleLerp(float v0, float v1, float t) {
	return (1 - t) * v0 + t * v1;
}

int main(int argc, char** argv) {
	Setting* setting = new Setting();
	setting->windowTitle = "Cyber Slug";
	setting->screenWidth = 1024;
	setting->screenHeight = 768;
	setting->windowFlag = WindowFlag::WINDOWED;
	Game* game = new Main(setting);
	game->Run();
	delete setting;
	delete game;

	return 0;
}