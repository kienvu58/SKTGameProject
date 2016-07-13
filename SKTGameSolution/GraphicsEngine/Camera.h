#pragma once
#include "../Utilities/utilities.h"
#include "Math.h"

class Camera
{
private:
	Camera();
	static Camera *instance;
public:
	float m_fNear;
	float m_fFar;
	float m_fFov;
	float m_fSpeed;

	static Camera* GetInstance();
	~Camera();
	Matrix GetLookAt(Vector3 &cameraPosition, Vector3 &targetPosition, Vector3 &up);
	void SetInfo(float n, float f, float fov, float speed);
	Vector3 cameraPos;
	Vector3 cameraFront;
	Vector3 cameraUp;
	Matrix GetCurrentViewMatrix();

	float pitch;
	float yaw;
};

