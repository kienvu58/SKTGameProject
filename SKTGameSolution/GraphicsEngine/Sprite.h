#pragma once
#include "GraphicalObject.h"

class Frame;

class Sprite : public GraphicalObject
{
public:
	Sprite();
	~Sprite();
	void Render() override;
	void Update(void* data) override;
private:
	int m_iIndex;
	Vector2 m_vec2Position;
};

