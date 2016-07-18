#include "Object.h"
#include "Globals.h"
#include "Camera.h"
#include <cmath>
#include <iostream>
#include <ctime>
float tt;

Object::Object(): m_typType(), m_pModel(nullptr), m_pShader(nullptr)
{
	m_matOthorProjection.SetIdentity();
}

Object::~Object()
{
}

void Object::Draw()
{
	glUseProgram(m_pShader->program);

	m_pShader->EnableStates();

	glBindBuffer(GL_ARRAY_BUFFER, m_pModel->GetVboId());
	if (m_typType != TypeObject::SPRITE)
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pModel->GetIboId());

	/*Set Position*/
	if (m_pShader->locationAttributePos != -1)
	{
		glEnableVertexAttribArray(m_pShader->locationAttributePos);
		glVertexAttribPointer(m_pShader->locationAttributePos, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, pos)));
	}

	/*Set Texture*/
	GLuint iTexLocation = m_pShader->locationUniformTex;
	const GLint* samplers(nullptr);
	int size = 0;
	if (m_typType != TypeObject::SKYBOX)
	{
		samplers = new GLint[m_vec2DTextures.size()];
		size = m_vec2DTextures.size();
		for (int i = 0; i < m_vec2DTextures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, m_vec2DTextures[i]->GetId());
			const_cast<GLint*>(samplers)[i] = i;
		}
	}
	else if (m_typType == TypeObject::SKYBOX)
	{
		samplers = new GLint[m_vecCubeTextures.size()];
		size = m_vecCubeTextures.size();
		for (int i = 0; i < m_vecCubeTextures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_CUBE_MAP, m_vecCubeTextures[i]->GetId());
			const_cast<GLint*>(samplers)[i] = i;
		}
	}

	if (iTexLocation != -1)
	{
		glUniform1iv(iTexLocation, size, samplers);
	}

	delete []samplers;

	/*Set UV*/
	GLuint uvLocation = m_pShader->locationAttributeUV;
	if (uvLocation != -1)
	{
		glEnableVertexAttribArray(uvLocation);
		glVertexAttribPointer(uvLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, uv)));
	}

	//mvp
	Matrix mvp = m_matWorld * m_matView * m_matProjection;

	GLuint mvpLocation = m_pShader->locationUniformMVP;
	if (mvpLocation != -1)
	{
		glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &(mvp.m[0][0]));
	}

	/*Set uniform time*/
	tt += 0.001;
	if (tt >= 1) tt = 0;
	//std::cout << tt;
	float currentTime = std::time(nullptr);
	if (m_pShader->locationUniformTime != -1)
	{
		glUniform1f(m_pShader->locationUniformTime, tt);
	}

	//glDrawArrays(GL_TRIANGLES, 0, 3);
	if (m_typType != TypeObject::SPRITE)
		glDrawElements(GL_TRIANGLES, m_pModel->GetNumIndices(), GL_UNSIGNED_INT, 0);
	else
	{
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}

	m_pShader->DisableStates();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	if (m_typType != TypeObject::SPRITE)
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	if (m_typType == TypeObject::OBJECT)
		glBindTexture(GL_TEXTURE_2D, 0);
	else if (m_typType == TypeObject::SKYBOX)
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void Object::SetWorldMatrix(Vector3 position, Vector3 rotation, Vector3 scale)
{
	Matrix translateMatrix;
	translateMatrix.SetTranslation(position);

	Matrix scaleMatrix;
	scaleMatrix.SetScale(scale);

	Matrix roteMatrix;
	Matrix roteZ;
	roteZ.SetRotationZ(Radians(rotation.z));
	Matrix roteY;
	roteY.SetRotationY(Radians(rotation.y));
	Matrix roteX;
	roteX.SetRotationX(Radians(rotation.x));
	roteMatrix = roteZ * roteY * roteX;
	m_matWorld = scaleMatrix * roteMatrix * translateMatrix;
}

void Object::SetViewMatrix(Matrix matView)
{
	m_matView = matView;
}

void Object::SetProjectionMatrix(Matrix matProjection)
{
	m_matProjection = matProjection;
}

void Object::SetType(TypeObject type)
{
	m_typType = type;
}
