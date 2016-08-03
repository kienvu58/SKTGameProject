#include "GamePlayState.h"
#include "../GraphicsEngine/AnimationManager.h"
#include "../GraphicsEngine/TextManager.h"
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include "SingletonClasses.h"
#include <ctime>
#include "BeamWave.h"
#include "../GraphicsEngine/Globals.h"
#include "../GraphicsEngine/HelperFunctions.h"

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
	//update
	float attackingRadius = 2.0f;
	b2Vec2 distance;
	b2Vec2 goKuPosition = m_Goku->GetBody()->GetPosition();
	int i;
//	for (i = 0; i < m_vCurrentEntities.size(); i++)
//	{
//		m_vCurrentEntities[i]->Update();
////		distance = goKuPosition - m_vCurrentEntities[i]->GetBody()->GetPosition();
////		if (distance.Length() <= attackingRadius)
////		{
////			b2Vec2 goKuPosition = m_Goku->GetBody()->GetPosition();
////			Dispatcher->DispatchMessageA(SEND_MSG_IMMEDIATELY, Singleton<Game>::GetInstance(), m_vCurrentEntities[i],
////				MSG_CELLJR_INSIDE_ATTACK_RANGE, &goKuPosition);
////		}
//	}
	game->IncreasePlayingTime(Globals::deltaTime);
	game->UpdateDifficulty(m_Goku->GetCurrentScore());

	m_spawner.SpawnMinions();
	for (auto it : m_mapCurrentEntities)
	{
		for (int i=0; i<it.second->size(); i++)
			it.second->at(i)->Update();
	}

	for (auto it : m_vCurrentKiBlasts)
	{
		it->Update();
	}
	for (auto it : m_vCurrentBeamWaves)
	{
		it->Update();
	}
}

void GamePlayState::Exit(Game* game)
{
}

void GamePlayState::Render(Game* game)
{
	std::string currentScore = std::to_string(m_Goku->GetCurrentScore());
	std::string scoreText = "Score: ";
	scoreText.append(currentScore);
	TextMgr->RenderString(scoreText.c_str(), Vector4(1, 0, 0, 1), 60.0f, 0, 0, 1, 1);
	std::string playingTimeText = std::to_string(game->GetPlayingTime());
	playingTimeText.append(" s");
	TextMgr->RenderString(playingTimeText.c_str(), Vector4(1, 0, 0, 1), 60.0f, 200.0f, 0, 1, 1);
	std::string difficultyText = "Difficulty: ";
	difficultyText.append(std::to_string(game->GetDifficulty()));
	TextMgr->RenderString(difficultyText.c_str(), Vector4(1, 0, 0, 1), 60.0f, 500.0f, 0, 1, 1);

//	//generate minions by the number of minions in the screen.
//	int currentNumMinions = 100;
//	if (GetNumEntitiesByType(ENTITY_CELLJUNIOR) < currentNumMinions)
//	{
//		for (int i = 0; i < currentNumMinions - GetNumEntitiesByType(ENTITY_CELLJUNIOR); i++)
//		{
//			EntityMinion* entity;
//			entity = m_pMinionPool->GetEntity();
//			if (entity)
//			{
//				entity->GetBody()->SetActive(true);
//				entity->GetBody()->SetTransform(b2Vec2(10, (rand() - rand()) % 6), 0);
//				entity->GetBody()->SetLinearVelocity(b2Vec2(-4, 0));
//				AddEntitesToTheScreen(ENTITY_CELLJUNIOR, entity);
//			}
//		}
//	}

	//m_spawner.SpawnMinions(this);

	for(auto it : m_mapCurrentEntities)
	{
		for (int i=0; i<it.second->size();i++)
		{
			it.second->at(i)->Render();
		}
	}

	for (auto it : m_vCurrentKiBlasts)
	{
		it->Render();
	}

	for (auto it : m_vCurrentBeamWaves)
	{
		it->Render();
	}

	m_Goku->Render();
}

void GamePlayState::Init(const char* filePath)
{
	//read file here, then create bodies and fixtures for enities.
	Factory->Init("File path");
	m_spawner.Init("File path");
	m_Goku = dynamic_cast<EntityPlayer*>(Factory->GetPrototype(ENTITY_PLAYER));
	//Init for pools
	m_pMinionPool = new Pool<EntityMinion>();
	
	int nMaxMinions = 100;
	for (int i=0; i<nMaxMinions; i++)
	{
		EntityMinion* minion = dynamic_cast<EntityCellJunior*>(Factory->GetPrototype(ENTITY_CELLJUNIOR)->Clone());
		minion->GetBody()->SetTransform(b2Vec2(rand()%10, (rand()-rand())%6), 0);
		m_pMinionPool->Add(minion);
	}
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

	if(telegram.Message == MSG_MINION_OUT_OF_WALL)
	{
		EntityMinion *theMinion = static_cast<EntityMinion*>(telegram.ExtraInfo);
		theMinion->GetBody()->SetActive(false);
		RemoveEntitiesOnTheScreen(ENTITY_CELLJUNIOR, theMinion);
		m_spawner.ReaseMinions(theMinion);
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
	
	if (telegram.Message == MSG_SPAWN_TRUE_KAMEHAMEHA)
	{
		auto kamehamehaPosition = DereferenceToType<b2Vec2>(telegram.ExtraInfo);
		std::cout << "Spawn True Kamehameha at " << kamehamehaPosition.x << " " << kamehamehaPosition.y << std::endl;
		BeamWave* kamehameha = new BeamWave();
		kamehameha->InitSpriteHead(5, 43, 1);
		kamehameha->InitSpriteBody(5, 42, 1);
		kamehameha->InitSpriteTail(5, 41, 1);
		kamehameha->Fire(kamehamehaPosition);
		m_vCurrentBeamWaves.push_back(kamehameha);
		return true;
	}
	return false;
}

GamePlayState::~GamePlayState()
{
	delete m_pMinionPool;

	for (auto it : m_vCurrentKiBlasts)
	{
		delete it;
	}

	for (auto it : m_vCurrentBeamWaves)
	{
		delete it;
	}

	for (auto it: m_mapCurrentEntities)
	{
		delete it.second;
	}
}

void GamePlayState::AddEntitesToTheScreen(EntityType type, Entity* entity)
{
	auto it = m_mapCurrentEntities.find(type);
	if (it != m_mapCurrentEntities.end())
	{
		if (entity != nullptr)
		{
			auto it2 = std::find(it->second->begin(), it->second->end(), entity);
			if (it2 == it->second->end())
			{
				it->second->push_back(entity);
			}
		}
	}else
	{
		std::vector<Entity*>* vecEntity = new std::vector<Entity*>();
		vecEntity->push_back(entity);
		m_mapCurrentEntities.insert(std::pair<EntityType, std::vector<Entity*>*>(type, vecEntity));
	}
}

void GamePlayState::RemoveEntitiesOnTheScreen(EntityType type, Entity* entity)
{
	auto it = m_mapCurrentEntities.find(type);
	if (it != m_mapCurrentEntities.end())
	{
		RemoveFromVector<Entity*>(*(it->second), entity);
	}
}

void GamePlayState::AddEntitesToTheScreen(EntityType type, std::vector<Entity*> entities)
{
}

void GamePlayState::RemoveEntitiesOnTheScreen(EntityType type, std::vector<Entity*> entities)
{
}

int GamePlayState::GetNumEntitiesByType(EntityType type)
{
	auto it = m_mapCurrentEntities.find(type);
	if (it != m_mapCurrentEntities.end())
		return it->second->size();
	return 0;
}

int GamePlayState::GetNumAllEntities()
{
	int size = 0;
	for(auto it : m_mapCurrentEntities)
	{
		size += it.second->size();
	}
	return size;
}
