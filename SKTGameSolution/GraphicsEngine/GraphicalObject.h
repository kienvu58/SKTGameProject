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
	virtual void Update(void* data);
	void SetModel(Model* pModel);
	void SetTexture(Texture* pTexture);
	void SetShaders(Shaders* pShaders);
protected:
	Model* m_pModel;
	Texture* m_pTexture;
	Shaders* m_pShaders;
};

//#include "../Utilities/utilities.h"
//#include <vector>
//#include "Texture.h"
//#include "CubeTexture.h"
//#include "Model.h"
//#include "Shaders.h"
//
//enum class TypeObject {OBJECT, SKYBOX, TERRAIN, SPRITE};
//
//class GraphicalObject
//{
//public:
//	GraphicalObject();
//	virtual ~GraphicalObject();
//	virtual void Draw();
//	void SetModel(Model *m) { m_pModel = m; };
//	void SetShader(Shaders *s) { m_pShader = s; };
//	void Add2dTexture(Texture *t) { m_vec2DTextures.push_back(t); }
//	void AddCubeTexture(CubeTexture *c) { m_vecCubeTextures.push_back(c); }
//	void SetWorldMatrix(Vector3 position, Vector3 rotation, Vector3 scale);
//	void SetViewMatrix(Matrix matView);
//	void SetProjectionMatrix(Matrix matProjection);
//	void SetType(TypeObject type);
//protected:
//	TypeObject m_typType;
//	Model *m_pModel;
//	std::vector<Texture*> m_vec2DTextures;
//	std::vector<CubeTexture*> m_vecCubeTextures;
//	Shaders *m_pShader;
//	Matrix m_matWorld;
//	Matrix m_matView;
//	Matrix m_matProjection;
//	Matrix m_matOthorProjection;
//};
//
