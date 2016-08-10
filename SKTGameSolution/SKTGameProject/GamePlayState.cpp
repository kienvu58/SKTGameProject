#include "GamePlayState.h"
#include "../GraphicsEngine/AnimationManager.h"
#include "../GraphicsEngine/TextManager.h"
#include <Box2D/Dynamics/b2Fixture.h>
#include "SingletonClasses.h"
#include <ctime>
#include "EntityBeamWave.h"
#include "../GraphicsEngine/Globals.h"
#include "../GraphicsEngine/HelperFunctions.h"

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

	//update
	float attackingRadius = 3.0f;
	b2Vec2 distance;
	b2Vec2 goKuPosition = m_Goku->GetBody()->GetPosition();
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
				b2Vec2 goKuPosition = m_Goku->GetBody()->GetPosition();
				Dispatcher->DispatchMessageA(GameInstance, cellJunior, MSG_CELLJR_INSIDE_ATTACK_RANGE, &goKuPosition);
			}
		}
	}

	m_Goku->Update();

	game->IncreasePlayingTime(Globals::deltaTime);
	game->UpdateDifficulty(m_Goku->GetCurrentScore());

	m_spawner.SpawnMinions();
	for (auto it : m_mapCurrentEntities)
	{
		for (int i = 0; i < it.second->size(); i++)
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
	std::string currentHealth = "Health: ";
	currentHealth.append(std::to_string(m_Goku->GetCurrentHealth()));
	TextMgr->RenderString(currentHealth.c_str(), Vector4(1, 0, 0, 1), 60.0f, 0.0f, 30.0f, 1, 1);

	for (auto it : m_mapCurrentEntities)
	{
		for (int i = 0; i < it.second->size(); i++)
		{
			it.second->at(i)->Render();
		}
	}

	for (auto it : m_vCurrentBeamWaves)
	{
		it->Render();
	}
	m_Goku->Render();
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

	Factory->Init("File path");
	m_spawner.Init("File path");
	m_Goku = static_cast<EntityPlayer*>(Factory->GetPrototype(ENTITY_PLAYER));

	MusicMgr->MusicVolume("GamePlay", 50);
}

bool GamePlayState::OnMessage(Game* game, const Telegram& telegram)
{
	if (telegram.Message == MSG_SPAWN_KI_BLAST)
	{
		auto kiBlastPosition = DereferenceToType<b2Vec2>(telegram.ExtraInfo);
		EntityKiBlast* kiBlast = static_cast<EntityKiBlast*>(PoolMgr->GetEntityByType(KI_BLAST));
		kiBlast->Fire(kiBlastPosition, 1);
		AddEntitesToTheScreen(kiBlast);
		return true;
	}

	if (telegram.Message == MSG_MINION_OUT_OF_WALL)
	{
		EntityMinion* theMinion = static_cast<EntityMinion*>(telegram.ExtraInfo);
		theMinion->Reset();
		RemoveEntitiesOnTheScreen(theMinion);
		return true;
	}

	if (telegram.Message == MSG_KIBLAST_OUT_OF_WALL)
	{
		EntityKiBlast* theKiBlast = static_cast<EntityKiBlast*>(telegram.ExtraInfo);
		RemoveEntitiesOnTheScreen(theKiBlast);
		return true;
	}

	if (telegram.Message == MSG_SPAWN_KAMEHAMEHA)
	{
		auto kamehamehaPosition = DereferenceToType<b2Vec2>(telegram.ExtraInfo);
		std::cout << "Spawn Kamehameha at " << kamehamehaPosition.x << " " << kamehamehaPosition.y << std::endl;
		EntityBeamWave* kamehameha = new EntityBeamWave();
		kamehameha->InitSpriteHead(4, 84, 1);
		kamehameha->InitSpriteBody(4, 83, 1);
		kamehameha->InitSpriteTail(4, 82, 1);
		kamehameha->Fire(kamehamehaPosition);
		m_vCurrentBeamWaves.push_back(kamehameha);
		return true;
	}

	if (telegram.Message == MSG_SPAWN_TRUE_KAMEHAMEHA)
	{
		auto kamehamehaPosition = DereferenceToType<b2Vec2>(telegram.ExtraInfo);
		std::cout << "Spawn True Kamehameha at " << kamehamehaPosition.x << " " << kamehamehaPosition.y << std::endl;
		EntityBeamWave* kamehameha = new EntityBeamWave();
		kamehameha->InitSpriteHead(8, 39, 1);
		kamehameha->InitSpriteBody(8, 38, 1);
		kamehameha->InitSpriteTail(8, 37, 1);
		kamehameha->Fire(kamehamehaPosition);
		m_vCurrentBeamWaves.push_back(kamehameha);
		return true;
	}
	return false;
}

GamePlayState::~GamePlayState()
{
	delete m_Button_Pause;
	delete m_Background;
	delete m_Background_Clone;

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

void GamePlayState::AddEntitesToTheScreen(Entity* entity)
{
	EntityType type = entity->GetType();
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
	}
	else
	{
		std::vector<Entity*>* vecEntity = new std::vector<Entity*>();
		vecEntity->push_back(entity);
		m_mapCurrentEntities.insert(std::pair<EntityType, std::vector<Entity*>*>(type, vecEntity));
	}
}

void GamePlayState::RemoveEntitiesOnTheScreen(Entity* entity)
{
	EntityType type = entity->GetType();
	auto it = m_mapCurrentEntities.find(type);
	if (it != m_mapCurrentEntities.end())
	{
		PoolMgr->ReleaseEntity(entity);
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
	for (auto it : m_mapCurrentEntities)
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
