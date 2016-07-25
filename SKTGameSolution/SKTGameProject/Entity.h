#pragma once
class Entity
{
public:
	Entity();
	virtual ~Entity();
	virtual void Render() = 0;
	virtual void Update() = 0;
};

