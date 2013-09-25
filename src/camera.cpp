
#include "../headers/camera.h"

CAMERA::CAMERA () 
{ 
	this->WINDOW_WIDTH = 0.0f;
	this->WINDOW_HEIGHT = 0.0f;
	this->FOV = 0.0f;
	this->NearPlane = 0.0f;
	this->FarPlane = 0.0f;
}

CAMERA::CAMERA (const float WINDOW_WIDTH, const float WINDOW_HEIGHT, const float FOV, const float NearPlane, const float FarPlane)
{
	this->WINDOW_WIDTH = WINDOW_WIDTH;
	this->WINDOW_HEIGHT = WINDOW_HEIGHT;
	this->FOV = FOV;
	this->NearPlane = NearPlane;
	this->FarPlane = FarPlane;

	CameraAngle = 0.0f;

	AspectRatio = this->WINDOW_WIDTH / this->WINDOW_HEIGHT;
}

CAMERA::~CAMERA () 
{ 
}

void CAMERA::SetDefaultCamera()
{
	CameraAngle = 0.0f;

	DefaultCameraMatrix.ViewMatrix = glm::lookAt(glm::vec3(0.0f, 1.5f, 1.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	DefaultCameraMatrix.ProjectionMatrix = glm::perspective(FOV, AspectRatio, NearPlane, FarPlane);
}

void CAMERA::RotateCameraAngle(const float _CameraAngle)
{
	DefaultCameraMatrix.ViewMatrix = glm::lookAt(glm::vec3(0.0f, 1.5f, 1.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

       	DefaultCameraMatrix.ViewMatrix = glm::rotate(DefaultCameraMatrix.ViewMatrix, _CameraAngle, glm::vec3(0.0f, 0.0f, 1.0f)); 

	DefaultCameraMatrix.ProjectionMatrix = glm::perspective(FOV, AspectRatio, NearPlane, FarPlane);
}

void CAMERA::RotateCameraLeft()
{
	if(CameraAngle == 0.0f)
	{
		CameraAngle = 360.0f;
	}

	if(CameraAngle <= 360.0f)
	{
		CameraAngle -= 1.0f; 
	}

	std::cout << "[DEBUG] Camera Angle: " << CameraAngle << std::endl;

	RotateCameraAngle(CameraAngle);
}

void CAMERA::RotateCameraRight()
{
	if(CameraAngle == 360.0f)
	{
		CameraAngle = 0.0f;
	}

	if(CameraAngle <= 360.0f)
	{
		CameraAngle += 1.0f; 
	}

	std::cout << "[DEBUG] Camera Angle: " << CameraAngle << std::endl;

	RotateCameraAngle(CameraAngle);
}

