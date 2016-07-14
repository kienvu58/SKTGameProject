#pragma once
#include "../Utilities/utilities.h"
#include "Math.h"

class Camera
{
public:
	Camera();
	~Camera();
	Matrix GetViewMatrix();
	void UpdateViewMatrix();
	Matrix GetProjectionMatrix();
	void UpdateProjectionMatrix();
	static Matrix GetLookAt(Vector3 &cameraPosition, Vector3 &targetPosition, Vector3 &up);
	void SetInfo(float n, float f, float fov, float speed, float sensitivity);
	void Move(Vector3 direction, float deltaTime);
	void Rotate(Vector2 offset, float deltaTime);
private:
	Vector3 m_vCameraPos;
	Vector3 m_vCameraFront;
	Vector3 m_vCameraUp;
	Matrix m_matView;
	Matrix m_matProjection;
	bool m_bIsViewDirty;
	bool m_bIsProjectionDirty;
	float m_fNear;
	float m_fFar;
	float m_fFov;
	float m_fSpeed;
	float m_fSensitivity;
	float m_fPitch;
	float m_fYaw;
};

