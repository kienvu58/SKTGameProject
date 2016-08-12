#include <json.hpp>
#include <fstream>
#include "EntityBeamWave.h"
#include "SingletonClasses.h"
#include "../GraphicsEngine/Globals.h"
#include "../GraphicsEngine/HelperFunctions.h"
#include "RayCastMultipleCallback.h"


EntityBeamWave::EntityBeamWave(): m_iSpriteWidth(0), m_fThickness(0), m_fLength(0)
{
}


EntityBeamWave::~EntityBeamWave()
{
}

void EntityBeamWave::Render()
{
	if (m_bIsActive)
	{
		if (m_pSpriteStartEffect)
			m_pSpriteStartEffect->Render();
		m_SpriteMid.Render();
		m_SpriteEnd.Render();
		m_SpriteStart.Render();
		for (auto hitEffect : m_vecHitEffects)
		{
			hitEffect->Render();
		}
	}
}

void EntityBeamWave::DetectIntersections()
{
	RayCastMultipleCallback* callbacks = new RayCastMultipleCallback[m_iNRaycasts];
	static auto space = m_fThickness / (m_iNRaycasts - 1);
	auto firstRaycastBegin = m_vec2Pos - b2Vec2(0, m_fThickness / 2);
	for (auto i = 0; i < m_iNRaycasts; i++)
	{
		auto begin = firstRaycastBegin + i * space * b2Vec2(0, 1);
		auto end = begin + m_fLength * b2Vec2(1, 0);
		callbacks[i].maskBits = CATEGORY_GREEN_KIBLAST | CATEGORY_CELLJUNIOR | CATEGORY_CELL;
		PhysicsMgr->GetWorld()->RayCast(&callbacks[i], begin, end);
		for (auto fixture : callbacks[i].fixtures)
		{
			auto entity = fixture->GetBody()->GetUserData();
			auto position = fixture->GetBody()->GetPosition();
			AddHitEffect(position);
			if (fixture->GetFilterData().categoryBits == CATEGORY_GREEN_KIBLAST)
			{
				Dispatcher->DispatchMessageA(this, static_cast<EntityKiBlast*>(entity), MSG_EXPLODE, nullptr);
			}
			else
			{
				auto dps = m_fAttackDamage * Globals::deltaTime;
				Dispatcher->DispatchMessageA(this, static_cast<EntityMinion*>(entity), MSG_MINION_TAKE_DAMAGE, &dps);
			}
		}
	}
	delete[] callbacks;
}

void EntityBeamWave::UpdateGraphics()
{
	auto scaleMidX = PixelsFromMeters(m_fLength) / m_iSpriteWidth;
	auto endPhysicsPosition = m_vec2Pos + m_iDirection * m_fLength * b2Vec2(1, 0);
	auto midPhysicsPosition = m_vec2Pos + m_iDirection * m_fLength / 2 * b2Vec2(1, 0);
	auto isReversed = m_iDirection == -1;

	auto midGraphicsPosition =
		GraphicsFromPhysics(midPhysicsPosition) - Vector2(1, 0) * m_iDirection * m_iSpriteWidth / 4;
	m_SpriteMid.SetRenderInfo(midGraphicsPosition, isReversed, Vector2(scaleMidX, 1));


	auto endGraphicsPosition =
		GraphicsFromPhysics(endPhysicsPosition) - Vector2(1, 0) * m_iDirection * m_iSpriteWidth / 2;
	m_SpriteEnd.SetRenderInfo(endGraphicsPosition, isReversed);

	m_SpriteStart.SetRenderInfo(GraphicsFromPhysics(m_vec2Pos), isReversed);
}

void EntityBeamWave::UpdateLength()
{
	auto end = GraphicsFromPhysics(m_vec2Pos + b2Vec2(m_fLength, 0));
	if (!Globals::IsOutOfBoundary(end, m_iSpriteWidth))
	{
		m_fLength += m_fSpeed * Globals::deltaTime;
	}
}

void EntityBeamWave::AddHitEffect(b2Vec2 position)
{
	auto hitEffect = static_cast<EntityEffect*>(PoolMgr->GetEntityByPrototypeId(m_iHitEffectPID));
	hitEffect->Start(position, this);
	m_vecHitEffects.push_back(hitEffect);
}

void EntityBeamWave::Update()
{
	if (m_bIsActive)
	{
		UpdateLength();
		UpdateGraphics();
		DetectIntersections();
		for (auto hitEffect : m_vecHitEffects)
		{
			hitEffect->Update();
		}
		if (m_pSpriteStartEffect)
			m_pSpriteStartEffect->Update();
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
	auto alpha = data["graphics"]["alpha"].get<float>();
	m_fSpeed = data["speed"].get<float>();
	m_iNRaycasts = data["nRaycasts"].get<int>();
	m_bHasAura = data["hasAura"].get<bool>();
	m_fThickness = MetersFromPixels(data["thicknessInPixels"].get<int>());
	m_fAttackDamage = data["attackDamage"].get<float>();

	m_iHitEffectPID = data["PIDs"]["HitEffect"].get<int>();
	m_iSpriteStartEffectPID = data["PIDs"]["SpriteStartEffect"].get<int>();

	auto pModel = ResourceMgr->GetModelById(modelId);
	m_iSpriteWidth = pModel->GetModelWidth();

	InitSpriteMid(modelId, frameMidId, shaderId);
	InitSpriteEnd(modelId, frameEndId, shaderId);
	InitSpriteStart(modelId, frameStartId, shaderId);

	m_SpriteEnd.SetOpacity(alpha);
	m_SpriteMid.SetOpacity(alpha);
	m_SpriteStart.SetOpacity(alpha);
}

void EntityBeamWave::Reset()
{
}

bool EntityBeamWave::HandleMessage(const Telegram& telegram)
{
	if (telegram.Message == MSG_CLEAN_UP)
	{
		// will be cleaned up after beamwave is stopped
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

void EntityBeamWave::Fire(b2Vec2 position, int direction)
{
	m_bIsActive = true;
	m_fLength = MetersFromPixels(m_iSpriteWidth);
	auto isReversed = direction == -1;
	m_SpriteEnd.SetRenderInfo(GraphicsFromPhysics(position), isReversed);
	auto bodyPosition = GraphicsFromPhysics(position) + Vector2(1, 0) * direction * m_iSpriteWidth / 2;
	m_SpriteMid.SetRenderInfo(bodyPosition / 2, isReversed);
	m_SpriteStart.SetRenderInfo(GraphicsFromPhysics(position), isReversed);
	m_vec2Pos = position;
	m_iDirection = direction;
	if (!m_pSpriteStartEffect)
	{
		m_pSpriteStartEffect = static_cast<EntityEffect*>(PoolMgr->GetEntityByPrototypeId(m_iSpriteStartEffectPID));
	}
	auto effectPos = position - direction * MetersFromPixels(m_iSpriteWidth) / 3 * b2Vec2(1, 0);
	m_pSpriteStartEffect->Start(effectPos, this);
}

void EntityBeamWave::Stop()
{
	m_bIsActive = false;
	m_pSpriteStartEffect->Stop();
	for (auto hitEffect : m_vecHitEffects)
	{
		PoolMgr->ReleaseEntity(hitEffect);
	}
	m_vecHitEffects.clear();
}
