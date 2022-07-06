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

	inputManager->AddInputMapping("mute", SDLK_m);
	inputManager->AddInputMapping("debug", SDLK_TAB);

// Sound
	// Music
	// TODO: Separate music class
	mainMusic = new Music("music_main.wav");
	mainMusic->SetVolume(10);
	mainMusic->Play(true);

	InitPreMenu();
}

void Main::Update()
{
// GameState Switch
	if (initFlag) {
		if (state == GameState::MENU) {
			InitMenu();
			initFlag = false;
		}
		else if (state == GameState::GAME) {
			InitInGame();
			initFlag = false;
		}
		else if (state == GameState::PAUSE) {
			InitPause();
			initFlag = false;
		}
	}

// State Update
	if (state == GameState::PREMENU) {
		UpdatePreMenu();
	}
	else if (state == GameState::MENU) {
		UpdateMenu();
	}
	else if (state == GameState::GAME) {
		UpdateInGame();
	}
	else if (state == GameState::PAUSE) {
		UpdatePause();
	}
}

void Main::Render()
{
	if (state == GameState::PREMENU) {
		logo->Draw();
		preMenuText->Draw();
	}
	else if (state == GameState::MENU) {
		playButton->Draw();
		exitButton->Draw();	

		player->Draw();

		// TODO: Bullet list loop draw call.
		for (Laser* laser: laserList) {
			laser->Draw();
		}
	}
	else if (state == GameState::GAME) {
		background->Draw();
		//floor->Draw();
	}
	else if (state == GameState::PAUSE) {

	}
}

void Engine::Main::InitPreMenu()
{
	SetBackgroundColor(120, 120, 120);

	// Logo
	logoTexture = new Texture("logo.png");
	logo = new Sprite(logoTexture, defaultSpriteShader, defaultQuad);

	logo->SetPosition(100, 600);
	logo->SetScale(0.8);

	// Text
	preMenuText = new Text("Abaddon Bold.ttf", 30, defaultTextShader);
	preMenuText->SetColor(255, 255, 255);
	preMenuText->SetText("Press space key to continue...");

	preMenuText->SetPosition(100, 100);
	preMenuText->SetScale(1);
}

void Engine::Main::InitMenu()
{
	// Menu
	menuTexture = new Texture("menu.png");

	playButton = new Sprite(menuTexture, defaultSpriteShader, defaultQuad);
	playButton->SetNumXFrames(1);
	playButton->SetNumYFrames(2);
	playButton->AddAnimation("idle", 0, 0);
	playButton->AddAnimation("hover", 1, 1);
	playButton->PlayAnim("idle");
	playButton->SetPosition(100, setting->screenHeight / 2);
	playButton->SetScale(4);

	exitButton = new Sprite(menuTexture, defaultSpriteShader, defaultQuad);
	exitButton->SetNumXFrames(1);
	exitButton->SetNumYFrames(2);
	exitButton->AddAnimation("idle", 0, 0);
	exitButton->AddAnimation("hover", 1, 1);
	exitButton->PlayAnim("idle");
	exitButton->SetPosition(100, (setting->screenHeight / 2) - (playButton->GetScaleHeight() + 20));
	exitButton->SetScale(4);

// Graphic
	//Character
	// TODO: Separate character class.
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
	player->SetScale(spriteScaleFac);
	// Boundingbox goes here
	// 
	// Enemy
	//enemyTexture = new Texture("");

	// Laser
	laserTexture = new Texture("bullet_trail.png");

	// SFX
	sfxShoot = new Sound("SingleShot2.wav");
	sfxShoot->SetVolume(5);
}

void Engine::Main::InitInGame()
{
	// Background
	backgroundTexture = new Texture("cyber_sunrise.png");
	background = new Sprite(backgroundTexture, defaultSpriteShader, defaultQuad);
	background->SetPosition(0, 0);
}

void Engine::Main::InitPause()
{
}

void Engine::Main::UpdatePreMenu()
{
	if (inputManager->IsKeyReleased("space")) {
		//state = GameState::MENU;
	}
}

void Engine::Main::UpdateMenu()
{
	// Anim Updates
	playButton->Update(GetGameTime());
	exitButton->Update(GetGameTime());

	player->Update(GetGameTime());

	for (Laser* laser : laserList) {
		laser->Update(GetGameTime());
	}

	// Graphic
	player->PlayAnim("idle");

	//Input Handling
	playerPos = player->GetPosition();
	playerRot = player->GetRotation();

	// Gravity
	// TODO: Gravity
	// TODO: Bullet minimum shooting time
	if (inputManager->IsKeyPressed("right")) {
		player->SetPosition(playerPos.x + characterSpeedFac, playerPos.y);
		player->SetFlipHorizontal((playerRot == -180 ? 1 : 0));
		player->PlayAnim("run");
		if (inputManager->IsKeyPressed("space")) {
			cout << "pewpew!";

			//bullet->SetPosition(playerPos.x + 10, playerPos.y);

			sfxShoot->Play(false);
			player->PlayAnim("run_aim");
		}
	}
	else if (inputManager->IsKeyPressed("left")) {
		player->SetPosition(playerPos.x - characterSpeedFac, playerPos.y);
		player->SetFlipHorizontal((playerRot == 0) ? 1 : 0);
		player->PlayAnim("run");
		if (inputManager->IsKeyPressed("space")) {
			cout << "pewpew!";

			//bullet->SetPosition(playerPos.x - 10, playerPos.y);

			sfxShoot->Play(false);
			player->PlayAnim("run_aim");
		}
	}
	else if (inputManager->IsKeyPressed("up")) {
		player->PlayAnim("jump");
		if (inputManager->IsKeyPressed("space")) {
			cout << "pewpew!";

			//bullet->SetPosition(playerPos.x + 10, playerPos.y);

			sfxShoot->Play(false);
			player->PlayAnim("jump_aim");
		}
	}
	else if (inputManager->IsKeyPressed("space")) {
		cout << "pewpew!";

		laserList.push_back(new Laser(CreateLaser()));

		sfxShoot->Play(false);
		player->PlayAnim("idle_aim");
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

	if (inputManager->IsKeyReleased("debug")) {
		cout << setting->screenHeight << ", " << setting->screenWidth;
	}
}

void Engine::Main::UpdateInGame()
{
}

void Engine::Main::UpdatePause()
{
}

Sprite* Main::CreateLaser() {
	Sprite* laser = new Sprite(laserTexture, defaultSpriteShader, defaultQuad);
	laser->SetNumXFrames(4);
	laser->SetNumYFrames(1);
	laser->SetAnimationDuration(60 * animationFrameFac);
	laser->AddAnimation("pulse", 0, 3);
	laser->SetScale(spriteScaleFac);
	laser->PlayAnim("pulse");

	laser->SetPosition(playerPos.x + 34, playerPos.y);

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