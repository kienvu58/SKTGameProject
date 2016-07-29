#pragma once
#include "Entity.h"
#include "../GraphicsEngine/Sprite.h"

class EntityStatic :
	public Entity
{
public:
	EntityStatic();
	void Render() override;
	void Update() override;
	void InitSprite(int modelId, int frameId, int shaderId);
	void InitPosition(int x, int y);
	~EntityStatic();

private:
	Sprite m_Sprite;
};

