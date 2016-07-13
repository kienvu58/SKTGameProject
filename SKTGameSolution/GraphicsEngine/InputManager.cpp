#include "InputManager.h"
#include "Globals.h"

InputManager* InputManager::instance = 0;

InputManager::InputManager()
{
	firstMouse = true;
	lastX = Globals::screenWidth / 2;
	lastY = Globals::screenHeight / 2;
	m_iKeys = 0;
}


InputManager::~InputManager()
{
}

InputManager* InputManager::GetInstance() {
	if (instance == 0) {
		instance = new InputManager();
	}
	return instance;
}