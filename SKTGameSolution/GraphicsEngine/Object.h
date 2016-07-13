#pragma once
#include "../Utilities/utilities.h"
#include <vector>
#include "Texture.h"
#include "CubeTexture.h"
#include "Model.h"
#include "Shaders.h"

enum class TypeObject {OBJECT, SKYBOX, TERRAIN};

class Object
{
private:
public:
	TypeObject m_typType;
	Model *m_pModel;
	std::vector<Texture*> m_vec2DTextures;
	std::vector<CubeTexture*> m_vecCubeTextures;
	Shaders *m_pShader;
	Vector3 m_vec3Pos;
	Vector3 m_vec3Rot;
	Vector3 m_vec3Scale;
	Matrix m_maxWorldMat;
	Object() :m_pModel(0),
			  m_pShader(0)
	{
		
	};
	virtual ~Object();
	virtual void Draw();
	void SetModel(Model *m) { m_pModel = m; };
	void SetShader(Shaders *s) { m_pShader = s; };
	void Add2dTexture(Texture *t) { m_vec2DTextures.push_back(t); }
	void AddCubeTexture(CubeTexture *c) { m_vecCubeTextures.push_back(c); }
};

