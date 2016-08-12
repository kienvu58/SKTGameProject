#include <json.hpp>
#include <fstream>
#include "EntityEffect.h"
#include "../GraphicsEngine/Globals.h"
#include "SingletonClasses.h"


EntityEffect::EntityEffect()
{
}

EntityEffect::EntityEffect(const EntityEffect& other): m_Sprite(other.m_Sprite),
                                                       m_pOwner(nullptr),
                                                       m_animation(other.m_animation),
                                                       m_iCurrentFrameIndex(0),
                                                       m_iLastFrameIndex(0),
                                                       m_fCurrentDelay(0),
                                                       m_iFrameCount(1),
                                                       m_bIsLoop(other.m_bIsLoop),
                                                       m_bAutoScaling(other.m_bAutoScaling)
{
}

EntityEffect::~EntityEffect()
{
}


void EntityEffect::Render()
{
	if (IsActive())
	{
		m_Sprite.Render();
	}
}

void EntityEffect::Update()
{
	if (IsActive())
	{
		if (m_bAutoScaling)
		{
			auto scale = (m_iCurrentFrameIndex) * 0.3 + 1;
			m_Sprite.SetRenderInfo(m_vec2Position, false, Vector2(scale, scale));
		}
		UpdateSpriteFrame();
		auto isAnimationPlayedOnce = m_iFrameCount >= m_animation->GetTotalFrames();
		auto isEffectFinished = !m_bIsLoop && isAnimationPlayedOnce;
		if (isEffectFinished)
		{
			Stop();
		}
	}
	else
	{
		Dispatcher->DispatchMessageA(this, m_pOwner, MSG_CLEAN_UP, nullptr);
	}
}

bool EntityEffect::HandleMessage(const Telegram& telegram)
{
	return false;
}

EntityType EntityEffect::GetType()
{
	return ENTITY_EFFECT;
}

Entity* EntityEffect::Clone()
{
	auto cloneEffect = new EntityEffect(*this);
	return cloneEffect;
}

void EntityEffect::UpdateSpriteFrame()
{
	if (m_iCurrentFrameIndex == m_iLastFrameIndex)
	{ // in duration of current frame, increase delay
		m_fCurrentDelay += Globals::animationTime * Globals::deltaTime;
	}
	else
	{ // into new frame
		m_iFrameCount++;
		m_fCurrentDelay = 0;
	}
	auto frame = m_animation->GetFrameByIndex(m_iCurrentFrameIndex);
	m_Sprite.SetFrame(frame);

	m_iLastFrameIndex = m_iCurrentFrameIndex;
	m_iCurrentFrameIndex = m_animation->GetNextFrameIndex(m_iCurrentFrameIndex, m_fCurrentDelay);
}

void EntityEffect::Stop()
{
	m_bIsActive = false;
}

void EntityEffect::Start(b2Vec2 position, Entity* pOwner)
{
	m_bIsActive = true;
	m_vec2Position = GraphicsFromPhysics(position);
	m_Sprite.SetRenderInfo(m_vec2Position);
	m_pOwner = pOwner;
}

void EntityEffect::ResetCurrentAnimationInfo()
{
	m_iCurrentFrameIndex = 0;
	m_iLastFrameIndex = 0;
	m_fCurrentDelay = 0.0f;
	m_iFrameCount = 1;
}

void EntityEffect::Init(int prototypeId, const char* dataPath)
{
	m_iPrototypeId = prototypeId;

	std::ifstream fin(dataPath);
	nlohmann::json data(fin);
	fin.close();

	m_animation = AnimationMgr->GetAnimationById(data["animationId"].get<int>());
	m_bIsLoop = data["isLoop"].get<bool>();
	m_bAutoScaling = data["autoScaling"].get<bool>();

	auto modelId = data["graphics"]["modelId"].get<int>();
	auto shaderId = data["graphics"]["shaderId"].get<int>();
	auto alpha = data["graphics"]["alpha"].get<float>();
	m_Sprite.SetModel(ResourceMgr->GetModelById(modelId));
	m_Sprite.SetShaders(ResourceMgr->GetShadersById(shaderId));
	m_Sprite.SetOpacity(alpha);
	UpdateSpriteFrame();
	ResetCurrentAnimationInfo();
}

void EntityEffect::Reset()
{
	ResetCurrentAnimationInfo();
}
