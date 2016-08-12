#include <json.hpp>
#include <fstream>
#include "EntityBeamWave.h"
#include "SingletonClasses.h"
#include "../GraphicsEngine/Globals.h"
#include "../GraphicsEngine/HelperFunctions.h"


EntityBeamWave::EntityBeamWave(): m_SpriteWidth(0), m_SpriteHeight(0), m_fLength(0)
{
}


EntityBeamWave::~EntityBeamWave()
{
}

void EntityBeamWave::Render()
{
	if (m_bIsActive)
	{
		m_SpriteMid.Render();
		m_SpriteEnd.Render();
		m_SpriteStart.Render();
	}
}

void EntityBeamWave::UpdateGraphics()
{
	auto scaleMidX = PixelsFromMeters(m_fLength) / m_SpriteWidth;
	auto endPhysicsPosition = m_vec2Pos + m_iDirection * m_fLength * b2Vec2(1, 0);
	auto midPhysicsPosition = m_vec2Pos + m_iDirection * m_fLength / 2 * b2Vec2(1, 0);
	auto isReversed = m_iDirection == -1;

	auto midGraphicsPosition =
		GraphicsFromPhysics(midPhysicsPosition) - Vector2(1, 0) * m_iDirection * m_SpriteWidth / 4;
	m_SpriteMid.SetRenderInfo(midGraphicsPosition, isReversed, Vector2(scaleMidX, 1));


	auto endGraphicsPosition =
		GraphicsFromPhysics(endPhysicsPosition) - Vector2(1, 0) * m_iDirection * m_SpriteWidth / 2;
	m_SpriteEnd.SetRenderInfo(endGraphicsPosition, isReversed);

	m_SpriteStart.SetRenderInfo(GraphicsFromPhysics(m_vec2Pos), isReversed);
}

void EntityBeamWave::Update()
{
	if (m_bIsActive)
	{
		m_fLength += m_fSpeed * Globals::deltaTime;
		UpdateGraphics();
	}
}


void EntityBeamWave::Init(int prototypeId, const char* dataPath)
{
	std::ifstream fin(dataPath);
	nlohmann::json data(fin);
	fin.close();

	auto modelId = data["graphics"]["modelId"].get<int>();
	auto frameStartId = data["graphics"]["frameStartId"].get<int>();
	auto frameMidId = data["graphics"]["frameMidId"].get<int>();
	auto frameEndId = data["graphics"]["frameEndId"].get<int>();
	auto shaderId = data["graphics"]["shaderId"].get<int>();
	m_fSpeed = data["speed"].get<float>();
	m_iNRaycasts = data["nRaycasts"].get<int>();
	m_bHasAura = data["hasAura"].get<bool>();

	auto pModel = ResourceMgr->GetModelById(modelId);
	m_SpriteWidth = pModel->GetModelWidth();
	m_SpriteHeight = pModel->GetModelHeight();

	InitSpriteMid(modelId, frameMidId, shaderId);
	InitSpriteEnd(modelId, frameEndId, shaderId);
	InitSpriteStart(modelId, frameStartId, shaderId);
}

void EntityBeamWave::Reset()
{
}

bool EntityBeamWave::HandleMessage(const Telegram& telegram)
{
	if (telegram.Message == MSG_CLEAN_UP)
	{
		auto effect = static_cast<EntityEffect*>(telegram.pSender);
		CleanUpHitEffect(effect);
		return true;
	}
	return false;
}

EntityType EntityBeamWave::GetType()
{
	return ENTITY_BEAMWAVE;
}

Entity* EntityBeamWave::Clone()
{
	auto clone = new EntityBeamWave(*this);
	return clone;
}

void EntityBeamWave::InitSpriteEnd(int modelId, int frameId, int shaderId)
{
	m_SpriteEnd.SetModel(ResourceMgr->GetModelById(modelId));
	m_SpriteEnd.SetFrame(FrameMgr->GetFrameById(frameId));
	m_SpriteEnd.SetShaders(ResourceMgr->GetShadersById(shaderId));
}

void EntityBeamWave::InitSpriteMid(int modelId, int frameId, int shaderId)
{
	auto pModel = ResourceMgr->GetModelById(modelId);
	m_SpriteMid.SetModel(pModel);
	m_SpriteMid.SetFrame(FrameMgr->GetFrameById(frameId));
	m_SpriteMid.SetShaders(ResourceMgr->GetShadersById(shaderId));
}

void EntityBeamWave::InitSpriteStart(int modelId, int frameId, int shaderId)
{
	m_SpriteStart.SetModel(ResourceMgr->GetModelById(modelId));
	m_SpriteStart.SetFrame(FrameMgr->GetFrameById(frameId));
	m_SpriteStart.SetShaders(ResourceMgr->GetShadersById(shaderId));
}

void EntityBeamWave::CleanUpHitEffect(EntityEffect* effect)
{
	PoolMgr->ReleaseEntity(effect);
	RemoveFromVector<EntityEffect*>(m_vecHitEffects, effect);
}

void EntityBeamWave::Fire(b2Vec2 position, int direction)
{
	m_bIsActive = true;
	m_fLength = MetersFromPixels(m_SpriteWidth);
	auto isReversed = direction == -1;
	m_SpriteEnd.SetRenderInfo(GraphicsFromPhysics(position), isReversed);
	auto bodyPosition = GraphicsFromPhysics(position) + Vector2(1, 0) * direction * m_SpriteWidth / 2;
	m_SpriteMid.SetRenderInfo(bodyPosition / 2, isReversed);
	m_SpriteStart.SetRenderInfo(GraphicsFromPhysics(position), isReversed);
	m_vec2Pos = position;
	m_iDirection = direction;
}

void EntityBeamWave::Stop()
{
	m_bIsActive = false;
}
