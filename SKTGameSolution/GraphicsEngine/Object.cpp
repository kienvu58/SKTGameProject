#include "stdafx.h"
#include "Object.h"
#include "Globals.h"
#include "Camera.h"
#include <cmath>
#include <iostream>
#include <ctime>
float tt;
Object::~Object()
{
	
}

void Object::Draw() {
	glUseProgram(m_pShader->program);

	m_pShader->EnableStates();

	glBindBuffer(GL_ARRAY_BUFFER, m_pModel->GetVboId());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pModel->GetIboId());

	/*Set Position*/
	if (m_pShader->locationAttributePos != -1){
		glEnableVertexAttribArray(m_pShader->locationAttributePos);
		glVertexAttribPointer(m_pShader->locationAttributePos, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}
	
	/*Set Texture*/
	GLuint iTexLocation = m_pShader->locationUniformTex;
	const GLint* samplers;
	int size;
	if (m_typType == TypeObject::OBJECT) {
		samplers = new GLint[m_vec2DTextures.size()];
		size = m_vec2DTextures.size();
		for (int i = 0; i < m_vec2DTextures.size(); i++) {
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, m_vec2DTextures[i]->GetId());
			const_cast<GLint*>(samplers)[i] = i;
		}
	}	
	else if (m_typType == TypeObject::SKYBOX) {
		samplers = new GLint[m_vecCubeTextures.size()];
		size = m_vecCubeTextures.size();
		for (int i = 0; i < m_vecCubeTextures.size(); i++) {
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_CUBE_MAP, m_vecCubeTextures[i]->GetId());
			const_cast<GLint*>(samplers)[i] = i;
		}
	}

	if (iTexLocation != -1) {
		glUniform1iv(iTexLocation, size, samplers);
	}

	delete []samplers;
	
	/*Set UV*/
	GLuint uvLocation = m_pShader->locationAttributeUV;
	if (uvLocation != -1) {
		glEnableVertexAttribArray(uvLocation);
		glVertexAttribPointer(uvLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vector3) + sizeof(Vector4)));
	}

	/*Set MVP*/
	Matrix translateMatrix;
	translateMatrix.SetTranslation(m_vec3Pos);

	Matrix scaleMatrix;
	scaleMatrix.SetScale(m_vec3Scale);

	Matrix roteMatrix;
	Matrix roteZ;
	roteZ.SetRotationZ(RADIAN_PER_DEGREE * m_vec3Rot.z);
	Matrix roteY;
	roteY.SetRotationY(RADIAN_PER_DEGREE * m_vec3Rot.y);
	Matrix roteX;
	roteX.SetRotationX(RADIAN_PER_DEGREE * m_vec3Rot.x);
	roteMatrix = roteZ*roteY*roteX;

	Matrix modelMatrix = scaleMatrix*roteMatrix*translateMatrix;

	//view matrix
	Matrix viewMatrix;
	viewMatrix.SetIdentity();
	viewMatrix = Camera::GetInstance()->GetCurrentViewMatrix();

	//projectionMatrix;
	Matrix projectMatrix;
	float ratio = float(Globals::screenWidth) / float(Globals::screenHeight);
	projectMatrix = projectMatrix.SetPerspective(RADIAN_PER_DEGREE * Camera::GetInstance()->m_fFov, ratio, 
		Camera::GetInstance()->m_fNear, Camera::GetInstance()->m_fFar);

	//mvp
	Matrix mvp = modelMatrix*viewMatrix*projectMatrix;

	GLuint mvpLocation = m_pShader->locationUniformMVP;
	if (mvpLocation != -1) {
		glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &(mvp.m[0][0]));
	}

	/*Set uniform time*/
	tt += 0.001;
	if (tt >= 1) tt = 0;
	//std::cout << tt;
	float currentTime = std::time(0);
	if (m_pShader->locationUniformTime != -1) {
		glUniform1f(m_pShader->locationUniformTime, tt);
	}

	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES, m_pModel->GetNumIndices(), GL_UNSIGNED_INT, 0);

	m_pShader->DisableStates();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	if (m_typType == TypeObject::OBJECT)
		glBindTexture(GL_TEXTURE_2D, 0);
	else if (m_typType == TypeObject::SKYBOX)
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
