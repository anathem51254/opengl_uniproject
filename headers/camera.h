
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
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class CAMERA
{
	public:
		
		CAMERA();
		CAMERA(const float WINDOW_WIDTH, const float WINDOW_HEIGHT, const float FOV, const float NearPlane, const float FarPlane);
		~CAMERA();

		struct CameraMatrix 
		{
			glm::mat4 ViewMatrix;
			glm::mat4 ProjectionMatrix;
		};

		CameraMatrix 	DefaultCameraMatrix;


		void 		SetDefaultCamera();
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

		float 		CameraAngle;

};

#endif

