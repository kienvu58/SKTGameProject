﻿#include "GamePlayState.h"
#include "../GraphicsEngine/AnimationManager.h"
#include "../GraphicsEngine/TextManager.h"
#include <Box2D/Dynamics/b2Fixture.h>
#include "SingletonClasses.h"
#include <ctime>
#include "../GraphicsEngine/Globals.h"
#include "../GraphicsEngine/HelperFunctions.h"
#include "EntityKiBlast.h"

GamePlayState::GamePlayState() : m_Player(nullptr), m_iScore(0), m_TheBestScore(0) {
    m_BackgroundPosition.x = Globals::screenWidth / 2;
    m_BackgroundPosition.y = Globals::screenWidth + Globals::screenWidth / 2;
}

void GamePlayState::Enter(Game *game) {
}

void GamePlayState::PressButton(Game *game) const {
    Vector2 lastMousePosition = InputMgr->GetLastMousePosition();
    if (m_Button_Pause.IsClicked(lastMousePosition)) {
        InputMgr->SetLastMousePosition(0, 0);
        MusicMgr->MusicPause("GamePlay");
        game->GetFSM()->ChangeState(GS_Pause::GetInstance());
    }
}


void GamePlayState::Execute(Game *game) {
    srand(static_cast<unsigned int>(time(nullptr)));
    PhysicsMgr->Update();
    MoveBackground();

    m_Player->Update();

    game->IncreasePlayingTime(Globals::deltaTime);
    game->UpdateDifficulty(m_iScore);

    m_spawner.SpawnMinions();
    for (auto pair : m_mapCurrentEntities) {
        for (auto entity : pair.second)
            entity->Update();
    }

    PressButton(game);
    HandleVirtualGamePad();

    UpdateHpBar();
    UpdateKiBar();
    UpdateOverheatBar();
}

void GamePlayState::Exit(Game *game) {
}

void GamePlayState::RenderText() const {
    std::string currentScore = std::to_string(m_iScore);

    std::string scoreText = "Score: ";
    scoreText.append(currentScore);
    TextMgr->RenderString(scoreText.c_str(), Vector4(1, 1, 0, 1), 60.0f, 450, 10, 1, 1);
    //	std::string playingTimeText = std::to_string(game->GetPlayingTime());
    //	playingTimeText.append(" s");
    //	TextMgr->RenderString(playingTimeText.c_str(), Vector4(1, 0, 0, 1), 60.0f, 200.0f, 0, 1, 1);
    //	std::string difficultyText = "Difficulty: ";
    //	difficultyText.append(std::to_string(game->GetDifficulty()));
    //	TextMgr->RenderString(difficultyText.c_str(), Vector4(1, 0, 0, 1), 60.0f, 500.0f, 0, 1, 1);
    //	std::string currentHealth = "Health: ";
    //	currentHealth.append(std::to_string(m_Player->GetCurrentHealth()));
    //	TextMgr->RenderString(currentHealth.c_str(), Vector4(1, 0, 0, 1), 60.0f, 0.0f, 30.0f, 1, 1);
    //	std::string currentKi = "Ki: ";
    //	currentKi.append(std::to_string(m_Player->GetCurrentKi()));
    //	TextMgr->RenderString(currentKi.c_str(), Vector4(1, 0, 0, 1), 60.0f, 0.0f, 60.0f, 1, 1);
}

void GamePlayState::RenderVirtualGamePad() {
#ifndef WIN32
    m_CircleWithDirections.Render();
    m_Circle4Dash.Render();
    m_Circle2Dash_J.Render();
    m_Circle2Dash_K.Render();
    m_Circle2Dash_L.Render();
    m_Circle2Dash_I.Render();

    m_ImageAura.Render();
    m_ImageBarrier.Render();
    m_ImageKamehameha.Render();
    m_ImageKiBlast.Render();
#endif
}

void GamePlayState::Render(Game *game) {
    m_Background.Render();
    m_Background_Clone.Render();
    m_Button_Pause.Render();

#ifndef WIN32
    RenderVirtualGamePad();
#endif

    m_HpBar.Render();
    m_HpOutline.Render();
    m_KiBar.Render();
    m_KiOutline.Render();
    m_OverheatBar.Render();
    m_OverheatOutline.Render();


    RenderText();

    m_Avatar.Render();

    for (const auto &pair : m_mapCurrentEntities) {
        for (auto entity : pair.second) {
            entity->Render();
        }
    }

    m_Player->Render();
}

void GamePlayState::MoveBackground() {
    if (m_BackgroundPosition.x == -Globals::screenWidth / 2) {
        m_BackgroundPosition.x = Globals::screenWidth + Globals::screenWidth / 2;
    }
    if (m_BackgroundPosition.y == -Globals::screenWidth / 2) {
        m_BackgroundPosition.y = Globals::screenWidth + Globals::screenWidth / 2;
    }
    m_Background.SetScreenPosition(m_BackgroundPosition.x--, Globals::screenHeight / 2);
    m_Background_Clone.SetScreenPosition(m_BackgroundPosition.y--, Globals::screenHeight / 2);
}

void GamePlayState::HandleVirtualGamePad() {
#ifndef WIN32
    auto touchEvents = InputMgr->GetTouchEvents();
    static const int INVALID_POINTER_ID = -1;
    int joyStickPointer, buttonJPointer, buttonKPointer, buttonLPointer, buttonIPointer;
    joyStickPointer = buttonIPointer = buttonJPointer = buttonKPointer = buttonLPointer = INVALID_POINTER_ID;
    for (auto pair : *touchEvents) {
        int pointerId = pair.first;
        Vector2 pointerPos = pair.second;

        joyStickPointer = m_Circle4Dash.IsClicked(pointerPos) ? pointerId : INVALID_POINTER_ID;
        buttonJPointer = m_Circle2Dash_J.IsClicked(pointerPos) ? pointerId : INVALID_POINTER_ID;
        buttonKPointer = m_Circle2Dash_K.IsClicked(pointerPos) ? pointerId : INVALID_POINTER_ID;
        buttonLPointer = m_Circle2Dash_L.IsClicked(pointerPos) ? pointerId : INVALID_POINTER_ID;
        buttonIPointer = m_Circle2Dash_I.IsClicked(pointerPos) ? pointerId : INVALID_POINTER_ID;
    }

    if (joyStickPointer != INVALID_POINTER_ID) {
        //check if inside circle.
        float margin = 100;
        Vector2 currentMousePosition = InputMgr->GetPointerPosition(joyStickPointer);
        Vector2 direction = currentMousePosition - m_CircleWithDirections.GetScreenPosition();
        float boundaryRadius =
                m_CircleWithDirections.GetSprite().GetModel()->GetModelWidth() / 2 + margin;
        float sensitivity = 20;
        if (direction.Length() < boundaryRadius && direction.Length() > sensitivity) {
            float radius = m_CircleWithDirections.GetSprite().GetModel()->GetModelWidth() / 2;
            if (direction.Length() > radius) {
                direction.Normalize();
                direction *= radius;
            }
            Vector2 newPosition = m_CircleWithDirections.GetScreenPosition() + direction;
            m_Circle4Dash.SetScreenPosition(int(newPosition.x), int(newPosition.y));

            float haftAreaSize = tanf(Radians(22.5));
            direction.Normalize();

            bool right = direction.x > haftAreaSize;
            bool left = direction.x < -haftAreaSize;
            bool down = direction.y > haftAreaSize;
            bool up = direction.y < -haftAreaSize;

            InputMgr->SetKeyEvent(KEY_D, right);
            InputMgr->SetKeyEvent(KEY_A, left);
            InputMgr->SetKeyEvent(KEY_W, up);
            InputMgr->SetKeyEvent(KEY_S, down);
        }
    }
    else {
        m_Circle4Dash.GetSprite().SetRenderInfo(m_CircleWithDirections.GetWorldPosition());
    }
    InputMgr->SetKeyEvent(KEY_J, buttonJPointer != INVALID_POINTER_ID);
    InputMgr->SetKeyEvent(KEY_K, buttonKPointer != INVALID_POINTER_ID);
    InputMgr->SetKeyEvent(KEY_L, buttonLPointer != INVALID_POINTER_ID);
    InputMgr->SetKeyEvent(KEY_I, buttonIPointer != INVALID_POINTER_ID);
#endif
}

void GamePlayState::InitVirtualGamePad() {
#ifndef WIN32
    m_CircleWithDirections.InitSprite(101, 202, 1);
    m_CircleWithDirections.SetScreenPosition(150, 480);

    m_Circle4Dash.InitSprite(102, 203, 1);
    m_Circle4Dash.SetScreenPosition(150, 480);

    Vector2 keyJPos(1058, 570);
    Vector2 keyKPos(1008, 480);
    Vector2 keyLPos(1058, 390);
    Vector2 keyIPos(940, 570);

    m_Circle2Dash_J.InitSprite(104, 204, 1);
    m_Circle2Dash_J.SetScreenPosition(keyJPos);

    m_Circle2Dash_K.InitSprite(104, 204, 1);
    m_Circle2Dash_K.SetScreenPosition(keyKPos);

    m_Circle2Dash_L.InitSprite(104, 204, 1);
    m_Circle2Dash_L.SetScreenPosition(keyLPos);

    m_Circle2Dash_I.InitSprite(104, 204, 1);
    m_Circle2Dash_I.SetScreenPosition(keyIPos);

    m_ImageKiBlast.InitSprite(202, 66, 1);
    m_ImageKamehameha.InitSprite(202, 84, 1);
    m_ImageBarrier.InitSprite(202, 86, 1);
    m_ImageAura.InitSprite(201, 44, 1);

    m_ImageKiBlast.SetScreenPosition(keyJPos);
    m_ImageKamehameha.SetScreenPosition(keyKPos + Vector2(5, 0));
    m_ImageBarrier.SetScreenPosition(keyLPos);
    m_ImageAura.SetScreenPosition(keyIPos);

    float alpha = 0.5;
    m_ImageAura.GetSprite().SetOpacity(alpha);
    m_ImageBarrier.GetSprite().SetOpacity(alpha);
    m_ImageKamehameha.GetSprite().SetOpacity(alpha);
    m_ImageKiBlast.GetSprite().SetOpacity(alpha);
#endif
}

void GamePlayState::Init(const char *filePath) {
    // Bars InitSprite
    m_HpBar.InitSprite(200, 212, 1);
    m_KiBar.InitSprite(200, 210, 1);
    m_OverheatBar.InitSprite(200, 211, 1);
    m_HpOutline.InitSprite(200, 213, 1);
    m_KiOutline.InitSprite(200, 213, 1);
    m_OverheatOutline.InitSprite(200, 213, 1);

    // Bars InitPosition
    auto barX = 250;
    m_HpBar.SetScreenPosition(barX, 25);
    m_HpOutline.SetScreenPosition(barX, 25);
    m_KiBar.SetScreenPosition(barX, 50);
    m_KiOutline.SetScreenPosition(barX, 50);
    m_OverheatBar.SetScreenPosition(barX, 75);
    m_OverheatOutline.SetScreenPosition(barX, 75);

    m_Avatar.InitSprite(9000, 9000, 1);
    m_Avatar.SetScreenPosition(50, 50);

    m_Background.InitSprite(2, 200, 1);

    m_Background_Clone.InitSprite(2, 201, 1);
    m_Background_Clone.SetScreenPosition(Globals::screenWidth + Globals::screenWidth / 2,
                                         Globals::screenHeight / 2);

    m_Button_Pause.InitSprite(5, 115, 1);
    m_Button_Pause.SetScreenPosition(1080, 40);

    InitVirtualGamePad();

    m_spawner.Init("Data/SPAWNER.json");

    m_Player = static_cast<EntityPlayer *>(Factory->GetPrototypeById(1));
    m_Player->Activate();

    MusicMgr->MusicVolume("GamePlay", 50);
}

bool GamePlayState::OnMessage(Game *game, const Telegram &telegram) {
    if (telegram.Message == MSG_CLEAN_UP) {
        RemoveEntityFromTheScreen(telegram.pSender);
        return true;
    }

    return false;
}

GamePlayState::~GamePlayState() {
}

void GamePlayState::AddEntityToTheScreen(Entity *entity) {
    auto prototypeId = entity->GetPrototypeId();
    auto pair = m_mapCurrentEntities.find(prototypeId);
    if (pair != m_mapCurrentEntities.end()) {
        if (entity != nullptr) {
            auto it2 = std::find(pair->second.begin(), pair->second.end(), entity);
            if (it2 == pair->second.end()) {
                pair->second.push_back(entity);
            }
        }
    }
    else {
        std::vector<Entity *> vecEntity;
        vecEntity.push_back(entity);
        m_mapCurrentEntities.insert(std::pair<int, std::vector<Entity *>>(prototypeId, vecEntity));
    }
}

void GamePlayState::RemoveEntityFromTheScreen(Entity *entity) {
    auto prototypeId = entity->GetPrototypeId();
    auto pair = m_mapCurrentEntities.find(prototypeId);
    if (pair != m_mapCurrentEntities.end()) {
        PoolMgr->ReleaseEntity(entity);
        RemoveFromVector<Entity *>(pair->second, entity);
    }
}

int GamePlayState::GetNumberOfEntitiesByPrototypeId(int prototypeId) {
    auto pair = m_mapCurrentEntities.find(prototypeId);
    if (pair != m_mapCurrentEntities.end())
        return pair->second.size();
    return 0;
}

int GamePlayState::GetNumberOfAllEntities() {
    auto size = 0;
    for (auto pair : m_mapCurrentEntities) {
        size += pair.second.size();
    }
    return size;
}

void GamePlayState::ClearEntitiesOnTheScreen() {
    for (auto entity : PoolMgr->GetInUseEntities()) {
        RemoveEntityFromTheScreen(entity);
    }
}

std::vector<Entity *> *GamePlayState::GetEntitiesByType(EntityType type) {
    auto pair = m_mapCurrentEntities.find(type);
    if (pair != m_mapCurrentEntities.end()) {
        return &pair->second;
    }
    return nullptr;
}

EntityPlayer *GamePlayState::GetPlayer() const {
    return m_Player;
}

void GamePlayState::IncreaseScore(int amount) {
    m_iScore += amount;
}

void GamePlayState::Reset() {
    m_iScore = 0;
    m_Player->Reset();
    ClearEntitiesOnTheScreen();
}

int GamePlayState::GetCurrentScore() const {
    return m_iScore;
}


void GamePlayState::UpdateHpBar() {
    float scaleFactor = m_Player->GetCurrentHealth() / m_Player->GetMaxHealth();
    float translateFactor = (1 - scaleFactor) / 2 * m_HpBar.GetSprite().GetModel()->GetModelWidth();

    Vector2 scaleVector = Vector2(scaleFactor, 1);
    Vector2 translateVector = Vector2(-translateFactor, 0);
    Vector2 currentPosition = m_HpBar.GetWorldPosition();

    m_HpBar.GetSprite().SetRenderInfo(currentPosition + translateVector, false, scaleVector);
}

void GamePlayState::UpdateKiBar() {
    float scaleFactor = m_Player->GetCurrentKi() / m_Player->GetMaxKi();
    float translateFactor = (1 - scaleFactor) / 2 * m_KiBar.GetSprite().GetModel()->GetModelWidth();

    Vector2 scaleVector = Vector2(scaleFactor, 1);
    Vector2 translateVector = Vector2(-translateFactor, 0);
    Vector2 currentPosition = m_KiBar.GetWorldPosition();

    m_KiBar.GetSprite().SetRenderInfo(currentPosition + translateVector, false, scaleVector);
}

void GamePlayState::UpdateOverheatBar() {
    float scaleFactor = m_Player->GetCurrentOverheat() / MAX_OVERHEAT;
    float translateFactor =
            (1 - scaleFactor) / 2 * m_OverheatBar.GetSprite().GetModel()->GetModelWidth();

    Vector2 scaleVector = Vector2(scaleFactor, 1);
    Vector2 translateVector = Vector2(-translateFactor, 0);
    Vector2 currentPosition = m_OverheatBar.GetWorldPosition();

    m_OverheatBar.GetSprite().SetRenderInfo(currentPosition + translateVector, false, scaleVector);
}
