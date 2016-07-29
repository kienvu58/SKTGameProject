#include "InputManager.h"


Vector2 InputManager::GetCurrentMousePosition()
{
	return m_v2CurrentMousePos;
}

InputManager::InputManager(): m_iKeyPressed(0)
{
}


InputManager::~InputManager()
{
}

void InputManager::SetKeyEvent(int key, bool isPressed)
{
	if (isPressed)
	{
		m_iKeyPressed |= key;
	}
	else
	{
		m_iKeyPressed &= ~key;
	}
}

bool InputManager::IsPressed(int key) const
{
	return m_iKeyPressed & key;
}

void InputManager::SetLastMousePosition(int x, int y)
{
	m_v2LastMousePos = Vector2(x, y);
}

void InputManager::SetCurrentMousePosition(int x, int y)
{
	m_v2CurrentMousePos = Vector2(x, y);
}

Vector2 InputManager::GetLastMousePosition()
{
	return m_v2LastMousePos;
}
