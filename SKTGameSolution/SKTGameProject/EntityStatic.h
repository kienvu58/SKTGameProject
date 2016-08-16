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
	Entity* Clone() override;

	void InitSprite(int modelId, int frameId, int shaderId);
	void SetScreenPosition(int x, int y);
	Sprite& GetSprite();

	bool IsClicked(Vector2 mousePosition) const;
	Vector2 GetWorldPosition() const;
	Vector2 GetScreenPosition() const;
private:
	Sprite m_Sprite;
	Vector2 m_ScreenPosition;
	Vector2 m_WorldPosition;
};

