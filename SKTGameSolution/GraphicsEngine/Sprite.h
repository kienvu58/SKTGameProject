#pragma once
#include "GraphicalObject.h"

class Frame;

class Sprite : public GraphicalObject
{
public:
	Sprite();
	~Sprite();
	void Render() override;
	void SetRenderInfo(Vector2 position, bool isReversed = false, Vector2 vec2Scale = Vector2(1, 1));
	void SetIndex(int index);
	void SetFrame(Frame* frame);


private:
	int m_Index;
};

