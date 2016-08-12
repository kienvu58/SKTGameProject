#pragma once
#include <Common/FSM/State.h>
#include "Game.h"
#include "EntityStatic.h"

class GamePauseState : public State<Game>
{
public:
	GamePauseState();
	~GamePauseState();

	void Enter(Game* game) override;
	static void PressButton(Game* game);
	void Execute(Game* game) override;
	void Exit(Game* game) override;
	void Render(Game* game) override;
	void Init(const char* filePath);

	bool OnMessage(Game*, const Telegram&) override;
private:
	EntityStatic *m_Background;
	EntityStatic *m_Button_Resume;
	EntityStatic *m_Button_Quit;
};

