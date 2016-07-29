#pragma once
#include "Entity.h"
#include "../GraphicsEngine/Sprite.h"

class EntityStatic :
	public Entity
{
public:
	EntityStatic();
	~EntityStatic();

	void Render() override;
	void Update() override;
	bool HandleMessage(const Telegram& telegram) override;
	EntityType GetType() override;
	Entity* Clone();

	void InitSprite(int modelId, int frameId, int shaderId);
	void InitPosition(int x, int y);


private:
	Sprite m_Sprite;
};

