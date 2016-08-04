#include <conio.h>
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include "Game.h"
#include "../Utilities/utilities.h"
#include "../GraphicsEngine/Globals.h"
#include "SingletonClasses.h"
#include "FactoryEntity.h"
#include "SoundManager.h"
float Globals::deltaTime = 0;
//sf::SoundBuffer buffer;
int Init(ESContext* esContext)
{
	// Start the clock
	CrudeTimerSingleton::CreateInstance();

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
	TextMgr->Init("../Resources/Fonts/arial.ttf");
	ResourceMgr->Init("../Resources/Data/RM.json");
	FrameMgr->Init("../Resources/Data/FM.json");
	AnimationMgr->Init("../Resources/Data/AM.json");
	PhysicsMgr->Init();

	//Init music and sound 
//	MusicMainMenu->InitMusic("../Resources/Sound/canary.wav");

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

void Draw(ESContext* esContext)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	Singleton<Game>::GetInstance()->Render();
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void Update(ESContext* esContext, float deltaTime)
{
	if (deltaTime)
	{
		Globals::deltaTime = deltaTime;
		GameInstance->Update();
	}
}

void Key(ESContext* esContext, unsigned char key, bool isPressed)
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

void MouseMove(ESContext* ESContext, float x, float y)
{
	InputMgr->SetCurrentMousePosition(x, y);
}

void MouseDown(ESContext* esContext, float x, float y)
{
	InputMgr->SetCurrentMousePosition(x, y);
	InputMgr->SetLastMousePosition(x, y);
}

void CleanUp()
{
	CrudeTimerSingleton::DestroyInstance();

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

int main(int argc, char* argv[])
{
	ESContext esContext;

	esInitContext(&esContext);

	esCreateWindow(&esContext, "SKT Game", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if (Init(&esContext) != 0)
		return 0;

//	MusicMainMenu->MusicPlay();


	esRegisterDrawFunc(&esContext, Draw);
	esRegisterUpdateFunc(&esContext, Update);
	esRegisterKeyFunc(&esContext, Key);
	esRegisterMouseMoveFunc(&esContext, MouseMove);
	esRegisterMouseDownFunc(&esContext, MouseDown);
	esMainLoop(&esContext);

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	MemoryDump();

	printf("Press any key...\n");
	_getch();

	return 0;
}
