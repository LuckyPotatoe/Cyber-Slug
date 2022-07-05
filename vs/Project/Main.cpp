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
	inputManager->AddInputMapping("space", SDLK_SPACE);

	inputManager->AddInputMapping("mute", SDLK_m);
	inputManager->AddInputMapping("debug", SDLK_TAB);

// Graphic
	// Background
	/*
	backgroundTexture = new Texture("");
	background = new Sprite(backgroundTexture, defaultSpriteShader, defaultQuad);
	*/
	SetBackgroundColor(130, 130, 130);

	// Platform
	floorTexture = new Texture("");
	floor = new Sprite(floorTexture, defaultSpriteShader, defaultQuad);

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
	// Boundingbox goes here

	//Laser
	Laser* laser1 = new Laser(laserPrefab);

	// Text
	/*
	text = new Text("lucon.ttf", 14, defaultTextShader);
	text->SetScale(1.0f);
	text->SetColor(255, 255, 255);
	text->SetPosition(0, setting->screenHeight - (text->GetFontSize() * text->GetScale()));
	*/
// Sound
	// Music
	// TODO: Separate music class
	mainMusic = new Music("music_main.wav");
	mainMusic->SetVolume(10);
	mainMusic->Play(true);
	
	// SFX
	sfxShoot = new Sound("SingleShot2.wav");
	sfxShoot->SetVolume(5);
}

void Main::Update()
{
// Graphic
	player->Update(GetGameTime());

	player->PlayAnim("idle");

//Input Handling
	playerPos = player->GetPosition();
	playerRot = player->GetRotation();

	/*
	bulletPos = bullet->GetPosition();
	bulletRot = bullet->GetRotation();
	*/

	// TODO: Bullet minimum shooting time
	if (inputManager->IsKeyPressed("right")) {
		player->SetPosition(playerPos.x + characterSpeedFac, playerPos.y);
		player->SetFlipHorizontal((playerRot == -180 ? 1 : 0));
		player->PlayAnim("run");
		if (inputManager->IsKeyPressed("space")) {
			cout << "pewpew!";

			//bullet->SetPosition(playerPos.x + 10, playerPos.y);
			//bullet->PlayAnim("pulse");

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
			//bullet->PlayAnim("pulse");

			sfxShoot->Play(false);
			player->PlayAnim("run_aim");
		}
	}
	else if (inputManager->IsKeyPressed("up")) {
		player->PlayAnim("jump");
		if (inputManager->IsKeyPressed("space")) {
			cout << "pewpew!";

			//bullet->SetPosition(playerPos.x + 10, playerPos.y);
			//bullet->PlayAnim("pulse");

			sfxShoot->Play(false);
			player->PlayAnim("jump_aim");
		}
	}
	else if (inputManager->IsKeyPressed("space")) {
		cout << "pewpew!";

		//bullet->SetPosition(playerPos.x + 10, playerPos.y);
		//bullet->PlayAnim("pulse");

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

void Main::Render()
{
	// Stage
	//background->Draw();
	floor->Draw();

	// Character
	player->Draw();

	// Bullet draw
	// TODO: Bullet list loop draw call.
}

int main(int argc, char** argv) {
	Setting* setting = new Setting();
	setting->windowTitle = "Cyber Slug";
	setting->screenWidth = 1024;
	setting->screenHeight = 768;
	setting->windowFlag = WindowFlag::BORDERLESS;
	Game* game = new Main(setting);
	game->Run();
	delete setting;
	delete game;

	return 0;
}