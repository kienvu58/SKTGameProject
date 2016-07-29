#pragma once

#include "../Utilities/Math.h"

#define KEY_A (1 << 0)
#define KEY_D (1 << 1)
#define KEY_W (1 << 2)
#define KEY_S (1 << 3)
#define KEY_J (1 << 4)
#define KEY_K (1 << 5)
#define KEY_L (1 << 6)

class InputManager
{
public:
	InputManager();
	~InputManager();

	void SetKeyEvent(int key, bool isPressed);
	bool IsPressed(int key) const;
	void SetLastMousePosition(int x, int y);
	void SetCurrentMousePosition(int x, int y);
	Vector2 GetLastMousePosition();
	Vector2 GetCurrentMousePosition();
private:
	int m_iKeyPressed;
	Vector2 m_v2LastMousePos;
	Vector2 m_v2CurrentMousePos;
};

