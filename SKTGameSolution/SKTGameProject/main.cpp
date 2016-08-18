#include <conio.h>
#include "../GraphicsEngine/Globals.h"
#include "SoundManager.h"
#include "../Utilities/MemoryOperators.h"
#include <cstdio>
#include "SingletonClasses.h"
#include "../Utilities/utilities.h"

extern int GameInit();
extern void GameDraw();
extern void GameUpdate(float);
extern void OnKeyEvent(unsigned char, bool);
extern void GameCleanUp();


int Init(ESContext* esContext)
{
	return GameInit();
}

void Draw(ESContext* esContext)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	GameDraw();
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void Update(ESContext* esContext, float deltaTime)
{
	GameUpdate(deltaTime);
}

void Key(ESContext* esContext, unsigned char key, bool isPressed)
{
	OnKeyEvent(key, isPressed);
}

void MouseMove(ESContext* ESContext, float x, float y)
{
	InputMgr->SetCurrentMousePosition(x, y);
}

void MouseDown(ESContext* esContext, float x, float y)
{
	InputMgr->SetCurrentMousePosition(x, y);
	InputMgr->SetLastMousePosition(x, y);
	InputMgr->SetMouseDown(true);
}

void MouseUp(ESContext* esContext, float x, float y)
{
	InputMgr->SetMouseDown(false);
}

void CleanUp()
{
	GameCleanUp();
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
	esRegisterMouseUpFunc(&esContext, MouseUp);
	esMainLoop(&esContext);

	//releasing OpenGL resources
	CleanUp();

	//#ifdef WIN32
	//identifying memory leaks
	MemoryDump();
	//#endif

	printf("Press any key...\n");
	_getch();

	return 0;
}
