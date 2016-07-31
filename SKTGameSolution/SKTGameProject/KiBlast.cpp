#include "KiBlast.h"
#include "SingletonClasses.h"
#include <Box2D/Dynamics/b2World.h>


KiBlast::KiBlast(): m_fSpeed(6) {
}


KiBlast::~KiBlast()
{
}

void KiBlast::Update()
{
	if (m_pBody->IsActive())
	{
		bool isReversed = m_iDirection == -1;
		m_Sprite.SetRenderInfo(GraphicsFromPhysics(m_pBody->GetPosition()), isReversed);
	}
}

void KiBlast::Render()
{
	if (m_pBody->IsActive())
	{
		m_Sprite.Render();
	}
}

Entity* KiBlast::Clone()
{
	return nullptr;
}

EntityType KiBlast::GetType()
{
	return KI_BLAST;
}

bool KiBlast::HandleMessage(const Telegram& telegram)
{
	return false;
}

void KiBlast::InitSprite(int modelId, int frameId, int shaderId)
{
	m_Sprite.SetModel(ResourceMgr->GetModelById(modelId));
	m_Sprite.SetFrame(FrameMgr->GetFrameById(frameId));
	m_Sprite.SetShaders(ResourceMgr->GetShadersById(shaderId));
}

void KiBlast::InitBody(const b2BodyDef& bodyDef, const b2FixtureDef& fixtureDef)
{
	m_pBody = PhysicsMgr->GetWorld()->CreateBody(&bodyDef);
	m_pBody->CreateFixture(&fixtureDef);
	m_pBody->SetBullet(true);
	m_pBody->SetUserData(this);
	m_pBody->SetActive(false);
}

void KiBlast::Fire(b2Vec2 position, int direction)
{
	m_pBody->SetActive(true);
	m_pBody->SetTransform(position, m_pBody->GetAngle());
	m_pBody->SetLinearVelocity(m_fSpeed * b2Vec2(direction, 0));
	m_iDirection = direction;
}
