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

GamePlayState::GamePlayState(): m_iScore(0) {
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
	if(i==-560)
	{
		i = 1680;
	}
	if(j==-560)
	{
		j = 1680;
	}
	m_Background->InitPosition(i--, 315);
	m_Background_Clone->InitPosition(j--, 315);
	srand(time(nullptr));
	PhysicsMgr->Update();
	m_Button_Pause->Update();
	m_Background->Update();
	m_Background_Clone->Update();

	m_Player->Update();

	game->IncreasePlayingTime(Globals::deltaTime);
	game->UpdateDifficulty(m_iScore);

	m_spawner.SpawnMinions();
	for (auto pair : m_mapCurrentEntities)
	{
		for (auto entity : pair.second)
			entity->Update();
	}

	PressButton(game);
}

void GamePlayState::Exit(Game* game)
{
}

void GamePlayState::Render(Game* game)
{
	m_Background->Render();
	m_Background_Clone->Render();
	m_Button_Pause->Render();
	std::string currentScore = std::to_string(m_iScore);
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

	for (const auto& pair : m_mapCurrentEntities)
	{
		for (auto entity : pair.second)
		{
			entity->Render();
		}
	}

	m_Player->Render();
}

void GamePlayState::Init(const char* filePath)
{
	m_Background = new EntityStatic();
	//m_Background->InitSprite(2, 106, 1);
	m_Background->InitSprite(100, 200, 1);

	m_Background_Clone = new EntityStatic();
	m_Background_Clone->InitSprite(100, 201, 1);
	m_Background_Clone->InitPosition(1120+1120/2, 315);

	m_Button_Pause = new EntityStatic();
	m_Button_Pause->InitSprite(5, 115, 1);
	m_Button_Pause->InitPosition(1090, 30);


	m_spawner.Init("File path");



	m_Player = static_cast<EntityPlayer*>(Factory->GetPrototypeById(1));
	m_Player->Activate();

	MusicMgr->MusicVolume("GamePlay", 50);
}

bool GamePlayState::OnMessage(Game* game, const Telegram& telegram)
{
	if (telegram.Message == MSG_CLEAN_UP)
	{
		Entity* entity = static_cast<Entity*>(telegram.ExtraInfo);
		RemoveEntityFromTheScreen(entity);
		return true;
	}

	return false;
}

GamePlayState::~GamePlayState()
{
	delete m_Button_Pause;
	delete m_Background;
	delete m_Background_Clone;
}

void GamePlayState::AddEntityToTheScreen(Entity* entity)
{
	auto prototypeId = entity->GetPrototypeId();
	auto pair = m_mapCurrentEntities.find(prototypeId);
	if (pair != m_mapCurrentEntities.end())
	{
		if (entity != nullptr)
		{
			auto it2 = std::find(pair->second.begin(), pair->second.end(), entity);
			if (it2 == pair->second.end())
			{
				pair->second.push_back(entity);
			}
		}
	}
	else
	{
		std::vector<Entity*> vecEntity;
		vecEntity.push_back(entity);
		m_mapCurrentEntities.insert(std::pair<int, std::vector<Entity*>>(prototypeId, vecEntity));
	}
}

void GamePlayState::RemoveEntityFromTheScreen(Entity* entity)
{
	auto prototypeId = entity->GetPrototypeId();
	auto pair = m_mapCurrentEntities.find(prototypeId);
	if (pair != m_mapCurrentEntities.end())
	{
		PoolMgr->ReleaseEntity(entity);
		RemoveFromVector<Entity*>(pair->second, entity);
	}
}

int GamePlayState::GetNumberOfEntitiesByPrototypeId(int prototypeId)
{
	auto pair = m_mapCurrentEntities.find(prototypeId);
	if (pair != m_mapCurrentEntities.end())
		return pair->second.size();
	return 0;
}

int GamePlayState::GetNumberOfAllEntities()
{
	auto size = 0;
	for (auto pair : m_mapCurrentEntities)
	{
		size += pair.second.size();
	}
	return size;
}

std::vector<Entity*>* GamePlayState::GetEntitiesByType(EntityType type)
{
	auto pair = m_mapCurrentEntities.find(type);
	if (pair != m_mapCurrentEntities.end())
	{
		return &pair->second;
	}
	return nullptr;
}

EntityPlayer* GamePlayState::GetPlayer() const
{
	return m_Player;
}

void GamePlayState::IncreaseScore(int amount)
{
	m_iScore += amount;
}

void GamePlayState::Reset()
{
	m_iScore = 0;
	m_Player->Reset();
}
