#include "Camera.h"
#include <iostream>
#include "Globals.h"

Camera::Camera(): m_bIsViewDirty(true),
                  m_bIsProjectionDirty(true),
                  m_fNear(0),
                  m_fFar(0),
                  m_fFov(0),
                  m_fSpeed(0.4f),
                  m_fSensitivity(0.05f),
                  m_fPitch(0),
                  m_fYaw(-90.0f)
{
	m_vCameraPos = Vector3(0.0f, 0.0f, 3.0f);
	m_vCameraFront = Vector3(0.0f, 0.0f, -1.0f);
	m_vCameraUp = Vector3(0.0f, 1.0f, 0.0f);
}

Camera::~Camera()
{
}

Matrix Camera::GetViewMatrix()
{
	return m_matView;
}

void Camera::UpdateViewMatrix()
{
	if (m_bIsViewDirty)
	{
		m_matView = GetLookAt(m_vCameraPos, m_vCameraPos + m_vCameraFront, m_vCameraUp);
		m_bIsViewDirty = false;
	}
}

Matrix Camera::GetProjectionMatrix()
{
	return m_matProjection;
}

void Camera::UpdateProjectionMatrix()
{
	if (m_bIsProjectionDirty)
	{
		if (m_CameraType == CameraType::PERSPECTIVE)
		{
			m_matProjection.SetPerspective(m_fFov, float(Globals::screenWidth) / float(Globals::screenHeight), m_fNear, m_fFar);
		}
		else
		{
			m_matProjection.SetOrthographic(-240, 240, 854/2, -854/2, 0.1, 40.0);
		}
		m_bIsProjectionDirty = false;
	}
}

Matrix Camera::GetLookAt(Vector3& cameraPosition, Vector3& targetPosition, Vector3& up)
{
	Vector3 cameraDirection = (cameraPosition - targetPosition).Normalize();
	Vector3 cameraRight = up.Cross(cameraDirection).Normalize();
	Vector3 cameraUp = cameraDirection.Cross(cameraRight);

	Matrix matView;
	matView.m[0][0] = cameraRight.x;
	matView.m[0][1] = cameraUp.x;
	matView.m[0][2] = cameraDirection.x;
	matView.m[0][3] = 0;

	matView.m[1][0] = cameraRight.y;
	matView.m[1][1] = cameraUp.y;
	matView.m[1][2] = cameraDirection.y;
	matView.m[1][3] = 0;

	matView.m[2][0] = cameraRight.z;
	matView.m[2][1] = cameraUp.z;
	matView.m[2][2] = cameraDirection.z;
	matView.m[2][3] = 0;

	matView.m[3][0] = -cameraRight.Dot(cameraPosition);
	matView.m[3][1] = -cameraUp.Dot(cameraPosition);
	matView.m[3][2] = -cameraDirection.Dot(cameraPosition);
	matView.m[3][3] = 1;

	return matView;
}

void Camera::SetInfo(float n, float f, float fov, float speed, float sensitivity)
{
	m_fNear = n;
	m_fFar = f;
	m_fFov = fov;
	m_fSpeed = speed;
	m_fSensitivity = sensitivity;
	m_bIsProjectionDirty = true;
}

void Camera::Move(Vector3 direction, float deltaTime)
{
	if (direction.Length() > 0)
	{
		Vector3 deltaMove;
		Vector3 zaxis = (-m_vCameraFront).Normalize();
		Vector3 xaxis = m_vCameraUp.Cross(zaxis).Normalize();
		Vector3 yaxis = zaxis.Cross(xaxis);
		deltaMove = (zaxis * direction.z + xaxis * direction.x + yaxis * direction.y).Normalize();
		deltaMove *= deltaTime * m_fSpeed;
		m_vCameraPos += deltaMove;
		m_bIsViewDirty = true;
	}
}

void Camera::SetCameraType(CameraType cameraType)
{
	m_CameraType = cameraType;
}

void Camera::Rotate(Vector2 offset, float deltaTime)
{
	if (offset.Length() > 0)
	{
		m_fPitch -= offset.y * m_fSensitivity;
		m_fYaw += offset.x * m_fSensitivity;
		m_fPitch = m_fPitch < 89.0f ? m_fPitch : 89.0f;
		m_fPitch = m_fPitch > -89.0f ? m_fPitch : -89.0f;
		m_vCameraFront.x = cos(Radians(m_fPitch)) * cos(Radians(m_fYaw));
		m_vCameraFront.y = sin(Radians(m_fPitch));
		m_vCameraFront.z = cos(Radians(m_fPitch)) * sin(Radians(m_fYaw));
		m_bIsViewDirty = true;
	}
}
