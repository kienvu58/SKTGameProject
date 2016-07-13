#include <Box2D/Box2d.h>
#include "../Utilities/utilities.h"
#include <iostream>
#include <conio.h>
#include "../GraphicsEngine/Globals.h"

int Init(ESContext* esContext)
{
	return 0;
}

void Draw(ESContext* esContext)
{
}

void Update(ESContext* esContext, float deltaTime)
{

}

void Key(ESContext* esContext, unsigned char key, bool isPressed)
{
}

void CleanUp()
{
}

int main(int argc, char* argv[])
{
	ESContext esContext;

	esInitContext(&esContext);
	
	esCreateWindow(&esContext, "SKT Game", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if (Init(&esContext) != 0)
		return 0;
	esRegisterDrawFunc(&esContext, Draw);
	esRegisterUpdateFunc(&esContext, Update);
	esRegisterKeyFunc(&esContext, Key);
	esMainLoop(&esContext);

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	MemoryDump();

	printf("Press any key...\n");
	_getch();

	return 0;
}
