#include "GamePlayState.h"
#include "../GraphicsEngine/AnimationManager.h"
#include "../GraphicsEngine/TextManager.h"
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include "SingletonClasses.h"
#include <ctime>
#include "BeamWave.h"

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
	m_Button_Pause->Update();
	m_Background->Update();
	//	m_pTestMinion->Update();
	//m_pCloneMinion->Update();
	//update
	for (int i = 0; i < m_vCurrentEntities.size(); i++)
	{
		m_vCurrentEntities[i]->Update();
	}
	for (auto it : m_vCurrentKiBlasts)
	{
		it->Update();
	}
	for (auto it : m_vCurrentBeamWaves)
	{
		it->Update();
	}
//	printf("%f | %f \n", InputMgr->GetLastMousePosition().x, InputMgr->GetLastMousePosition().y);
	if (InputMgr->GetLastMousePosition().x >= 1069.0f && InputMgr->GetLastMousePosition().x <= 1111.0f
		&& InputMgr->GetLastMousePosition().y >= 9.0f && InputMgr->GetLastMousePosition().y <= 51.0f)
	{
		//GamePause
		MusicMgr->MusicStop("GamePlay");
		printf("GamePause\n");
		game->GetFSM()->ChangeState(GS_Pause::GetInstance());
	}
}

void GamePlayState::Exit(Game* game)
{
}

void GamePlayState::Render(Game* game)
{
	m_Background->Render();
	m_Goku->Render();
	m_Button_Pause->Render();
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
			{
				entity->GetBody()->SetTransform(b2Vec2(10, (rand() - rand()) % 6), 0);
				entity->GetBody()->SetLinearVelocity(b2Vec2(-4, 0));
				m_vCurrentEntities.push_back(entity);
			}
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

	for (auto it : m_vCurrentBeamWaves)
	{
		it->Render();
	}

	//	m_pTestMinion->Render();
	//	m_pCloneMinion->Render();
}

void GamePlayState::Init(const char* filePath)
{
	m_Background = new EntityStatic();
	m_Background->InitSprite(2, 47, 1);
	//read file here, then create bodies and fixtures for enities.
	m_PFactory = new FactoryEntity();
	m_PFactory->Init("file path");

	m_Goku = dynamic_cast<EntityPlayer*>(m_PFactory->GetPrototype(ENTITY_PLAYER));

	//	m_pTestMinion = dynamic_cast<EntityCellJunior*>(m_PFactory->GetPrototype(ENTITY_CELLJUNIOR)->Clone());
	//	m_pCloneMinion = m_pTestMinion->Clone();

	//Init for pools
	m_pMinionPool = new Pool<EntityMinion>();

	int nMaxMinions = 10;
	for (int i = 0; i < nMaxMinions; i++)
	{
		EntityMinion* minion = dynamic_cast<EntityCellJunior*>(m_PFactory->GetPrototype(ENTITY_CELLJUNIOR)->Clone());
		minion->GetBody()->SetTransform(b2Vec2(rand() % 10, (rand() - rand()) % 6), 0);
		//		minion->GetBody()->SetTransform(b2Vec2(0, 0), 0);
		m_pMinionPool->Add(minion);
	}

	m_Button_Pause = new EntityStatic();
	m_Button_Pause->InitSprite(5, 45, 1);
	m_Button_Pause->InitPosition(1090, 30);
}

bool GamePlayState::OnMessage(Game* game, const Telegram& telegram)
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

	if (telegram.Message == MSG_MINION_OUT_OF_WALL)
	{
		EntityMinion* theMinion = static_cast<EntityMinion*>(telegram.ExtraInfo);
		auto it = std::find(m_vCurrentEntities.begin(), m_vCurrentEntities.end(), theMinion);
		if (it != m_vCurrentEntities.end())
		{
			std::swap(*it, m_vCurrentEntities.back());
			m_vCurrentEntities.pop_back();
		}
		m_pMinionPool->ReleaseEntity(theMinion);

		return true;
	}

	if (telegram.Message == MSG_SPAWN_KAMEHAMEHA)
	{
		auto kamehamehaPosition = DereferenceToType<b2Vec2>(telegram.ExtraInfo);
		std::cout << "Spawn Kamehameha at " << kamehamehaPosition.x << " " << kamehamehaPosition.y << std::endl;
		BeamWave* kamehameha = new BeamWave();
		kamehameha->InitSpriteHead(4, 40, 1);
		kamehameha->InitSpriteBody(4, 39, 1);
		kamehameha->InitSpriteTail(4, 38, 1);
		kamehameha->Fire(kamehamehaPosition);
		m_vCurrentBeamWaves.push_back(kamehameha);
		return true;
	}
	return false;
}

GamePlayState::~GamePlayState()
{
	delete m_PFactory;
	delete m_Button_Pause;
	delete m_Background;
	//	delete m_pTestMinion;
	//	delete m_pCloneMinion;
	delete m_pMinionPool;

	for (auto it : m_vCurrentKiBlasts)
	{
		delete it;
	}

	for (auto it : m_vCurrentBeamWaves)
	{
		delete it;
	}
}
