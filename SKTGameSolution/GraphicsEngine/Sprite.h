#pragma once
#include "GraphicalObject.h"

class Frame;

class Sprite : public GraphicalObject
{
public:
	Sprite();
	~Sprite();
	void Render() override;
	void SetPosition(Vector2 position);
	void SetIndex(int index);
	void SetFrame(Frame* frame);
private:
	int m_Index;
};

