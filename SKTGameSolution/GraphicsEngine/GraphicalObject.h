#pragma once
#include "Model.h"
#include "Texture.h"
#include "Shaders.h"

class GraphicalObject
{
public:
	GraphicalObject();
	virtual ~GraphicalObject();

	virtual void Render();
	void SetModel(Model* pModel);
	void SetTexture(Texture* pTexture);
	void SetShaders(Shaders* pShaders);
	Model* GetModel() const;
protected:
	Model* m_pModel;
	Texture* m_pTexture;
	Shaders* m_pShaders;
	Matrix m_matMVP;
};


