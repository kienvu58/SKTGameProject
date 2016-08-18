#include "Game.h"
#include "../Utilities/utilities.h"
#include "../GraphicsEngine/Globals.h"
#include "SingletonClasses.h"
#include "Definations.h"

float Globals::deltaTime = 0;
float Globals::scaleX = 1;
float Globals::scaleY = 1;

int GameInit()
{
	// Create instance for each manager class
	ResourceManagerSingleton::CreateInstance();
	InputManagerSingleton::CreateInstance();
	TextManagerSingleton::CreateInstance();
	AnimationManagerSingleton::CreateInstance();
	FrameManagerSingleton::CreateInstance();
	PhysicsManagerSingleton::CreateInstance();
	MusicManagerSingleton::CreateInstance();

	FactorySingleton::CreateInstance();
	PoolManagerSingleton::CreateInstance();
	MessageDispatcherSingleton::CreateInstance();

	Game::CreateStateInstances();

	// Initialize data for each manager
	ResourceMgr->Init(RM_PATH);
	TextMgr->Init(FONT_PATH);
	FrameMgr->Init(FM_PATH);
	AnimationMgr->Init(AM_PATH);
	PhysicsMgr->Init();
	Factory->Init(FE_PATH);

	// Init game
	GameSingleton::CreateInstance();

	GameInstance->GetFSM()->SetCurrentState(GS_Welcome::GetInstance());

	GameInstance->Init();

	// Set OpenGl blending option
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return 0;
}

void GameDraw()
{
	GameInstance->Render();
}

void GameUpdate(float deltaTime)
{
	Globals::deltaTime = deltaTime;
	if (deltaTime)
	{
		GameInstance->Update();
	}
}

void OnKeyEvent(unsigned char key, bool isPressed)
{
#ifdef WIN32
	switch (key)
	{
	case 'A':
		InputMgr->SetKeyEvent(KEY_A, isPressed);
		break;
	case 'W':
		InputMgr->SetKeyEvent(KEY_W, isPressed);
		break;
	case 'S':
		InputMgr->SetKeyEvent(KEY_S, isPressed);
		break;
	case 'D':
		InputMgr->SetKeyEvent(KEY_D, isPressed);
		break;
	case 'J':
		InputMgr->SetKeyEvent(KEY_J, isPressed);
		break;
	case 'K':
		InputMgr->SetKeyEvent(KEY_K, isPressed);
		break;
	case 'L':
		InputMgr->SetKeyEvent(KEY_L, isPressed);
		break;
	case 'I':
		InputMgr->SetKeyEvent(KEY_I, isPressed);
		break;
	}
#endif
}

void GameCleanUp()
{
	MessageDispatcherSingleton::DestroyInstance();

	TextManagerSingleton::DestroyInstance();
	InputManagerSingleton::DestroyInstance();
	ResourceManagerSingleton::DestroyInstance();
	AnimationManagerSingleton::DestroyInstance();
	FrameManagerSingleton::DestroyInstance();
	PhysicsManagerSingleton::DestroyInstance();
	MusicManagerSingleton::DestroyInstance();

	FactorySingleton::DestroyInstance();
	PoolManagerSingleton::DestroyInstance();

	Game::DestroyStateInstances();

	GameSingleton::DestroyInstance();
}

void GameSetScaleFactor(int width, int height)
{
    Globals::scaleX = float(Globals::screenWidth) / width;
    Globals::scaleY = float(Globals::screenHeight) / height;
}

void OnTouchEvent(int type, int x, int y, int id)
{
    int mouseX = int(x * Globals::scaleX);
    int mouseY = int(y * Globals::scaleY);

	InputMgr->AddTouchEvent(id, type, mouseX, mouseY);

	if (type == Globals::TOUCH_ACTION_MOVE) {
		InputMgr->SetCurrentMousePosition(mouseX, mouseY);
	}
	if (type == Globals::TOUCH_ACTION_UP) {
		InputMgr->SetMouseDown(false);
	}
	if (type == Globals::TOUCH_ACTION_DOWN) {
		InputMgr->SetCurrentMousePosition(mouseX, mouseY);
		InputMgr->SetLastMousePosition(mouseX, mouseY);
		InputMgr->SetMouseDown(true);
	}
}

void ClearTouchEvents()
{
	InputMgr->ClearTouchEvents();
}
