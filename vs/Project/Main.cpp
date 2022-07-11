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

// Sound
	// Music
	// TODO: Separate music class
	mainMusic = new Music("music_main.wav");
	mainMusic->SetVolume(10);
	mainMusic->Play(true);

// Pause
	pauseOverlayTexture = new Texture("pause_overlay.png");
	pauseOverlay = new Sprite(pauseOverlayTexture, defaultSpriteShader, defaultQuad);
	
	pauseText = new Text("Abaddon Bold.ttf", 30, defaultTextShader);
	pauseText->SetText("PAUSED");
	pauseText->SetPosition(setting->screenWidth / 2, setting->screenHeight / 2);

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
		else if (gameState == GameState::PAUSE) {
			InitPause();
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

		if (dotSprite1 != NULL) {
			dotSprite1->Draw();
			dotSprite2->Draw();
			dotSprite3->Draw();
			dotSprite4->Draw();

			dotSprite5->Draw();
			dotSprite6->Draw();
			dotSprite7->Draw();
			dotSprite8->Draw();
		}

		for (Laser* laser : laserList) {
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

		if (dotSprite1 != NULL) {
			dotSprite1->Draw();
			dotSprite2->Draw();
			dotSprite3->Draw();
			dotSprite4->Draw();

			dotSprite5->Draw();
			dotSprite6->Draw();
			dotSprite7->Draw();
			dotSprite8->Draw();
		}

		for (Laser* laser : laserList) {
			if (laser != NULL) {
				laser->Draw();
			}
		}

		if (pauseOverlay != NULL && pauseText != NULL) {
			pauseOverlay->Draw();
			pauseText->Draw();
		}
	}
}

void Engine::Main::InitPreMenu()
{
	backgroundTextureLogo = new Texture("background_logo.png");
	backgroundLogo = new Sprite(backgroundTextureLogo, defaultSpriteShader, defaultQuad);

	preMenuText = new Text("Abaddon Bold.ttf", 30, defaultTextShader);
	preMenuText->SetColor(255, 255, 255);
	preMenuText->SetText("Press space key to continue...");

	preMenuText->SetPosition(100, 100);
	preMenuText->SetScale(1);
}

void Engine::Main::InitMenu()
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
}

void Engine::Main::InitInGame()
{
	spawnPointList = {
		// High center falldown
		{setting->screenWidth, setting->screenHeight + 25},
		// Down leftmost point
		{-20, 0},
		// down lightmost point
		{(setting->screenWidth * 2) + 20, 0}
	};

	// Background
	backgroundTexturePlain = new Texture("background_plain.png");
	backgroundPlain = new Sprite(backgroundTexturePlain, defaultSpriteShader, defaultQuad);

	//Text
	scoreText = new Text("Abaddon Bold.ttf", 30, defaultTextShader);
	scoreText->SetText("Score: " + to_string(score));
	scoreText->SetPosition(50, setting->screenHeight - 50);

	// Stage
	dot = new Texture("dot.png");

	floor = new Sprite(dot, defaultSpriteShader, defaultQuad);
	floor->SetScale(1);
	floor->SetBoundingBoxSize(setting->screenWidth * 2, 50);

	// Graphic
	player = CreatePlayer();

	dotSprite1 = new Sprite(dot, defaultSpriteShader, defaultQuad);
	dotSprite2 = new Sprite(dot, defaultSpriteShader, defaultQuad);
	dotSprite3 = new Sprite(dot, defaultSpriteShader, defaultQuad);
	dotSprite4 = new Sprite(dot, defaultSpriteShader, defaultQuad);

	dotSprite5 = new Sprite(dot, defaultSpriteShader, defaultQuad);
	dotSprite6 = new Sprite(dot, defaultSpriteShader, defaultQuad);
	dotSprite7 = new Sprite(dot, defaultSpriteShader, defaultQuad);
	dotSprite8 = new Sprite(dot, defaultSpriteShader, defaultQuad);

	// Laser
	laserTexture = new Texture("bullet_trail.png");

	// SFX
	sfxShoot = new Sound("SingleShot2.wav");
	sfxShoot->SetVolume(5);

	// Enemy
	// TODO: Change texture to actual enemy texture
	enemyTexture = new Texture("character.png");
}

void Engine::Main::InitPause()
{
	// MOVED TO Init(), ga gede2 amat, to avoid redundant calls.
	// We modify draw call and state changing to handle pause.
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

	player->Update(GetGameTime());

	// TODO: Laser delete call.
	for (Laser* laser : laserList) {
		laser->Update(GetGameTime());
		if (laser->GetPosition().x < 0 || laser->GetPosition().x > setting->screenWidth) {
			laser->SetState(GameObjectState::DEAD);
		}
	}

	// Graphic
	player->PlayAnim("idle");

	//Input Handling
	lastPlayerPos = playerPos;
	playerPos = player->GetPosition();
	playerRot = player->GetRotation();

	UpdatePhysics();

	// TODO: Air control
	// TODO: Character state handling
	// TODO: Momentum system
	if (inputManager->IsKeyPressed("right")) {
		playerOrient = Orientation::RIGHT;
		if (isMoving) {
			acceleration = 1;
		}
		else if (isMoving == false) {
			acceleration = 0;
		}

		player->SetPosition(playerPos.x + characterSpeedFac, playerPos.y);
		player->SetFlipHorizontal(0);
		player->PlayAnim("run");
		UpdatePhysics();
		if (inputManager->IsKeyPressed("space")) {
			player->PlayAnim("run_aim");
			Shoot();
			if (inputManager->IsKeyReleased("up") && isFalling != true) {
				player->PlayAnim("jump_aim");
				player->SetPosition(playerPos.x, playerPos.y + 100);
			}
		}
		else if (inputManager->IsKeyReleased("up") && isFalling != true) {
			player->PlayAnim("jump");
			player->SetPosition(playerPos.x, playerPos.y + 100);
			if (inputManager->IsKeyPressed("space")) {
				player->PlayAnim("jump_aim");
				Shoot();
			}
		}
	}
	else if (inputManager->IsKeyPressed("left")) {
		playerOrient = Orientation::LEFT;
		if (isMoving) {
			acceleration = 1;
		}
		else if (isMoving == false) {
			acceleration = 0;
		}

		player->SetPosition(playerPos.x - characterSpeedFac, playerPos.y);
		player->SetFlipHorizontal(1);
		player->PlayAnim("run");
		UpdatePhysics();
		if (inputManager->IsKeyPressed("space")) {
			player->PlayAnim("run_aim");
			Shoot();
			if (inputManager->IsKeyReleased("up") && isFalling != true) {
				player->PlayAnim("jump_aim");
				player->SetPosition(playerPos.x, playerPos.y + 100);
			}
		}
		else if (inputManager->IsKeyReleased("up") && isFalling != true) {
			player->PlayAnim("jump");
			player->SetPosition(playerPos.x, playerPos.y + 100);
			if (inputManager->IsKeyPressed("space")) {
				player->PlayAnim("jump_aim");
				Shoot();
			}
		}
	}
	else if (inputManager->IsKeyReleased("up") && isFalling != true) {
		player->PlayAnim("jump");
		player->SetPosition(playerPos.x, playerPos.y + 100);
		if (inputManager->IsKeyPressed("space")) {
			player->PlayAnim("jump_aim");
			Shoot();
		}
	}
	else if (inputManager->IsKeyPressed("space")) {
		player->PlayAnim("idle_aim");
		Shoot();
	}

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

	dotSprite1->SetPosition(playerBB->GetVertices()[0].x - (0.5f * dotSprite1->GetScaleWidth()),
		playerBB->GetVertices()[0].y - (0.5f * dotSprite1->GetScaleHeight()));
	dotSprite2->SetPosition(playerBB->GetVertices()[1].x - (0.5f * dotSprite2->GetScaleWidth()),
		playerBB->GetVertices()[1].y - (0.5f * dotSprite2->GetScaleHeight()));
	dotSprite3->SetPosition(playerBB->GetVertices()[2].x - (0.5f * dotSprite3->GetScaleWidth()),
		playerBB->GetVertices()[2].y - (0.5f * dotSprite3->GetScaleHeight()));
	dotSprite4->SetPosition(playerBB->GetVertices()[3].x - (0.5f * dotSprite4->GetScaleWidth()),
		playerBB->GetVertices()[3].y - (0.5f * dotSprite3->GetScaleHeight()));

	floorBB = floor->GetBoundingBox();

	dotSprite5->SetPosition(floorBB->GetVertices()[0].x - (0.5f * dotSprite5->GetScaleWidth()),
		floorBB->GetVertices()[0].y - (0.5f * dotSprite5->GetScaleHeight()));
	dotSprite6->SetPosition(floorBB->GetVertices()[1].x - (0.5f * dotSprite6->GetScaleWidth()),
		floorBB->GetVertices()[1].y - (0.5f * dotSprite6->GetScaleHeight()));
	dotSprite7->SetPosition(floorBB->GetVertices()[2].x - (0.5f * dotSprite7->GetScaleWidth()),
		floorBB->GetVertices()[2].y - (0.5f * dotSprite7->GetScaleHeight()));
	dotSprite8->SetPosition(floorBB->GetVertices()[3].x - (0.5f * dotSprite8->GetScaleWidth()),
		floorBB->GetVertices()[3].y - (0.5f * dotSprite8->GetScaleHeight()));

	// TODO: Enemy Spawn
	//enemyList.push_back(CreateEnemy());
}

void Engine::Main::UpdatePause()
{
	if (inputManager->IsKeyReleased("escape")) {
		gameState = GameState::GAME;
	}
}

void Engine::Main::UpdatePhysics()
{
	if (lastPlayerPos.x != playerPos.x) {
		isMoving = true;
	}
	else {
		isMoving = false;
	}
	
	if (lastPlayerPos.y > playerPos.y) {
		isFalling = true;
	}
	else {
		isFalling = false;
	}

	/* 
	Acceleration: Simplifying the actual physics for a more 'arcadey' feeling not floaty.
	Accel kicks into max value const the moment a movement is made (on ground),
	it is made as a decay factor for momentum.
	*/
	if (acceleration = 0) {
		momentum = simpleLerp(momentum, 0, 0.8);
	}
	else if (playerOrient == Orientation::RIGHT) {
		// This is to avoid mid air direction switching
		if (momentum >= 0) {
			momentum = simpleLerp(momentum, 10, acceleration);
		}
	}
	else if (playerOrient == Orientation::LEFT) {
		if (momentum <= 0) {
			momentum = simpleLerp(momentum, -10, acceleration);
		}
	}

	// Gravity
	if (player->GetBoundingBox()->CollideWith(floor->GetBoundingBox()) == false) {
		player->SetPosition(playerPos.x + momentum, playerPos.y - gravity);
	}
	
	// Floor correction
	if (playerPos.y < 50) {
		player->SetPosition(playerPos.x, 50);
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
}

void Main::DestroyPause()
{
	// EMPTY TO SAVE I/O CALLS

	/*delete pauseOverlayTexture;
	delete pauseOverlay;
	delete pauseText;*/
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

Sprite* Main::CreateLaser() {
	Sprite* laser = new Sprite(laserTexture, defaultSpriteShader, defaultQuad);
	laser->SetNumXFrames(4);
	laser->SetNumYFrames(1);
	laser->SetAnimationDuration(15);
	laser->AddAnimation("pulse", 0, 3);
	laser->SetScale(1.2);
	laser->PlayAnim("pulse");
	laser->SetBoundingBoxSize(laser->GetScaleWidth(), laser->GetScaleHeight());
	
	// Position correction for the gun barrel
	// TODO: Hardcode offset?
	if (playerOrient == Orientation::RIGHT) {
		laser->SetPosition(playerPos.x + 70, playerPos.y + 21);
	}
	else if (playerOrient == Orientation::LEFT) {
		laser->SetPosition(playerPos.x - 70, playerPos.y + 21);
		laser->SetFlipHorizontal(1);
	}

	return laser;
}

Sprite* Main::CreateEnemy() {
	Sprite* enemy = new Sprite(enemyTexture, defaultSpriteShader, defaultQuad);
	enemy->SetNumXFrames(6);
	enemy->SetNumYFrames(6);
	enemy->SetAnimationDuration(60 * animationFrameFac);
	enemy->AddAnimation("idle", 0, 3);
	enemy->AddAnimation("idle_aim", 6, 9);
	enemy->AddAnimation("run", 12, 17);
	enemy->AddAnimation("run_aim", 18, 23);
	enemy->AddAnimation("jump", 24, 27);
	enemy->AddAnimation("jump_aim", 30, 33);

	return enemy;
}

void Main::Shoot()
{
	cout << "pewpew!";

	if (shootCounter > maxShootSpeed) {
		laserList.push_back(new Laser(CreateLaser(), playerOrient));
		sfxShoot->Play(false);
		shootCounter = 0;
	}
	else {
		shootCounter += GetGameTime();
	}
}

float Main::simpleLerp(float v0, float v1, float t){
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