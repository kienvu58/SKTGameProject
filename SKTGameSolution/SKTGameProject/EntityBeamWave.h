#pragma once
#include "Entity.h"
#include "../GraphicsEngine/Sprite.h"
#include "EntityBullet.h"
#include "EntityEffect.h"
#include "RayCastMultipleCallback.h"
#include <Box2D/Common/b2Math.h>

class EntityBeamWave :
	public EntityBullet
{
public:
	EntityBeamWave();
	~EntityBeamWave();

	void Render() override;
	void DetectIntersections();
	void Update() override;
	bool HandleMessage(const Telegram& telegram) override;
	EntityType GetType() override;
	Entity* Clone() override;

	void InitSpriteEnd(int modelId, int frameId, int shaderId);
	void InitSpriteMid(int modelId, int frameId, int shaderId);
	void InitSpriteStart(int modelId, int frameId, int shaderId);

	void UpdateGraphics();
	void UpdateLength();
	void AddHitEffect(b2Vec2 position);
	void Fire(b2Vec2 position, int direction) override;
	void Stop();

	void Init(int prototypeId, const char* dataPath) override;
	void Reset() override;
private:

	// Graphics information
	Sprite m_SpriteEnd;
	Sprite m_SpriteMid;
	Sprite m_SpriteStart;
	int m_iSpriteWidth;
	float m_fThickness;
	bool m_bHasAura;

	// PIDs
	int m_iSpriteStartEffectPID;
	int m_iHitEffectPID;

	EntityEffect* m_pSpriteStartEffect;
	std::vector<EntityEffect*> m_vecHitEffects;

	// Physics information
	b2Vec2 m_vec2Pos;		
	int m_iNRaycasts;
	float m_fLength;
};

