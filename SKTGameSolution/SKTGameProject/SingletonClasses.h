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
#include "GamePlayState.h"
#include "GameWelcomeState.h"
#include "MainMenuState.h"
#include "GameOptionState.h"
#include "CrudeTimer.h"
#include "MessageDispatcher.h"

// Clock
typedef Singleton<CrudeTimer> CrudeTimerSingleton;

// Message Dispatcher
typedef Singleton<MessageDispatcher> MessageDispatcherSingleton;

// Managers
typedef Singleton<InputManager> InputManagerSingleton;
typedef Singleton<FrameManager> FrameManagerSingleton;
typedef Singleton<AnimationManager> AnimationManagerSingleton;
typedef Singleton<ResourceManager> ResourceManagerSingleton;
typedef Singleton<TextManager> TextManagerSingleton;
typedef Singleton<PhysicsManager> PhysicsManagerSingleton;

// Player States
typedef Singleton<PlayerStandingState> PS_Standing;
typedef Singleton<PlayerMovingState> PS_Moving;
typedef Singleton<PlayerFiringState> PS_Firing;
typedef Singleton<PlayerFiringSpecialState> PS_FiringSpecial;
typedef Singleton<PlayerFiringUltimateState> PS_FiringUltimate;
typedef Singleton<PlayerGlobalState> PS_Global;

// Minion States
typedef Singleton<WanderingState> MS_Wandering;
typedef Singleton<MinionGlobalState> MS_Global;

// Game States
typedef Singleton<GamePlayState> GS_GamePlay;
typedef Singleton<GameWelcomeState> GS_Welcome;
typedef Singleton<MainMenuState> GS_MainMenu;
typedef Singleton<GameOptionState> GS_Option;

#define InputMgr InputManagerSingleton::GetInstance()
#define FrameMgr FrameManagerSingleton::GetInstance()
#define AnimationMgr AnimationManagerSingleton::GetInstance()
#define ResourceMgr ResourceManagerSingleton::GetInstance()
#define TextMgr TextManagerSingleton::GetInstance()
#define PhysicsMgr PhysicsManagerSingleton::GetInstance()
#define Clock CrudeTimerSingleton::GetInstance()
#define Dispatcher MessageDispatcherSingleton::GetInstance()
