#include "KiBlast.h"
#include "SingletonClasses.h"


KiBlast::KiBlast()
{
}


KiBlast::~KiBlast()
{
}

void KiBlast::Update()
{

}

void KiBlast::Render()
{
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

void KiBlast::InitBody(const b2BodyDef& bodyDef, const b2FixtureDef& fixtureDef)
{
	m_pBody = PhysicsMgr->GetWorld()->CreateBody(&bodyDef);
	m_pBody->CreateFixture(&fixtureDef);
	m_pBody->IsBullet();
	m_pBody->SetUserData(this);
}
