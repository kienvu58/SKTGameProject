#pragma once

#include <map>
#include "../Utilities/utilities.h"

#define KEY_A (1 << 0)
#define KEY_D (1 << 1)
#define KEY_W (1 << 2)
#define KEY_S (1 << 3)
#define KEY_J (1 << 4)
#define KEY_K (1 << 5)
#define KEY_L (1 << 6)
#define KEY_I (1 << 7)

class InputManager
{
public:
	InputManager();
	~InputManager();

	void SetKeyEvent(int key, bool isPressed);
	bool IsPressed(int key) const;
	void SetLastMousePosition(float x, float y);
	void SetCurrentMousePosition(float x, float y);
	void SetMouseDown(bool b);
	bool IsMouseDown() const;
	Vector2 GetLastMousePosition() const;
	Vector2 GetCurrentMousePosition() const;
	void ResetKeys();
	void AddTouchEvent(int pointerId, int actionType, int pointerX, int pointerY);
	Vector2 GetPointerPosition(int pointerId) const;
	const std::map<int, Vector2>* GetTouchEvents() const;
	void ClearTouchEvents();
private:
	int m_iKeyPressed;
	bool m_bIsMouseDown;
	Vector2 m_v2LastMousePos;
	Vector2 m_v2CurrentMousePos;

	std::map<int, Vector2> m_TouchEvents;
};
