#include "GamePlayState.h"
#include "../GraphicsEngine/AnimationManager.h"
#include "../GraphicsEngine/TextManager.h"
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include "SingletonClasses.h"
#include <ctime>

GamePlayState::GamePlayState()
{
}

void GamePlayState::Enter(Game* game)
{
}

void GamePlayState::Execute(Game* game)
{
	srand(time(nullptr));
	PhysicsMgr->Update();
	m_Goku->Update();
	m_pTestMinion->Update();
	m_pCloneMinion->Update();
	//update
	for (int i = 0; i < m_vCurrentEntities.size(); i++)
	{
		m_vCurrentEntities[i]->Update();
	}
	for (auto it : m_vCurrentKiBlasts)
	{
		it->Update();
	}
}

void GamePlayState::Exit(Game* game)
{
}

void GamePlayState::Render(Game* game)
{
	m_Goku->Render();
	TextMgr->RenderString("Test Game", Vector4(1, 0, 0, 1), 60.0f, 0, 0, 1, 1);
	//m_pTestMinion->Render();

	//generate minions by the number of minions in the screen.
	int currentNumMinions = 10;
	if (m_vCurrentEntities.size() < currentNumMinions)
	{
		for (int i = 0; i < currentNumMinions - m_vCurrentEntities.size(); i++)
		{
			EntityMinion* entity;
			entity = m_pMinionPool->GetEntity();
			if (entity)
				m_vCurrentEntities.push_back(entity);
		}
	}

	//render
	for (auto it : m_vCurrentEntities)
	{
		it->Render();
	}

	for (auto it : m_vCurrentKiBlasts)
	{
		it->Render();
	}

	m_pTestMinion->Render();
	m_pCloneMinion->Render();
}

void GamePlayState::Init(const char* filePath)
{
	//read file here, then create bodies and fixtures for enities.
	m_PFactory = new FactoryEntity();
	m_PFactory->Init("file path");

	m_Goku = dynamic_cast<EntityPlayer*>(m_PFactory->GetPrototype(ENTITY_PLAYER));

	m_pTestMinion = dynamic_cast<EntityCellJunior*>(m_PFactory->GetPrototype(ENTITY_CELLJUNIOR)->Clone());
	m_pCloneMinion = m_pTestMinion->Clone();

	//Init for pools
	m_pMinionPool = new Pool<EntityMinion>();

	int nMaxMinions = 10;
	for (int i=0; i<nMaxMinions; i++)
	{
		EntityMinion* minion = dynamic_cast<EntityCellJunior*>(m_PFactory->GetPrototype(ENTITY_CELLJUNIOR)->Clone());
		m_pMinionPool->Add(minion);
	}
}

void GamePlayState::Update()
{
}

void GamePlayState::Render()
{
}

Entity* GamePlayState::Clone()
{
	return nullptr;
}

EntityType GamePlayState::GetType()
{
	return GOD;
}

bool GamePlayState::HandleMessage(const Telegram& telegram)
{
	if (telegram.Message == MSG_SPAWN_KI_BLAST)
	{
		auto kiBlastPosition = DereferenceToType<b2Vec2>(telegram.ExtraInfo);
		std::cout << "Spawn ki blast at " << kiBlastPosition.x << " " << kiBlastPosition.y << std::endl;
		KiBlast* kiBlast = new KiBlast();

		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;

		b2PolygonShape boxShape;
		boxShape.SetAsBox(MetersFromPixels(24), MetersFromPixels(12));

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &boxShape;
		fixtureDef.restitution = 1.0f;
		fixtureDef.isSensor = true;

		kiBlast->InitBody(bodyDef, fixtureDef);
		kiBlast->InitSprite(4, 36, 1);
		kiBlast->Fire(kiBlastPosition, 1);
		m_vCurrentKiBlasts.push_back(kiBlast);
		return true;
	}
	return false;
}

GamePlayState::~GamePlayState()
{
	delete m_PFactory;
	delete m_pTestMinion;
	delete m_pCloneMinion;
	delete m_pMinionPool;

	for (auto it : m_vCurrentKiBlasts)
	{
		delete it;
	}
}
