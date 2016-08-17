#include "InputManager.h"
#include "Globals.h"


InputManager::InputManager(): m_iKeyPressed(0),
                              m_bIsMouseDown(false)
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
	return bool(m_iKeyPressed & key);
}

void InputManager::SetLastMousePosition(float x, float y)
{
	m_v2LastMousePos = Vector2(x, y);
}

void InputManager::SetCurrentMousePosition(float x, float y)
{
	m_v2CurrentMousePos = Vector2(x, y);
}

Vector2 InputManager::GetLastMousePosition() const
{
	return m_v2LastMousePos;
}

Vector2 InputManager::GetCurrentMousePosition() const
{
	return m_v2CurrentMousePos;
}

void InputManager::SetMouseDown(bool b)
{
	m_bIsMouseDown = b;
}

bool InputManager::IsMouseDown() const
{
	return m_bIsMouseDown;
}

void InputManager::ResetKeys()
{
	m_iKeyPressed = 0;
}

void InputManager::AddTouchEvent(int pointerId, int actionType, int pointerX, int pointerY)
{
	if (actionType == Globals::TOUCH_ACTION_UP) {
		m_TouchEvents.erase(pointerId);
	}
	else {
		Vector2 pointerPos(pointerX, pointerY);
		m_TouchEvents[pointerId] = pointerPos;
	}
}

Vector2 InputManager::GetPointerPosition(int pointerId) const
{
	auto it = m_TouchEvents.find(pointerId);
	if (it != m_TouchEvents.end())
	{
		return it->second;
	}
	return Vector2(-1, -1);
}

const std::map<int, Vector2>* InputManager::GetTouchEvents() const
{
	return &m_TouchEvents;
}

void InputManager::ClearTouchEvents()
{
	m_TouchEvents.clear();
}
