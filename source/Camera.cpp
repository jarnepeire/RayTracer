#pragma once
#include "Camera.h"
#include "SDL.h"
#include "Structs.h"

using namespace Elite;
Camera::Camera()
	: m_AspectRatio()
	, m_FOV()
	, m_TranslationSpeed(2.f)
	, m_RotationSpeed(0.3f)
	, m_Height()
	, m_Width()
	, m_Right(1.f, 0.f, 0.f)
	, m_Up(0.f, 1.f, 0.f)
	, m_WorldUp(0.f, 1.f, 0.f)
	, m_Forward(0.f, 0.f, 1.f)
	, m_Position(0.f, 1.f, 5.f)
	, m_LookAt(Elite::FMatrix4::Identity())
{
}

void Camera::Initialize(const Elite::FPoint3& position, float width, float height, float fovAngle)
{
	m_Position = position;
	m_AspectRatio = width / height;
	m_Width = (int)width;
	m_Height = (int)height;
	m_FOV = (float)tan(fovAngle * E_TO_RADIANS / 2.f);
}

void Camera::Update(const InputManager& input, float deltaT)
{
	//Get mouse data
	const auto& relativeMouseData = input.GetRelativeMouseStateData();

	//Check for button presses
	if (input.IsPressed(EMouseInput::LRMB))
	{
		//Translation only (UP AND DOWN)
		m_Position.y -= relativeMouseData.y  * m_TranslationSpeed * deltaT;

		//Remake ONB with new position
		MakeLookAtMatrix();
	}
	else if (input.IsPressed(EMouseInput::LMB))
	{
		//Rotation First
		Elite::FMatrix3 yRotation = MakeRotation(-relativeMouseData.x * deltaT * m_RotationSpeed, m_Up);
		m_Forward = yRotation * m_Forward;

		//Translation Second
		float speed = relativeMouseData.y * m_TranslationSpeed * deltaT;
		m_Position.x += speed * m_Forward.x;
		m_Position.z += speed * m_Forward.z;

		//Remake ONB with newly updated vectors/position
		MakeLookAtMatrix();
	}
	else if (input.IsPressed(EMouseInput::RMB))
	{
		//Rotation
		Elite::FMatrix3 xRotation = MakeRotation(-relativeMouseData.y * m_RotationSpeed * deltaT, m_Right);
		Elite::FMatrix3 yRotation = MakeRotation(-relativeMouseData.x * m_RotationSpeed * deltaT, m_Up);
		m_Forward = xRotation * yRotation * m_Forward;

		//Remake ONB with new forward
		MakeLookAtMatrix();
	}
}

void Camera::CalculateCameraRay(int xRasterSpace, int yRasterSpace, Ray& outputRay)
{
	//Convert from raster to screenspace
	float yScreenSpace = (1 - 2 * (yRasterSpace + 0.5f) / m_Height) * m_FOV;
	float xScreenSpace = (2 * (xRasterSpace + 0.5f) / m_Width - 1) * m_AspectRatio * m_FOV;

	//Treating it as a point - point to get a direction
	FPoint3 pixelToLookAt{ xScreenSpace, yScreenSpace, -1 };
	FPoint4 transformedPos = m_LookAt * FPoint4(pixelToLookAt, 1.f);
	FVector4 dir = transformedPos - FPoint4(m_Position, 1.f);
	FVector3 transformedDir = FVector3(GetNormalized(dir));

	//Fill ray information
	outputRay.Origin = m_Position;
	outputRay.Direction = transformedDir;
}

void Camera::SetPosition(const Elite::FPoint3& position)
{
	SetPosition(position.x, position.y, position.z);
}

void Camera::SetPosition(float x, float y, float z)
{
	m_Position = Elite::FPoint3(x, y, z); 
	MakeLookAtMatrix();
}

void Camera::MakeLookAtMatrix()
{
	m_Right = Elite::GetNormalized(Cross(m_WorldUp, m_Forward));
	m_Up = Elite::GetNormalized(Cross(m_Forward, m_Right));

	m_LookAt = Elite::FMatrix4(m_Right, m_Up, m_Forward, FVector4(FVector3(m_Position), 1.f));
}
