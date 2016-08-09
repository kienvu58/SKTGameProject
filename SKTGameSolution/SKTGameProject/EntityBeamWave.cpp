#include "EntityBeamWave.h"
#include "SingletonClasses.h"
#include "../GraphicsEngine/Globals.h"


EntityBeamWave::EntityBeamWave(): m_bIsActive(false), m_iInitializedWidth(0), m_fLength(0), m_fSpeed(16), m_iDirection(1)
{
}


EntityBeamWave::~EntityBeamWave()
{
}

void EntityBeamWave::Render()
{
	if (m_bIsActive)
	{
		m_SpriteBody.Render();
		m_SpriteHead.Render();
		m_SpriteTail.Render();
	}
}

void EntityBeamWave::Update()
{
	if (m_bIsActive)
	{
		static float count = 0.0f;
		count += Globals::deltaTime * Globals::animationTime;
		if (count >= 9)
		{
			m_bIsActive = false;
			count = 0.0f;
		}


		m_fLength += m_fSpeed * Globals::deltaTime;

//		auto randScale = 1.0f + 0.1f * (- 1 + 2 * float(rand()) / RAND_MAX);
		auto randScale = 0.95f + Globals::deltaTime * 10;

		auto scaleBodyX = PixelsFromMeters(m_fLength) / m_iInitializedWidth;
		auto scaleHeadX = 1.0f;
		if (scaleBodyX < 1.0f)
		{
			scaleHeadX = scaleBodyX;
		}
		auto headPhysicsPosition = m_vec2StartPosition + m_iDirection * m_fLength * b2Vec2(1, 0);
		auto bodyPhysicsPosition = m_vec2StartPosition + m_iDirection * m_fLength / 2 * b2Vec2(1, 0);
		auto isReversed = m_iDirection == -1;

		auto bodyGraphicsPosition =
			GraphicsFromPhysics(bodyPhysicsPosition) - Vector2(1, 0) * m_iDirection * m_iInitializedWidth / 4;
		m_SpriteBody.SetRenderInfo(bodyGraphicsPosition, isReversed, Vector2(scaleBodyX, randScale));


		auto headGraphicsPosition =
			GraphicsFromPhysics(headPhysicsPosition) - Vector2(1, 0) * m_iDirection * m_iInitializedWidth / 2;
		m_SpriteHead.SetRenderInfo(headGraphicsPosition, isReversed, Vector2(scaleHeadX, 1) * randScale);

		m_SpriteTail.SetRenderInfo(GraphicsFromPhysics(m_vec2StartPosition), isReversed, Vector2(scaleHeadX, 1) * randScale);
	}
}

bool EntityBeamWave::HandleMessage(const Telegram& telegram)
{
	return false;
}

EntityType EntityBeamWave::GetType()
{
	return BEAM_WAVE;
}

Entity* EntityBeamWave::Clone()
{
	return nullptr;
}

void EntityBeamWave::InitSpriteHead(int modelId, int frameId, int shaderId)
{
	m_SpriteHead.SetModel(ResourceMgr->GetModelById(modelId));
	m_SpriteHead.SetFrame(FrameMgr->GetFrameById(frameId));
	m_SpriteHead.SetShaders(ResourceMgr->GetShadersById(shaderId));
}

void EntityBeamWave::InitSpriteBody(int modelId, int frameId, int shaderId)
{
	auto pModel = ResourceMgr->GetModelById(modelId);
	m_iInitializedWidth = pModel->GetModelWidth();
	m_SpriteBody.SetModel(pModel);
	m_SpriteBody.SetFrame(FrameMgr->GetFrameById(frameId));
	m_SpriteBody.SetShaders(ResourceMgr->GetShadersById(shaderId));
}

void EntityBeamWave::InitSpriteTail(int modelId, int frameId, int shaderId)
{
	m_SpriteTail.SetModel(ResourceMgr->GetModelById(modelId));
	m_SpriteTail.SetFrame(FrameMgr->GetFrameById(frameId));
	m_SpriteTail.SetShaders(ResourceMgr->GetShadersById(shaderId));
}

void EntityBeamWave::Fire(b2Vec2 position, int direction)
{
	m_bIsActive = true;
	m_fLength = 0;
	bool isReversed = direction == -1;
	m_SpriteHead.SetRenderInfo(GraphicsFromPhysics(position), isReversed);
	auto bodyPosition = GraphicsFromPhysics(position) + Vector2(1, 0) * direction * m_iInitializedWidth / 2;
	m_SpriteBody.SetRenderInfo(bodyPosition / 2, isReversed);
	m_SpriteTail.SetRenderInfo(GraphicsFromPhysics(position), isReversed);
	m_vec2StartPosition = position;
	m_iDirection = direction;
}
