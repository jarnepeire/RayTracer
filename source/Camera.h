#pragma once
#include "EMath.h"
#include "InputManager.h"

struct Ray;

class Camera final
{
public:
	Camera();
	~Camera() = default;

	/* Initialize camera with some base variables */
	void Initialize(const Elite::FPoint3& position, float width, float height, float fovAngle);
	
	/* Update camera according to the input and time */
	void Update(const InputManager& input, float deltaT);

	/* Calculates and returns ray from camera eye pos to the currently evaluated pixel in screen space 
		X- and Y-parameters are defined in raster space -> conversion to screen space happens in function */
	void CalculateCameraRay(int xRasterSpace, int yRasterSpace, Ray& outputRay);

	/* Return the aspect ratio of the camera */
	float GetAspectRatio() const { return m_AspectRatio; }

	/* Return the fov value (!= the fov angle) */
	float GetFOV() const { return m_FOV; }

	/* Return reference to the camera position */
	const Elite::FPoint3& GetPosition() const { return m_Position; }

	/* Return reference to the look at matrix (also known as cameraToWorld matrix) */
	const Elite::FMatrix4& GetLookAtMatrix() const { return m_LookAt; }

	/* Set new fov angle for camera */
	void SetFOV(float fovAngle) { m_FOV = (float)tan(fovAngle * E_TO_RADIANS / 2.f); }

	/* Set new camera position by FPoint3 */
	void SetPosition(const Elite::FPoint3& position);

	/* Set new camera position by x,y,z floats */
	void SetPosition(float x, float y, float z);

	/* Set new translation speed (how fast the camera moves through the scene) */
	void SetTranslationSpeed(float speed) { m_TranslationSpeed = speed; }

	/* Set new rotation speed (how fast the camera rotates around the scene) */
	void SetRotationSpeed(float speed) { m_RotationSpeed = speed; }

private:
	/* Camera info */
	float m_AspectRatio;
	float m_FOV;
	float m_TranslationSpeed;
	float m_RotationSpeed;

	/* Window info */
	int m_Height;
	int m_Width;

	Elite::FVector3 m_Right;
	Elite::FVector3 m_Up;
	Elite::FVector3 m_WorldUp;
	Elite::FVector3 m_Forward;
	Elite::FPoint3 m_Position;
	Elite::FMatrix4 m_LookAt;

	/* Private functions */
	void MakeLookAtMatrix();
};

