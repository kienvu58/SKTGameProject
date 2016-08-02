#include "BeamWave.h"
#include "SingletonClasses.h"
#include "../GraphicsEngine/Globals.h"


BeamWave::BeamWave(): m_bIsActive(false), m_iInitializedWidth(0), m_fLength(0), m_fSpeed(16), m_iDirection(1)
{
}


BeamWave::~BeamWave()
{
}

void BeamWave::Render()
{
	if (m_bIsActive)
	{
		m_SpriteBody.Render();
		m_SpriteHead.Render();
		m_SpriteTail.Render();
	}
}

void BeamWave::Update()
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
		m_SpriteBody.SetRenderInfo(bodyGraphicsPosition, isReversed, Vector2(scaleBodyX, scaleHeadX));

		
		auto headGraphicsPosition = 
			GraphicsFromPhysics(headPhysicsPosition) - Vector2(1, 0) * m_iDirection * m_iInitializedWidth / 2;
		m_SpriteHead.SetRenderInfo(headGraphicsPosition, isReversed, Vector2(scaleHeadX, scaleHeadX));

		m_SpriteTail.SetRenderInfo(GraphicsFromPhysics(m_vec2StartPosition), isReversed, Vector2(scaleHeadX, scaleHeadX));
	}
}

bool BeamWave::HandleMessage(const Telegram& telegram)
{
	return false;
}

EntityType BeamWave::GetType()
{
	return BEAM_WAVE;
}

Entity* BeamWave::Clone()
{
	return nullptr;
}

void BeamWave::InitSpriteHead(int modelId, int frameId, int shaderId)
{
	m_SpriteHead.SetModel(ResourceMgr->GetModelById(modelId));
	m_SpriteHead.SetFrame(FrameMgr->GetFrameById(frameId));
	m_SpriteHead.SetShaders(ResourceMgr->GetShadersById(shaderId));
}

void BeamWave::InitSpriteBody(int modelId, int frameId, int shaderId)
{
	auto pModel = ResourceMgr->GetModelById(modelId);
	m_iInitializedWidth = pModel->GetModelWidth();
	m_SpriteBody.SetModel(pModel);
	m_SpriteBody.SetFrame(FrameMgr->GetFrameById(frameId));
	m_SpriteBody.SetShaders(ResourceMgr->GetShadersById(shaderId));
}

void BeamWave::InitSpriteTail(int modelId, int frameId, int shaderId)
{
	m_SpriteTail.SetModel(ResourceMgr->GetModelById(modelId));
	m_SpriteTail.SetFrame(FrameMgr->GetFrameById(frameId));
	m_SpriteTail.SetShaders(ResourceMgr->GetShadersById(shaderId));
}

void BeamWave::Fire(b2Vec2 position, int direction)
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
