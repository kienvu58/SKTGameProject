#include "InputManager.h"
#include "Globals.h"

InputManager* InputManager::s_Instance = nullptr;

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

InputManager* InputManager::GetInstance()
{
	if (s_Instance == nullptr)
	{
		s_Instance = new InputManager();
	}
	return s_Instance;
}

void InputManager::DestroyInstance()
{
	if (s_Instance != nullptr)
	{
		delete s_Instance;
		s_Instance = nullptr;
	}
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
