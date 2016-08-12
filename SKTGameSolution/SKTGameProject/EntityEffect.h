#pragma once
#include "Entity.h"
#include "../GraphicsEngine/Animation.h"
#include "../GraphicsEngine/Sprite.h"

class EntityEffect :
	public Entity
{
public:
	EntityEffect();
	EntityEffect(const EntityEffect& other);
	~EntityEffect();

	void Render() override;
	void Update() override;
	bool HandleMessage(const Telegram& telegram) override;
	EntityType GetType() override;
	Entity* Clone() override;

	void Init(int prototypeId, const char* dataPath) override;
	void Reset() override;

	void UpdateSpriteFrame();
	void Stop();
	void Start(b2Vec2 position, Entity* pOwner);
	void ResetCurrentAnimationInfo();
private:
	Sprite m_Sprite;
	Entity* m_pOwner;

	Animation* m_animation;
	int m_iCurrentFrameIndex;
	int m_iLastFrameIndex;
	float m_fCurrentDelay;
	int m_iFrameCount;
	bool m_bIsLoop;
	bool m_bAutoScaling;
	Vector2 m_vec2Position;
};

