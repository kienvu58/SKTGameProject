#include "stdafx.h"
#include "Camera.h"
#include <iostream>

Camera* Camera::instance = 0;

Camera::Camera()
{
	cameraPos = Vector3(0.0f, 0.0f, 0.0f);
	cameraFront = Vector3(0.0f, 0.0f, -1.0f);
	cameraUp = Vector3(0.0f, 1.0f, 0.0f);
	m_fSpeed = 0.4;
	pitch = 0;
	yaw = -90;
}

Camera::~Camera()
{
}

Camera* Camera::GetInstance() {
	if (instance == 0) {
		instance = new Camera;
	}
	return instance;
}

Matrix Camera::GetLookAt(Vector3 &cameraPosition, Vector3 &targetPosition, Vector3 &up) {
	//calculate camera dirction vector.
	Vector3 cameraDirection = cameraPosition - targetPosition;
	cameraDirection.Normalize();
	//calculate camera right vector.
	Vector3 cameraRight = up.Cross(cameraDirection);
	cameraRight.Normalize();
	//calculate the up vecotr of the camera.
	Vector3 cameraUp = cameraDirection.Cross(cameraRight);

	Matrix left, right;
	int i, j;
	
	left.m[0][0] = cameraRight.x;
	left.m[0][1] = cameraRight.y;
	left.m[0][2] = cameraRight.z;
	left.m[0][3] = 0;

	left.m[1][0] = cameraUp.x;
	left.m[1][1] = cameraUp.y;
	left.m[1][2] = cameraUp.z;
	left.m[1][3] = 0;

	left.m[2][0] = cameraDirection.x;
	left.m[2][1] = cameraDirection.y;
	left.m[2][2] = cameraDirection.z;
	left.m[2][3] = 0;

	left.m[3][0] = 0;
	left.m[3][1] = 0;
	left.m[3][2] = 0;
	left.m[3][3] = 1;
	////
	right.m[0][0] = 1;
	right.m[0][1] = 0;
	right.m[0][2] = 0;
	right.m[0][3] = -cameraPosition.x;

	right.m[1][0] = 0;
	right.m[1][1] = 1;
	right.m[1][2] = 0;
	right.m[1][3] = -cameraPosition.y;

	right.m[2][0] = 0;
	right.m[2][1] = 0;
	right.m[2][2] = 1;
	right.m[2][3] = -cameraPosition.z;

	right.m[3][0] = 0;
	right.m[3][1] = 0;
	right.m[3][2] = 0;
	right.m[3][3] = 1;
	
	Matrix view = left*right;

	return view.Transpose(); 
}

void Camera::SetInfo(float n, float f, float fov, float speed) {
	m_fNear = n;
	m_fFar = f;
	m_fFov = fov;
	m_fSpeed = speed;
}

Matrix Camera::GetCurrentViewMatrix() {
	return GetLookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

