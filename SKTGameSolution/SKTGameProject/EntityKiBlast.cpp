#include "EntityKiBlast.h"
#include "SingletonClasses.h"
#include <Box2D/Dynamics/b2World.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include "../GraphicsEngine/Globals.h"


EntityKiBlast::EntityKiBlast(): m_fSpeed(6),
                    m_fAttackDamage(10)
{
}


EntityKiBlast::~EntityKiBlast()
{
}

void EntityKiBlast::Update()
{
	if (m_pBody->IsActive())
	{
		bool isReversed = m_iDirection == -1;
		m_Sprite.SetRenderInfo(GraphicsFromPhysics(m_pBody->GetPosition()), isReversed);
		if (IsOutOfWall())
		{
			Dispatcher->DispatchMessageA(this, GameInstance, MSG_KIBLAST_OUT_OF_WALL, this);
		}
	}
}

void EntityKiBlast::Render()
{
	if (m_pBody->IsActive())
	{
		m_Sprite.Render();
	}
}

Entity* EntityKiBlast::Clone()
{
	EntityKiBlast* newKiBlast = new EntityKiBlast();

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
	//newKiBlast->GetBody()->SetActive(false);
	//attributes
	newKiBlast->SetSpeed(m_fSpeed);
	newKiBlast->SetSprite(m_Sprite);

	return newKiBlast;
}

EntityType EntityKiBlast::GetType()
{
	return KI_BLAST;
}

bool EntityKiBlast::HandleMessage(const Telegram& telegram)
{
	return false;
}

void EntityKiBlast::InitSprite(int modelId, int frameId, int shaderId)
{
	m_Sprite.SetModel(ResourceMgr->GetModelById(modelId));
	m_Sprite.SetFrame(FrameMgr->GetFrameById(frameId));
	m_Sprite.SetShaders(ResourceMgr->GetShadersById(shaderId));
}

void EntityKiBlast::InitBody(const b2BodyDef& bodyDef, const b2FixtureDef& fixtureDef)
{
	m_pBody = PhysicsMgr->GetWorld()->CreateBody(&bodyDef);
	m_pBody->CreateFixture(&fixtureDef);
	m_pBody->SetBullet(true);
	m_pBody->SetUserData(this);
	m_pBody->SetActive(false);
}

void EntityKiBlast::Fire(b2Vec2 position, int direction)
{
	m_pBody->SetActive(true);
	m_pBody->SetTransform(position, m_pBody->GetAngle());
	m_pBody->SetLinearVelocity(m_fSpeed * b2Vec2(direction, 0));
	m_iDirection = direction;
}

void EntityKiBlast::SetSprite(Sprite sprite)
{
	m_Sprite = sprite;
}

void EntityKiBlast::SetSpeed(float speed)
{
	m_fSpeed = speed;
}

bool EntityKiBlast::IsOutOfWall()
{
	float tmp = 0;
	float wallHalfWidth = MetersFromPixels(Globals::screenWidth) / 2;
	float wallHalfHeight = MetersFromPixels(Globals::screenHeight) / 2;
	float boundryX = wallHalfWidth + tmp;
	float boundryY = wallHalfHeight + tmp;

	b2Vec2 position = m_pBody->GetPosition();

	if (-boundryX < position.x && position.x < boundryX
		&& -boundryY < position.y && position.y < boundryY)
		return false;

	return true;
}

b2Body* EntityKiBlast::GetBody() const
{
	return m_pBody;
}

float EntityKiBlast::Attack() const
{
	return m_fAttackDamage;
}
