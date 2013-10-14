
#ifndef CAMERA_H
#define CAMERA_H

#include <stdexcept>
#include <memory>

#include <string>
#include <stack>

#include <iostream>
#include <fstream>
#include <sstream>

#include <ctime>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/type_ptr.hpp>

class CAMERA
{
	public:
		
		CAMERA();
		CAMERA(const float WINDOW_WIDTH, const float WINDOW_HEIGHT, const float FOV, const float NearPlane, const float FarPlane);
		~CAMERA();

		struct CameraMatrix 
		{
			glm::mat4 IdentityMatrix;
			glm::mat4 ViewMatrix;
			glm::mat4 ProjectionMatrix;
			glm::mat4 MVP;
		};

		CameraMatrix 	DefaultCameraMatrix;
		CameraMatrix	FPSCameraMatrix;

		void		UpdateDefaultCamera();

		void		SetFPSCamera();

		void		MoveMouseCamera(const float x, const float y, const float DeltaTime);

		void		StrafeCameraRight(const float DeltaTime);
		void		StrafeCameraLeft(const float DeltaTime);
		void		MoveCameraForward(const float DeltaTime);
		void		MoveCameraBackward(const float DeltaTime);


		void 		ComputeVectors();

		void		UpdateMVP();
		

		void 		SetDefaultCamera();

		void		FaceCameraRight();
		void		FaceCameraLeft();
		void		FaceCameraFront();
		void		FaceCameraBack();


		void		RotateCameraLeft();
		void 		RotateCameraRight();
		void		RotateCameraAngle(const float CameraAngle);

	private:

		float	 	WINDOW_WIDTH;
		float 		WINDOW_HEIGHT;

		float		AspectRatio;
		float 		FOV;	
		float 		NearPlane;
		float 		FarPlane;

		float		Speed;

		float		MouseSensitivity;

		float 		CameraAngle;

		float 		Horizontal;
		float 		Vertical;

		glm::vec3	RightVector;
		glm::vec3	PositionVector;
		glm::vec3	DirectionVector;
		glm::vec3	UpVector;


};

#endif

