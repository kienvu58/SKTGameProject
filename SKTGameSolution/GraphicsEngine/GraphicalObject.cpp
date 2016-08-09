#include "GraphicalObject.h"


GraphicalObject::GraphicalObject(): m_pModel(nullptr), m_pTexture(nullptr)
{
}

GraphicalObject::~GraphicalObject()
{
}

void GraphicalObject::Render()
{
}

void GraphicalObject::SetModel(Model* pModel)
{
	m_pModel = pModel;
}

void GraphicalObject::SetTexture(Texture* pTexture)
{
	m_pTexture = pTexture;
}

void GraphicalObject::SetShaders(Shaders* pShaders)
{
	m_pShaders = pShaders;
}

Model* GraphicalObject::GetModel() const
{
	return m_pModel;
}
