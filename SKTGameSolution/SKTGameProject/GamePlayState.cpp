#include "GamePlayState.h"
#include "../GraphicsEngine/AnimationManager.h"
#include "../GraphicsEngine/TextManager.h"
#include <Box2D/Dynamics/b2Fixture.h>
#include "SingletonClasses.h"
#include <ctime>
#include "EntityBeamWave.h"
#include "../GraphicsEngine/Globals.h"
#include "../GraphicsEngine/HelperFunctions.h"
#include "EntityKiBlast.h"

GamePlayState::GamePlayState()
{
}

void GamePlayState::Enter(Game* game)
{
}

void GamePlayState::PressButton(Game* game)
{
	if (InputMgr->GetLastMousePosition().x >= 1069.0f && InputMgr->GetLastMousePosition().x <= 1111.0f
		&& InputMgr->GetLastMousePosition().y >= 9.0f && InputMgr->GetLastMousePosition().y <= 51.0f)
	{
		//GamePause
		MusicMgr->MusicPause("GamePlay");
//		printf("GamePause\n");
		game->GetFSM()->ChangeState(GS_Pause::GetInstance());
	}
}

void GamePlayState::Execute(Game* game)
{
	srand(time(nullptr));
	PhysicsMgr->Update();
	m_Button_Pause->Update();
	m_Background->Update();

	//update
	float attackingRadius = 3.0f;
	b2Vec2 distance;
	b2Vec2 goKuPosition = m_Player->GetBody()->GetPosition();
	int i;
	std::vector<Entity*>* cellJuniors = GetEntitiesByType(ENTITY_CELLJUNIOR);

	if (cellJuniors)
	{
		for (i = 0; i < cellJuniors->size(); i++)
		{
			EntityCellJunior* cellJunior = static_cast<EntityCellJunior*>(cellJuniors->at(i));
			distance = goKuPosition - cellJunior->GetBody()->GetPosition();
			if (distance.Length() <= attackingRadius
				&& cellJunior->GetFSM()->CurrentState() != CJS_Attacking::GetInstance())
			{
				b2Vec2 goKuPosition = m_Player->GetBody()->GetPosition();
				Dispatcher->DispatchMessageA(GameInstance, cellJunior, MSG_CELLJR_INSIDE_ATTACK_RANGE, &goKuPosition);
			}
		}
	}

	m_Player->Update();

	game->IncreasePlayingTime(Globals::deltaTime);
	game->UpdateDifficulty(m_Player->GetCurrentScore());

	m_spawner.SpawnMinions();
	for (auto it : m_mapCurrentEntities)
	{
		for (int i = 0; i < it.second->size(); i++)
			it.second->at(i)->Update();
	}

	PressButton(game);
}

void GamePlayState::Exit(Game* game)
{
}

void GamePlayState::Render(Game* game)
{
	m_Background->Render();
	m_Button_Pause->Render();
	std::string currentScore = std::to_string(m_Player->GetCurrentScore());
	std::string scoreText = "Score: ";
	scoreText.append(currentScore);
	TextMgr->RenderString(scoreText.c_str(), Vector4(1, 0, 0, 1), 60.0f, 0, 0, 1, 1);
	std::string playingTimeText = std::to_string(game->GetPlayingTime());
	playingTimeText.append(" s");
	TextMgr->RenderString(playingTimeText.c_str(), Vector4(1, 0, 0, 1), 60.0f, 200.0f, 0, 1, 1);
	std::string difficultyText = "Difficulty: ";
	difficultyText.append(std::to_string(game->GetDifficulty()));
	TextMgr->RenderString(difficultyText.c_str(), Vector4(1, 0, 0, 1), 60.0f, 500.0f, 0, 1, 1);
	std::string currentHealth = "Health: ";
	currentHealth.append(std::to_string(m_Player->GetCurrentHealth()));
	TextMgr->RenderString(currentHealth.c_str(), Vector4(1, 0, 0, 1), 60.0f, 0.0f, 30.0f, 1, 1);

	for (auto it : m_mapCurrentEntities)
	{
		for (int i = 0; i < it.second->size(); i++)
		{
			it.second->at(i)->Render();
		}
	}

	m_Player->Render();
}

void GamePlayState::Init(const char* filePath)
{
	m_Background = new EntityStatic();
	m_Background->InitSprite(2, 106, 1);

	m_Button_Pause = new EntityStatic();
	m_Button_Pause->InitSprite(5, 115, 1);
	m_Button_Pause->InitPosition(1090, 30);


	m_spawner.Init("File path");



	m_Player = static_cast<EntityPlayer*>(Factory->GetPrototypeById(1));

	MusicMgr->MusicVolume("GamePlay", 50);
}

bool GamePlayState::OnMessage(Game* game, const Telegram& telegram)
{
	if (telegram.Message == MSG_MINION_OUT_OF_WALL)
	{
		EntityMinion* theMinion = static_cast<EntityMinion*>(telegram.ExtraInfo);
		theMinion->Reset();
		RemoveEntityFromTheScreen(theMinion);
		return true;
	}

	if (telegram.Message == MSG_CLEAN_UP)
	{
		EntityKiBlast* theKiBlast = static_cast<EntityKiBlast*>(telegram.ExtraInfo);
		RemoveEntityFromTheScreen(theKiBlast);
		return true;
	}

	return false;
}

GamePlayState::~GamePlayState()
{
	delete m_Button_Pause;
	delete m_Background;

	for (auto it: m_mapCurrentEntities)
	{
		delete it.second;
	}
}

void GamePlayState::AddEntityToTheScreen(Entity* entity)
{
	auto prototypeId = entity->GetPrototypeId();
	auto pair = m_mapCurrentEntities.find(prototypeId);
	if (pair != m_mapCurrentEntities.end())
	{
		if (entity != nullptr)
		{
			auto it2 = std::find(pair->second->begin(), pair->second->end(), entity);
			if (it2 == pair->second->end())
			{
				pair->second->push_back(entity);
			}
		}
	}
	else
	{
		std::vector<Entity*>* vecEntity = new std::vector<Entity*>();
		vecEntity->push_back(entity);
		m_mapCurrentEntities.insert(std::pair<int, std::vector<Entity*>*>(prototypeId, vecEntity));
	}
}

void GamePlayState::RemoveEntityFromTheScreen(Entity* entity)
{
	auto prototypeId = entity->GetPrototypeId();
	auto pair = m_mapCurrentEntities.find(prototypeId);
	if (pair != m_mapCurrentEntities.end())
	{
		PoolMgr->ReleaseEntity(entity);
		RemoveFromVector<Entity*>(*(pair->second), entity);
	}
}

int GamePlayState::GetNumberOfEntitiesByPrototypeId(int prototypeId)
{
	auto pair = m_mapCurrentEntities.find(prototypeId);
	if (pair != m_mapCurrentEntities.end())
		return pair->second->size();
	return 0;
}

int GamePlayState::GetNumberOfAllEntities()
{
	auto size = 0;
	for (auto pair : m_mapCurrentEntities)
	{
		size += pair.second->size();
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
	return m_Player;
}
