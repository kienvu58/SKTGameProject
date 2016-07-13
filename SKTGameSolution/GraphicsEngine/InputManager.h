#pragma once

#define KEY_A 1
#define KEY_D 2
#define KEY_W 4
#define KEY_S 8

class InputManager
{
private:
	InputManager();
	static InputManager* instance;
public:
	int m_iKeys;
	float lastX;
	float lastY;
	bool firstMouse;
	~InputManager();
	static InputManager* GetInstance();
};

