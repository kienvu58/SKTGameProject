#include "Game.h"
#include "../Utilities/utilities.h"
#include "../GraphicsEngine/Globals.h"
#include "SingletonClasses.h"
#include "../GraphicsEngine/HelperFunctions.h"
#include "Definations.h"

#ifndef WIN32
#include "jni_base.h"
#endif

float Globals::deltaTime = 0;

int GameInit()
{
	// Start the clock
	//	CrudeTimerSingleton::CreateInstance();

	// Create instance for each manager class
	InputManagerSingleton::CreateInstance();
	TextManagerSingleton::CreateInstance();
	AnimationManagerSingleton::CreateInstance();
	FrameManagerSingleton::CreateInstance();
	ResourceManagerSingleton::CreateInstance();
	PhysicsManagerSingleton::CreateInstance();
	MusicManagerSingleton::CreateInstance();

	MessageDispatcherSingleton::CreateInstance();

	// Initialize data for each manager
	TextMgr->Init(FONT_PATH);
	ResourceMgr->Init(RM_PATH);
	FrameMgr->Init(FM_PATH);
	AnimationMgr->Init(AM_PATH);
	PhysicsMgr->Init();

	// Init game
	GameSingleton::CreateInstance();

	GameInstance->CreateStateInstances();
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
	}
}

void GameCleanUp()
{
	//	CrudeTimerSingleton::DestroyInstance();

	MessageDispatcherSingleton::DestroyInstance();

	TextManagerSingleton::DestroyInstance();
	InputManagerSingleton::DestroyInstance();
	ResourceManagerSingleton::DestroyInstance();
	AnimationManagerSingleton::DestroyInstance();
	FrameManagerSingleton::DestroyInstance();
	PhysicsManagerSingleton::DestroyInstance();
	MusicManagerSingleton::DestroyInstance();

	GameInstance->DestroyStateInstances();
	GameSingleton::DestroyInstance();
}

void OnTouchEvent(int type, int x, int y, int id)
{
	static const int TOUCH_ACTION_UP = 0;
	static const int TOUCH_ACTION_DOWN = 1;
	static const int TOUCH_ACTION_MOVE = 2;

//	WORD movementMask(0);
//	WORD rotationMask(0);

	static Vector2 basePoint;
	Vector2 currentPoint(0, 0);

	if (type == TOUCH_ACTION_DOWN) {
		basePoint = Vector2(x, y);
		currentPoint = basePoint;
	}
	else if (type == TOUCH_ACTION_MOVE) {
		int dx = x - basePoint.x;
		int dy = y - basePoint.y;

		if (abs(dx) > abs(dy)) {
//			movementMask = dx > 0 ? MOVE_LEFT : MOVE_RIGHT;
		}
		else {
//			movementMask = dy > 0 ? MOVE_BACKWARD : MOVE_FORWARD;
		}

//		GetSceneManager()->SetMovementMask(movementMask);
//		GetSceneManager()->SetRotationMask(rotationMask);

	}
	else { //TOUCH_ACTION_UP
//		movementMask = 0;
	}
}
