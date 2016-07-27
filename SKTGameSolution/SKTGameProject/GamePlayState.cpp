#include "GamePlayState.h"
#include "../GraphicsEngine/ResourceManager.h"
#include "../GraphicsEngine/AnimationManager.h"
#include "../GraphicsEngine/FrameManager.h"
#include "../GraphicsEngine/TextManager.h"
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include "PhysicsManager.h"

static Sprite spriteGoku;

GamePlayState::GamePlayState()
{
}

void GamePlayState::Enter(Game* game)
{

}

void GamePlayState::Execute(Game* game)
{
	PhysicsMgr->Update();
	//m_Background->Update();
	m_Goku->Update();
	//m_pButton->Update();
}

void GamePlayState::Exit(Game* game)
{
}

void GamePlayState::Render(Game* game)
{
	//m_Background->Render();
	m_Goku->Render();
	TextMgr->RenderString("Test Game", Vector4(1, 0, 0, 1), 60.0f, 0, 0, 1, 1);
//	m_pButton->Render();
	//m_pTestMinion->Render();
}

GamePlayState* GamePlayState::GetInstance()
{
	static GamePlayState instance;
	return &instance;
}

void GamePlayState::Clear()
{
	delete m_Background;
	delete m_Goku;
	delete m_pButton;
	delete m_pTestMinion;
}

void GamePlayState::Init(const char* filePath)
{
	m_Goku = new EntityPlayer();
	m_Goku->InitSprite(1, 1, 1);
	m_Goku->SetSpriteData(38, Vector2());

	//read file here, then create bodies and fixtures for enities.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2(1, 2);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(MetersFromPixels(128) / 2 / 2, MetersFromPixels(128) / 2 / 2);

	b2FixtureDef fixture;
	fixture.shape = &boxShape;
	fixture.restitution = 1.0f;

	m_Goku->InitBody(bodyDef, fixture);

	/*m_pTestMinion = new EntityMinion();
	m_pTestMinion->InitSprite(1, 1, 1);
	m_pTestMinion->SetSpriteData(38, Vector2(110, 0));
	m_Background = new EntityPlayer();
	m_Background->InitSprite(2, 2, 1);
	m_pButton = new EntityPlayer();
	m_pButton->InitSprite(3, 3, 1);*/

}

GamePlayState::~GamePlayState()
{
}
