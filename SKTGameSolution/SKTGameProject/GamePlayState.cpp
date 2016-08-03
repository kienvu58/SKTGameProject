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
	
	//update
	float attackingRadius = 4.0f;
	b2Vec2 distance;
	b2Vec2 goKuPosition = m_Goku->GetBody()->GetPosition();
	int i;
	std::vector<Entity*>* cellJuniors = GetEntitiesByType(ENTITY_CELLJUNIOR);

	if (cellJuniors) {
		for (i = 0; i < cellJuniors->size(); i++)
		{
			EntityCellJunior* cellJunior = dynamic_cast<EntityCellJunior*>(cellJuniors->at(i));
			distance = goKuPosition - cellJunior->GetBody()->GetPosition();
			if (distance.Length() <= attackingRadius
				&& cellJunior->GetFSM()->CurrentState() != CJS_Attacking::GetInstance())
			{
				b2Vec2 goKuPosition = m_Goku->GetBody()->GetPosition();
				Dispatcher->DispatchMessageA(SEND_MSG_IMMEDIATELY, Singleton<Game>::GetInstance(), cellJunior,
					MSG_CELLJR_INSIDE_ATTACK_RANGE, &goKuPosition);
			}
		}
	}

	m_Goku->Update();

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
}

bool GamePlayState::OnMessage(Game* game, const Telegram& telegram)
{
	if (telegram.Message == MSG_SPAWN_KI_BLAST)
	{
		auto kiBlastPosition = DereferenceToType<b2Vec2>(telegram.ExtraInfo);
		std::cout << "Spawn ki blast at " << kiBlastPosition.x << " " << kiBlastPosition.y << std::endl;
		KiBlast* kiBlast = dynamic_cast<KiBlast*>(Factory->GetPrototype(KI_BLAST)->Clone());;
		kiBlast->Fire(kiBlastPosition, 1);
		m_vCurrentKiBlasts.push_back(kiBlast);
		return true;
	}

	if(telegram.Message == MSG_MINION_OUT_OF_WALL)
	{
		EntityMinion *theMinion = static_cast<EntityMinion*>(telegram.ExtraInfo);
		theMinion->GetBody()->SetActive(false);
		RemoveEntitiesOnTheScreen(theMinion->GetType(), theMinion);
		m_spawner.RealeaseMinions(theMinion);
		std::cout << "out of wall .\n";
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

std::vector<Entity*>* GamePlayState::GetEntitiesByType(EntityType type)
{
	auto it = m_mapCurrentEntities.find(type);
	if (it != m_mapCurrentEntities.end())
	{
		return it->second;
	}
	return nullptr;
}

EntityPlayer* GamePlayState::GetPlayer() const
{
	return m_Goku;
}
