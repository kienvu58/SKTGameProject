#pragma once
#include "Object.h"

class Sprite : public Object
{
public:
	Sprite();
	~Sprite();
	void InitModel(float x, float y, float w, float h, float texW, float texH, Vector2 origin);
};

