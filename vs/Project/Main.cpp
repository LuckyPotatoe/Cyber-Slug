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
	if (stateSwitchFlag) {
		if (state == GameState::MENU) {
			InitMenu();
			stateSwitchFlag = false;
		}
		else if (state == GameState::GAME) {
			InitInGame();
			stateSwitchFlag = false;
		}
		else if (state == GameState::PAUSE) {
			InitPause();
			stateSwitchFlag = false;
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
		if (logo == NULL || preMenuText == NULL) {
			return;
		}
		logo->Draw();
		preMenuText->Draw();
	}
	else if (state == GameState::MENU) {
		if (playButton == NULL || exitButton == NULL || player == NULL) {
			return;
		}
		playButton->Draw();
		exitButton->Draw();	

		player->Draw();

		dotSprite1->Draw();
		dotSprite2->Draw();
		dotSprite3->Draw();
		dotSprite4->Draw();

		for (Laser* laser: laserList) {
			if (laser != NULL) {
				laser->Draw();
			}
		}
	}
	else if (state == GameState::GAME) {
		if (background != NULL) {
			background->Draw();
		}
		//floor->Draw();
	}
	else if (state == GameState::PAUSE) {

	}
}

void Engine::Main::InitPreMenu()
{
	SetBackgroundColor(120, 120, 120);

	logoTexture = new Texture("logo.png");
	logo = new Sprite(logoTexture, defaultSpriteShader, defaultQuad);

	logo->SetPosition(100, 600);
	logo->SetScale(0.8);

	preMenuText = new Text("Abaddon Bold.ttf", 30, defaultTextShader);
	preMenuText->SetColor(255, 255, 255);
	preMenuText->SetText("Press space key to continue...");

	preMenuText->SetPosition(100, 100);
	preMenuText->SetScale(1);
}

void Engine::Main::InitMenu()
{
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
	player->SetScale(characterScaleFac);
	player->SetBoundingBoxSize(player->GetScaleWidth() / 1.7, player->GetScaleHeight());

	dot = new Texture("dot.png");

	dotSprite1 = new Sprite(dot, defaultSpriteShader, defaultQuad);
	dotSprite2 = new Sprite(dot, defaultSpriteShader, defaultQuad);
	dotSprite3 = new Sprite(dot, defaultSpriteShader, defaultQuad);
	dotSprite4 = new Sprite(dot, defaultSpriteShader, defaultQuad);

	// Laser
	laserTexture = new Texture("bullet_trail.png");

	// SFX
	sfxShoot = new Sound("SingleShot2.wav");
	sfxShoot->SetVolume(5);
}

void Engine::Main::InitInGame()
{
	// Enemy
	enemyTexture = new Texture("");

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
		state = GameState::MENU;
		stateSwitchFlag = true;
		DestroyPreMenu();
	}
}

void Engine::Main::UpdateMenu()
{
	// Anim Updates
	playButton->Update(GetGameTime());
	exitButton->Update(GetGameTime());

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
	playerPos = player->GetPosition();
	playerRot = player->GetRotation();

	// Gravity
	// TODO: Gravity
	if (inputManager->IsKeyPressed("right")) {
		playerOrient = Orientation::RIGHT;
		player->SetPosition(playerPos.x + characterSpeedFac, playerPos.y);
		player->SetFlipHorizontal(0);
		player->PlayAnim("run");
		if (inputManager->IsKeyPressed("space")) {
			cout << "pewpew!";
			player->PlayAnim("run_aim");

			if (shootCounter > maxShootSpeed) {
				laserList.push_back(new Laser(CreateLaser(), playerOrient));
				sfxShoot->Play(false);
				shootCounter = 0;
			}
			else {
				shootCounter += GetGameTime();
			}
		}
	}
	else if (inputManager->IsKeyPressed("left")) {
		playerOrient = Orientation::LEFT;
		player->SetPosition(playerPos.x - characterSpeedFac, playerPos.y);
		player->SetFlipHorizontal(1);
		player->PlayAnim("run");
		if (inputManager->IsKeyPressed("space")) {
			cout << "pewpew!";
			player->PlayAnim("run_aim");

			if (shootCounter > maxShootSpeed) {
				laserList.push_back(new Laser(CreateLaser(), playerOrient));
				sfxShoot->Play(false);
				shootCounter = 0;
			}
			else {
				shootCounter += GetGameTime();
			}
		}
	}
	else if (inputManager->IsKeyPressed("up")) {
		player->PlayAnim("jump");
		if (inputManager->IsKeyPressed("space")) {
			cout << "pewpew!";
			player->PlayAnim("jump_aim");

			if (shootCounter > maxShootSpeed) {
				laserList.push_back(new Laser(CreateLaser(), playerOrient));
				sfxShoot->Play(false);
				shootCounter = 0;
			}
			else {
				shootCounter += GetGameTime();
			}
		}
	}
	else if (inputManager->IsKeyPressed("space")) {
		cout << "pewpew!";
		player->PlayAnim("idle_aim");

		if (shootCounter > maxShootSpeed) {
			laserList.push_back(new Laser(CreateLaser(), playerOrient));
			sfxShoot->Play(false);
			shootCounter = 0;
		}
		else {
			shootCounter += GetGameTime();
		}
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

	playerBB = player->GetBoundingBox();

	dotSprite1->SetPosition(playerBB->GetVertices()[0].x - (0.5f * dotSprite1->GetScaleWidth()),
		playerBB->GetVertices()[0].y - (0.5f * dotSprite1->GetScaleHeight()));
	dotSprite2->SetPosition(playerBB->GetVertices()[1].x - (0.5f * dotSprite2->GetScaleWidth()),
		playerBB->GetVertices()[1].y - (0.5f * dotSprite2->GetScaleHeight()));
	dotSprite3->SetPosition(playerBB->GetVertices()[2].x - (0.5f * dotSprite3->GetScaleWidth()),
		playerBB->GetVertices()[2].y - (0.5f * dotSprite3->GetScaleHeight()));
	dotSprite4->SetPosition(playerBB->GetVertices()[3].x - (0.5f * dotSprite4->GetScaleWidth()),
		playerBB->GetVertices()[3].y - (0.5f * dotSprite3->GetScaleHeight()));
}

void Engine::Main::UpdateInGame()
{
}

void Engine::Main::UpdatePause()
{
}

void Engine::Main::DestroyPreMenu()
{
	delete logo;
	delete logoTexture;
	delete preMenuText;
}

void Engine::Main::DestroyMenu()
{
}

void Engine::Main::DestroyInGame()
{
}

void Engine::Main::DestroyPause()
{
}

Sprite* Main::CreateLaser() {
	Sprite* laser = new Sprite(laserTexture, defaultSpriteShader, defaultQuad);
	laser->SetNumXFrames(4);
	laser->SetNumYFrames(1);
	laser->SetAnimationDuration(15);
	laser->AddAnimation("pulse", 0, 3);
	laser->SetScale(1.8);
	laser->PlayAnim("pulse");
	
	// Position correction for the gun barrel
	if (playerOrient == Orientation::RIGHT) {
		laser->SetPosition(playerPos.x + 100, playerPos.y + 30);
	}
	else if (playerOrient == Orientation::LEFT) {
		laser->SetPosition(playerPos.x - 100, playerPos.y + 30);
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