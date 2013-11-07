
#include "../headers/camera.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

unsigned int LastTime = 0;

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
	this->WINDOW_WIDTH 	= WINDOW_WIDTH;
	this->WINDOW_HEIGHT 	= WINDOW_HEIGHT;
	this->FOV 		= FOV;
	this->NearPlane 	= NearPlane;
	this->FarPlane		= FarPlane;

	AspectRatio 		= this->WINDOW_WIDTH / this->WINDOW_HEIGHT;

	Speed 			= 0.5f;

	CameraAngle 		= 0.0f;

	MouseSensitivity 	= 0.0015f;

	Horizontal 		= M_PI; // 180 degrees - looking straight
	 
	Vertical 		= float(M_PI/4.0f); // 45 degrees - looking down

	PositionVector		= glm::vec3(0.0f, 100.0f, 0.0f);
}

CAMERA::~CAMERA () 
{ 
}

//////////////////
//  FPS Camera 	//
//////////////////


void CAMERA::SetFPSCamera()
{
	ComputeVectors();

	FPSCameraMatrix.ProjectionMatrix = glm::perspective(FOV, AspectRatio, NearPlane, FarPlane);
	FPSCameraMatrix.ViewMatrix = glm::lookAt(PositionVector, PositionVector + DirectionVector, UpVector);

}

void CAMERA::MoveMouseCamera(const float x, const float y, const float DeltaTime)
{
	float X = float(WINDOW_WIDTH / 2 - x);
	float Y = float(WINDOW_HEIGHT /2 - y);

	Horizontal += MouseSensitivity * DeltaTime * X;
	Vertical += MouseSensitivity * DeltaTime * Y;
}

void CAMERA::StrafeCameraRight(const float DeltaTime)
{
	PositionVector -= RightVector * DeltaTime * Speed;
}

void CAMERA::StrafeCameraLeft(const float DeltaTime)
{
	PositionVector += RightVector * DeltaTime * Speed;
}

void CAMERA::MoveCameraForward(const float DeltaTime)
{
	PositionVector += DirectionVector * DeltaTime * Speed;
}

void CAMERA::MoveCameraBackward(const float DeltaTime)
{
	PositionVector -= DirectionVector * DeltaTime * Speed;
}

void CAMERA::ComputeVectors()
{
	DirectionVector = glm::vec3(cos(Vertical) * sin(Horizontal), sin(Vertical), cos(Vertical) * cos(Horizontal));

	RightVector = glm::vec3(sin(Horizontal - M_PI / 2.0f), 0, cos(Horizontal - M_PI / 2.0f));

	UpVector = glm::cross(RightVector, DirectionVector);
}















void CAMERA::UpdateDefaultCamera()
{
	DefaultCameraMatrix.ProjectionMatrix 	= glm::perspective(FOV, AspectRatio, NearPlane, FarPlane);
	DefaultCameraMatrix.ViewMatrix 		= glm::lookAt(PositionVector, PositionVector + DirectionVector, UpVector);

	//std::cout << "[DEBUG] Position: X " << PositionVector.x << ", Y " << PositionVector.y << ", Z " << PositionVector.z << std::endl; 
}

void CAMERA::UpdateMVP()
{
	DefaultCameraMatrix.IdentityMatrix 	= glm::mat4(1.0f);

	DefaultCameraMatrix.MVP			= DefaultCameraMatrix.ProjectionMatrix                                                              * DefaultCameraMatrix.ViewMatrix                                                                    * DefaultCameraMatrix.IdentityMatrix;

	DefaultCameraMatrix.Normal		= glm::inverse(                                                                                       glm::transpose((                                                                                                    DefaultCameraMatrix.IdentityMatrix                                                                * DefaultCameraMatrix.ViewMatrix                                                                     )));
}

void CAMERA::SetDefaultCamera()
{
	Horizontal 		= M_PI;
	Vertical 		= 0.0f;

	PositionVector		= glm::vec3(0.0f, 16.0f, 0.0f);

	DefaultCameraMatrix.ProjectionMatrix 	= glm::perspective(FOV, AspectRatio, NearPlane, FarPlane);
	DefaultCameraMatrix.ViewMatrix 		= glm::lookAt(PositionVector, PositionVector + DirectionVector, UpVector);

	DefaultCameraMatrix.IdentityMatrix 	= glm::mat4(1.0f);

	DefaultCameraMatrix.MVP			= DefaultCameraMatrix.ProjectionMatrix * DefaultCameraMatrix.ViewMatrix * DefaultCameraMatrix.IdentityMatrix;
}


















void CAMERA::FaceCameraRight()
{
	Horizontal 		= (3*M_PI)/2.0f;
	Vertical 		= (11.0f*M_PI)/6.0f;

	PositionVector		= glm::vec3(300.0f, 80.0f, -80.0f);

	DefaultCameraMatrix.ProjectionMatrix 	= glm::perspective(FOV, AspectRatio, NearPlane, FarPlane);
	DefaultCameraMatrix.ViewMatrix 		= glm::lookAt(PositionVector, PositionVector + DirectionVector, UpVector);

	DefaultCameraMatrix.IdentityMatrix 	= glm::mat4(1.0f);

	DefaultCameraMatrix.MVP			= DefaultCameraMatrix.ProjectionMatrix * DefaultCameraMatrix.ViewMatrix * DefaultCameraMatrix.IdentityMatrix;
}


void CAMERA::FaceCameraLeft()
{
	Horizontal 		= M_PI/2.0f;
	Vertical 		= (11.0f*M_PI)/6.0f;

	PositionVector		= glm::vec3(-300.0f, 80.0f, -80.0f);

	DefaultCameraMatrix.ProjectionMatrix 	= glm::perspective(FOV, AspectRatio, NearPlane, FarPlane);
	DefaultCameraMatrix.ViewMatrix 		= glm::lookAt(PositionVector, PositionVector + DirectionVector, UpVector);

	DefaultCameraMatrix.IdentityMatrix 	= glm::mat4(1.0f);

	DefaultCameraMatrix.MVP			= DefaultCameraMatrix.ProjectionMatrix * DefaultCameraMatrix.ViewMatrix * DefaultCameraMatrix.IdentityMatrix;
}

void CAMERA::FaceCameraFront()
{
	Horizontal 		= M_PI;
	Vertical 		= (11.0f*M_PI)/6.0f;

	PositionVector		= glm::vec3(0.0f, 150.0f, 100.0f);

	DefaultCameraMatrix.ProjectionMatrix 	= glm::perspective(FOV, AspectRatio, NearPlane, FarPlane);
	DefaultCameraMatrix.ViewMatrix 		= glm::lookAt(PositionVector, PositionVector + DirectionVector, UpVector);

	DefaultCameraMatrix.IdentityMatrix 	= glm::mat4(1.0f);

	DefaultCameraMatrix.MVP			= DefaultCameraMatrix.ProjectionMatrix * DefaultCameraMatrix.ViewMatrix * DefaultCameraMatrix.IdentityMatrix;
}

void CAMERA::FaceCameraBack()
{
	Horizontal 		= 0.0f;
	Vertical 		= (11.0f*M_PI)/6.0f;

	PositionVector		= glm::vec3(0.0f, 150.0f, -200.0f);

	DefaultCameraMatrix.ProjectionMatrix 	= glm::perspective(FOV, AspectRatio, NearPlane, FarPlane);
	DefaultCameraMatrix.ViewMatrix 		= glm::lookAt(PositionVector, PositionVector + DirectionVector, UpVector);

	DefaultCameraMatrix.IdentityMatrix 	= glm::mat4(1.0f);

	

	DefaultCameraMatrix.MVP			= DefaultCameraMatrix.ProjectionMatrix * DefaultCameraMatrix.ViewMatrix * DefaultCameraMatrix.IdentityMatrix;
}


void CAMERA::RotateCameraAngle(const float _CameraAngle)
{
	//DefaultCameraMatrix.ViewMatrix = glm::lookAt(glm::vec3(0.0f, 5.0f, 1.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

       	DefaultCameraMatrix.ViewMatrix = glm::rotate(DefaultCameraMatrix.ViewMatrix, _CameraAngle, glm::vec3(0.0f, 0.0f, 1.0f)); 

	//DefaultCameraMatrix.ProjectionMatrix = glm::perspective(FOV, AspectRatio, NearPlane, FarPlane);
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

	//RotateCameraAngle(CameraAngle);
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

	//RotateCameraAngle(CameraAngle);
}

