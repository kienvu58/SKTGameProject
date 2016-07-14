#pragma once

#define KEY_A (1 << 0)
#define KEY_D (1 << 1)
#define KEY_W (1 << 2)
#define KEY_S (1 << 3)
#include "../Utilities/Math.h"

class InputManager
{
public:
	static InputManager* GetInstance();
	static void DestroyInstance();
	void SetKeyEvent(int key, bool isPressed);
	bool IsPressed(int key) const;
	void SetLastMousePosition(int x, int y);
	void SetCurrentMousePosition(int x, int y);
	Vector2 GetLastMousePosition();
	Vector2 GetCurrentMousePosition();
	~InputManager();
private: 
	InputManager(); 
	static InputManager* s_Instance;
	int m_iKeyPressed;
	Vector2 m_v2LastMousePos;
	Vector2 m_v2CurrentMousePos;
};

#define InputMgr InputManager::GetInstance()

