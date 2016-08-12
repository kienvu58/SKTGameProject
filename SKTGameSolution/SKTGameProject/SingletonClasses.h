#pragma once
#include <Singleton.hpp>
#include "../GraphicsEngine/InputManager.h"
#include "../GraphicsEngine/FrameManager.h"
#include "../GraphicsEngine/AnimationManager.h"
#include "../GraphicsEngine/ResourceManager.h"
#include "../GraphicsEngine/TextManager.h"
#include "PhysicsManager.h"
#include "PlayerOwnedStates.h"
#include "MinionOwnedStates.h"
#include "GameWelcomeState.h"
#include "GamePlayState.h"
#include "MainMenuState.h"
#include "GameOptionState.h"
#include "MessageDispatcher.h"
#include "SoundManager.h"
#include "GamePauseState.h"
#include "CellJuniorOwnedStates.h"
#include "FactoryEntity.h"
#include "PoolManager.h"
#include "GameOverState.h"
#include "CellOwnedStates.h"


class GamePlayState;
// Game
typedef Singleton<Game> GameSingleton;

//// Clock
//typedef Singleton<CrudeTimer> CrudeTimerSingleton;

// Message Dispatcher
typedef Singleton<MessageDispatcher> MessageDispatcherSingleton;

// Managers
typedef Singleton<InputManager> InputManagerSingleton;
typedef Singleton<FrameManager> FrameManagerSingleton;
typedef Singleton<AnimationManager> AnimationManagerSingleton;
typedef Singleton<ResourceManager> ResourceManagerSingleton;
typedef Singleton<TextManager> TextManagerSingleton;
typedef Singleton<PhysicsManager> PhysicsManagerSingleton;
typedef Singleton<SoundManager> MusicManagerSingleton;

// Player States
typedef Singleton<PlayerStandingState> PS_Standing;
typedef Singleton<PlayerMovingState> PS_Moving;
typedef Singleton<PlayerFiringState> PS_Firing;
typedef Singleton<PlayerFiringSpecialState> PS_FiringSpecial;
typedef Singleton<PlayerFiringUltimateState> PS_FiringUltimate;
typedef Singleton<PlayerGlobalState> PS_Global;
typedef Singleton<PlayerTakingDamageState> PS_TakingDamage;
typedef Singleton<PlayerFallingToDead> PS_FallToDead;
typedef Singleton<PlayerChargingState> PS_Charging;

// Minion States
typedef Singleton<WanderingState> MS_Wandering;
typedef Singleton<MinionGlobalState> MS_Global;

// CellJunior States
typedef Singleton<CellJuniorGlobalState> CJS_Global;
typedef Singleton<CellJuniorWanderingState> CJS_Wandering;
typedef Singleton<CellJuniorAttackingState> CJS_Attacking;

// Cell States
typedef Singleton<CellGlobalState> CS_Global;
typedef Singleton<CellWanderingState> CS_Wandering;
typedef Singleton<CellAttackingState> CS_Attacking;
typedef Singleton<CellDodgingState> CS_Dodging;

// Game States
typedef Singleton<GameWelcomeState> GS_Welcome;
typedef Singleton<MainMenuState> GS_MainMenu;
typedef Singleton<GameOptionState> GS_Option;
typedef Singleton<GamePauseState> GS_Pause;
typedef Singleton<GamePlayState> GS_GamePlay;
typedef Singleton<GameOverState> GS_GameOver;

// Factory Prototype
typedef  Singleton<FactoryEntity> FactorySingleton;

// Pool Manager
typedef Singleton<PoolManager> PoolManagerSingleton;

#define InputMgr InputManagerSingleton::GetInstance()
#define FrameMgr FrameManagerSingleton::GetInstance()
#define AnimationMgr AnimationManagerSingleton::GetInstance()
#define ResourceMgr ResourceManagerSingleton::GetInstance()
#define TextMgr TextManagerSingleton::GetInstance()
#define PhysicsMgr PhysicsManagerSingleton::GetInstance()
#define Dispatcher MessageDispatcherSingleton::GetInstance()
#define GameInstance GameSingleton::GetInstance()

//Music
#define MusicMgr MusicManagerSingleton::GetInstance()
#define Factory FactorySingleton::GetInstance()
#define PoolMgr PoolManagerSingleton::GetInstance()

