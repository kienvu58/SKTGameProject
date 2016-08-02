#pragma once
#include "Entity.h"
#include "../GraphicsEngine/Sprite.h"

class BeamWave :
	public Entity
{
public:
	BeamWave();
	~BeamWave();

	void Render() override;
	void Update() override;
	bool HandleMessage(const Telegram& telegram) override;
	EntityType GetType() override;
	Entity* Clone() override;

	void InitSpriteHead(int modelId, int frameId, int shaderId);
	void InitSpriteBody(int modelId, int frameId, int shaderId);
	void InitSpriteTail(int modelId, int frameId, int shaderId);

	void Fire(b2Vec2 position, int direction = 1);

private:
	bool m_bIsActive;

	// Graphics information
	Sprite m_SpriteHead;
	Sprite m_SpriteBody;
	Sprite m_SpriteTail;
	int m_iInitializedWidth;

	// Physics information
	b2Vec2 m_vec2StartPosition;		
	float m_fLength;
	float m_fSpeed;
	int m_iDirection;	// 1: left to right, -1: right to left
};

