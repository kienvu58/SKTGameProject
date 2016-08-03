#include "KiBlast.h"
#include "SingletonClasses.h"
#include <Box2D/Dynamics/b2World.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Fixture.h>


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
	KiBlast* newKiBlast = new KiBlast();

	//physics
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2(0, 0);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(MetersFromPixels(24), MetersFromPixels(12));

	b2FixtureDef fixture;
	fixture.shape = &boxShape;
	fixture.restitution = 1.0f;
	fixture.isSensor = true;
	fixture.filter.categoryBits = CATEGORY_KI_BLAST;
	fixture.filter.maskBits = CATEGORY_MINION;
	newKiBlast->InitBody(bodyDef, fixture);

	//attributes
	newKiBlast->SetSpeed(m_fSpeed);
	newKiBlast->SetSprite(m_Sprite);

	return newKiBlast;
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

void KiBlast::SetSprite(Sprite sprite)
{
	m_Sprite = sprite;
}

void KiBlast::SetSpeed(float speed)
{
	m_fSpeed = speed;
}
