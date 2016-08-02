#pragma once
#include "Entity.h"
#include "../GraphicsEngine/Animation.h"

class EntityEffect :
	public Entity
{
public:
	EntityEffect();
	~EntityEffect();

	void Render() override;
	void Update() override;
	bool HandleMessage(const Telegram& telegram) override;
	EntityType GetType() override;
	Entity* Clone() override;

private:
	Animation* m_animationStart;
	Animation* m_animationLoop;
};

