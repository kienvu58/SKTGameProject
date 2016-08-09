#pragma once
#include <Common/FSM/State.h>
#include "Game.h"
#include "EntityStatic.h"
#include "EntityLiving.h"


class GameOptionState : public State<Game>
{
public:
	GameOptionState();
	~GameOptionState();

	void Enter(Game* game) override;
	void PressButton(Game* game);
	void Execute(Game* game) override;
	void Exit(Game* game) override;
	void Render(Game* game) override;
	void Init(const char* filePath);


	bool OnMessage(Game*, const Telegram&) override;
private:
	EntityStatic *m_Background;
	EntityStatic *m_Button_V;
	EntityStatic *m_Button_X;
	EntityStatic *m_MusicBarGreen;
	EntityStatic *m_MusicBarBlack;
	Vector2 MusicBarBlack;

};

