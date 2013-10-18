
#include "../headers/bridgescene.h"


void CORE::DrawBeams()
{
	float x = 0.0f;
	float z = 0.0f;
	float y = 0.0f;

	objects->BindObject(0);

	generic_shader->ChangeUniformColor(255.0f, 206.0f, 153.0f);	

	y = 76.0f;
	z = -40.0f;

	for(x = 4.0f; x < 128.0f; x += 8.0f)
	{
		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, z));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();
		MatrixStack.pop();
	}

	for(x = -4.0f; x > -128.0f; x += -8.0f)
	{
		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, z));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();
		MatrixStack.pop();
	}


	// Sloped end
	//
	y = 75.0f;
	
	for(x = 132.0f; x < 224.0f; x += 8.0f)
	{
		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, z));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(355.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();
		MatrixStack.pop();

		y -= 1.0;
	}
}

void CORE::DrawUnderBeams()
{
	float x = 0.0f;
	float y = 0.0f;
	float yu = 0.0f;
	float zf = 0.0f;
	float zb = 0.0f;
	float zm = 0.0f;

	objects->BindObject(7);

	generic_shader->ChangeUniformColor(200.0f, 150.0f, 100.0f);	

	y = 72.0f;
	yu = 70.0f; 
	zf = 0.0f;
	zb = -80.0f;
	zm = -40.0f;

	// Under Beam
	for(x = 0.0f; x < 128.0f; x += 32.0f)
	{

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zf));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zm));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zb));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();
		MatrixStack.pop();

	}

	for(x = 0.0f; x > -128.0f; x += -32.0f)
	{

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zf));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zm));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zb));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();
		MatrixStack.pop();
	}
	

	objects->BindObject(8);

	generic_shader->ChangeUniformColor(200.0f, 150.0f, 100.0f);	

	float rotx = 0.0f;
	float roty = 270.0f;
	float rotz = 90.0f;
	for(x = 0.0f; x < 160.0f; x += 32.0f)
	{
		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zf));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_ONE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zm));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_ONE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zb));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_ONE();
		MatrixStack.pop();


		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zf));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_TWO();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zm));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_TWO();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zb));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_TWO();
		MatrixStack.pop();


		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zf));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_THREE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zm));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_THREE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zb));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_THREE();
		MatrixStack.pop();
	}

	for(x = 0.0f; x > -128.0f; x += -32.0f)
	{

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zf));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_ONE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zm));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_ONE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zb));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_ONE();
		MatrixStack.pop();


		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zf));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_TWO();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zm));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_TWO();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zb));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_TWO();
		MatrixStack.pop();


		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zf));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_THREE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zm));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_THREE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zb));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_THREE();
		MatrixStack.pop();
	}

	// End
	
	objects->BindObject(7);

	generic_shader->ChangeUniformColor(200.0f, 150.0f, 100.0f);	

	y = 71.0f;
	yu = 67.0f; 
	zf = 0.0f;
	zb = -80.0f;
	zm = -40.0f;

	for(x = 128.0f; x < 224.0f; x += 32.0f)
	{

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zf));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(5.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zm));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(5.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zb));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(5.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();
		MatrixStack.pop();

		y -= 3;
	}

	objects->BindObject(8);

	generic_shader->ChangeUniformColor(200.0f, 150.0f, 100.0f);	

	rotx = 355.0f;
	roty = 270.0f;
	rotz = 90.0f;
	for(x = 160.0f; x < 256.0f; x += 32.0f)
	{
		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zf));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(rotx, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_ONE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zm));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(rotx, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_ONE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zb));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(rotx, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_ONE();
		MatrixStack.pop();


		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zf));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(rotx, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_TWO();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zm));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(rotx, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_TWO();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zb));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(rotx, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_TWO();
		MatrixStack.pop();


		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zf));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(rotx, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_THREE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zm));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(rotx, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_THREE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, yu, zb));
			RotateModelMatrix(rotz, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(roty, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(rotx, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawUnderBeamRound_THREE();
		MatrixStack.pop();

		yu -= 3;
	}
}

void CORE::DrawLegs()
{
	objects->BindObject(2);

	generic_shader->ChangeUniformColor(221.0f, 183.0f, 152.0f);	

	for(float x = 32.0f; x < 128.0f; x += 64.0f)
	{
		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, 0.0f, -16.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawLegs_ONE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, 0.0f, -16.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawLegs_TWO();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, 0.0f, -16.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawLegs_THREE();
		MatrixStack.pop();


		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, 0.0f, -64.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawLegs_ONE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, 0.0f, -64.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawLegs_TWO();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, 0.0f, -64.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawLegs_THREE();
		MatrixStack.pop();
	}

	for(float x = -32.0f; x > -128.0f; x += -64.0f)
	{
		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, 0.0f, -16.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawLegs_ONE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, 0.0f, -16.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawLegs_TWO();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, 0.0f, -16.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawLegs_THREE();
		MatrixStack.pop();


		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, 0.0f, -64.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawLegs_ONE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, 0.0f, -64.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawLegs_TWO();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, 0.0f, -64.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawLegs_THREE();
		MatrixStack.pop();
	}
}

void CORE::DrawLegSupport()
{
	float y = 0.0f;
	float zf = 0.0f;
	float zb = 0.0f;
	float rotx = 90.0f;
	float roty = 0.0f;
	float rotz = 0.0f;

	objects->BindObject(9);

	generic_shader->ChangeUniformColor(221.0f, 183.0f, 22.0f);	
	
	y  = 60.0f;
	zf = -40.0f;
	zb = -88.0f;
	for(float x = 32.0f; x < 128.0f; x += 64.0f)
	{
		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zf));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(rotx, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawLegSupport_ONE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zf));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(rotx, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawLegSupport_TWO();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zf));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(rotx, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawLegSupport_THREE();
		MatrixStack.pop();
		

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zb));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(rotx, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawLegSupport_ONE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zb));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(rotx, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawLegSupport_TWO();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zb));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(rotx, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawLegSupport_THREE();
		MatrixStack.pop();
	}

	for(float x = -32.0f; x > -128.0f; x += -64.0f)
	{
		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zf));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(rotx, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawLegSupport_ONE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zf));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(rotx, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawLegSupport_TWO();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zf));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(rotx, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawLegSupport_THREE();
		MatrixStack.pop();
		

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zb));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(rotx, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawLegSupport_ONE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zb));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(rotx, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawLegSupport_TWO();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zb));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(rotx, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawLegSupport_THREE();
		MatrixStack.pop();
	}
}

void CORE::DrawRails()
{
	float zf = 0.0f;
	float zb = 0.0f;
	float y = 0.0f;

	objects->BindObject(1);

	generic_shader->ChangeUniformColor(230.0f, 201.0f, 179.0f);	

	zf = 10.0f;
	zb = -90.0f;
	y = 78.0f;
	for(float x = 16.0f; x < 128.0f; x += 32.0f)
	{
		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zf));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zb));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();
		MatrixStack.pop();
	}

	for(float x = -16.0f; x > -128.0f; x += -32.0f)
	{
		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zf));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zb));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();
		MatrixStack.pop();
	}

	objects->BindObject(4);

	zf = 10.0f;
	zb = -90.0f;
	y = 88.0f;
	for(float x = 0.0f; x < 160.0f; x += 32.0f)
	{
		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zf));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawHalfCylinder_ONE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zf));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawHalfCylinder_TWO();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zf));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawHalfCylinder_THREE();
		MatrixStack.pop();
		

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zb));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawHalfCylinder_ONE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zb));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawHalfCylinder_TWO();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zb));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawHalfCylinder_THREE();
		MatrixStack.pop();
	}

	for(float x = 0.0f; x > -128.0f; x += -32.0f)
	{

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zf));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawHalfCylinder_ONE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zf));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawHalfCylinder_TWO();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zf));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawHalfCylinder_THREE();
		MatrixStack.pop();
		

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zb));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawHalfCylinder_ONE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zb));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawHalfCylinder_TWO();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zb));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawHalfCylinder_THREE();
		MatrixStack.pop();
	}


	// Sloped end
	objects->BindObject(1);

	zf = 10.0f;
	zb = -90.0f;
	y = 75.0f;
	for(float x = 143.0f; x < 223.0f; x += 32.0f)
	{
		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zf));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zb));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();
		MatrixStack.pop();
		y -= 3;
	}

	objects->BindObject(4);

	zf = 10.0f;
	zb = -90.0f;
	y = 85.0f;
	for(float x = 159.0f; x < 253.0f; x += 32.0f)
	{
		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zf));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(5.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawHalfCylinder_ONE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zf));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(5.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawHalfCylinder_TWO();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zf));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(5.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawHalfCylinder_THREE();
		MatrixStack.pop();
		

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zb));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(5.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawHalfCylinder_ONE();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zb));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(5.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawHalfCylinder_TWO();
		MatrixStack.pop();

		MatrixStack.push(camera->DefaultCameraMatrix.MVP);
			TranslateModelMatrix(glm::vec3(x, y, zb));
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			RotateModelMatrix(5.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawHalfCylinder_THREE();
		MatrixStack.pop();

		y -= 3;
	}
}

void CORE::DrawGateOne()
{
	float zf = 0.0f;
	float zb = 0.0f;
	float y = 0.0f;
	float x = 0.0f;

	objects->BindObject(1);

	generic_shader->ChangeUniformColor(230.0f, 201.0f, 179.0f);	

	zf = 10.0f;
	zb = -90.0f;
	y = 72.0f;
	x = 225.0f;
	//y = 0.0f;
	//x = 0.0f;


	if(AnimateGateOne == true)
	{
		if(AnimateGateOneClose == true)
		{
			AnimateAngleOne += 1.0;

			if(AnimateAngleOne > 90.0f)
			{
				AnimateGateOne = false;
				AnimateGateOneOpen = true;
				AnimateGateOneClose = false;
				AnimateAngleOne = 90.0f;
			}
			//std::cout << "[DEBUG] +Angle: " << AnimateAngleOne << std::endl;
		}

		if(AnimateGateOneOpen == true)
		{
			AnimateAngleOne -= 1.0;

			if(AnimateAngleOne < 0.0f)
			{
				AnimateGateOne = false;
				AnimateGateOneClose = true;
				AnimateGateOneOpen = false;
				AnimateAngleOne = 0.0f;
			}
			//std::cout << "[DEBUG] -Angle: " << AnimateAngleOne << std::endl;
		}
	}

	MatrixStack.push(camera->DefaultCameraMatrix.MVP);

		TranslateModelMatrix(glm::vec3(x, y, zf));
		generic_shader->UpdateUniformModel(MatrixStack.top());


		RotateModelMatrix(AnimateAngleOne, glm::vec3(0.0f, 1.0f, 0.0f));
		generic_shader->UpdateUniformModel(MatrixStack.top());


			TranslateModelMatrix(glm::vec3(0.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();

			TranslateModelMatrix(glm::vec3(24.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();

			TranslateModelMatrix(glm::vec3(24.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();
		

			TranslateModelMatrix(glm::vec3(-48.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());


			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());

				TranslateModelMatrix(glm::vec3(8.0f, -10.0f, 0.0f));
				generic_shader->UpdateUniformModel(MatrixStack.top());
				objects->DrawCube();

				TranslateModelMatrix(glm::vec3(0.0f, -24.0f, 0.0f));
				generic_shader->UpdateUniformModel(MatrixStack.top());
				objects->DrawCube();
			
				// Reset
				TranslateModelMatrix(glm::vec3(-8.0f, 34.0f, 0.0f));
				generic_shader->UpdateUniformModel(MatrixStack.top());

				TranslateModelMatrix(glm::vec3(-4.0f, -10.0f, 0.0f));
				generic_shader->UpdateUniformModel(MatrixStack.top());
				objects->DrawCube();

				TranslateModelMatrix(glm::vec3(0.0f, -24.0f, 0.0f));
				generic_shader->UpdateUniformModel(MatrixStack.top());
				objects->DrawCube();

		TranslateModelMatrix(glm::vec3(4.0f, 34.0f, 0.0f));
		generic_shader->UpdateUniformModel(MatrixStack.top());

	MatrixStack.pop();
}

void CORE::DrawGateTwo()
{
	float zf = 0.0f;
	float zb = 0.0f;
	float y = 0.0f;
	float x = 0.0f;

	objects->BindObject(1);

	generic_shader->ChangeUniformColor(230.0f, 201.0f, 179.0f);	

	zf = -90.0f;
	zb = -90.0f;
	y = 72.0f;
	x = 225.0f;
	//y = 0.0f;
	//x = 0.0f;

	if(AnimateGateTwo == true)
	{
		if(AnimateGateTwoClose == true)
		{
			AnimateAngleTwo -= 1.0;

			if(AnimateAngleTwo < -90.0f)
			{
				AnimateGateTwo = false;
				AnimateGateTwoOpen = true;
				AnimateGateTwoClose = false;
				AnimateAngleTwo = -90.0f;
			}
			//std::cout << "[DEBUG] -Angle: " << AnimateAngleTwo << std::endl;
		}

		if(AnimateGateTwoOpen == true)
		{
			AnimateAngleTwo += 1.0;

			if(AnimateAngleTwo > 0.0f)
			{
				AnimateGateTwo = false;
				AnimateGateTwoClose = true;
				AnimateGateTwoOpen = false;
				AnimateAngleTwo = 0.0f;
			}
			//std::cout << "[DEBUG] +Angle: " << AnimateAngleTwo << std::endl;
		}

	}

	MatrixStack.push(camera->DefaultCameraMatrix.MVP);

		TranslateModelMatrix(glm::vec3(x, y, zf));
		generic_shader->UpdateUniformModel(MatrixStack.top());


		RotateModelMatrix(AnimateAngleTwo, glm::vec3(0.0f, 1.0f, 0.0f));
		generic_shader->UpdateUniformModel(MatrixStack.top());


			TranslateModelMatrix(glm::vec3(0.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();

			TranslateModelMatrix(glm::vec3(24.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();

			TranslateModelMatrix(glm::vec3(24.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());
			objects->DrawCube();
		

			TranslateModelMatrix(glm::vec3(-48.0f, 0.0f, 0.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());


			RotateModelMatrix(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			generic_shader->UpdateUniformModel(MatrixStack.top());

				TranslateModelMatrix(glm::vec3(8.0f, -10.0f, 0.0f));
				generic_shader->UpdateUniformModel(MatrixStack.top());
				objects->DrawCube();

				TranslateModelMatrix(glm::vec3(0.0f, -24.0f, 0.0f));
				generic_shader->UpdateUniformModel(MatrixStack.top());
				objects->DrawCube();
			
				// Reset
				TranslateModelMatrix(glm::vec3(-8.0f, 34.0f, 0.0f));
				generic_shader->UpdateUniformModel(MatrixStack.top());

				TranslateModelMatrix(glm::vec3(-4.0f, -10.0f, 0.0f));
				generic_shader->UpdateUniformModel(MatrixStack.top());
				objects->DrawCube();

				TranslateModelMatrix(glm::vec3(0.0f, -24.0f, 0.0f));
				generic_shader->UpdateUniformModel(MatrixStack.top());
				objects->DrawCube();

		TranslateModelMatrix(glm::vec3(4.0f, 34.0f, 0.0f));
		generic_shader->UpdateUniformModel(MatrixStack.top());

	MatrixStack.pop();
}

void CORE::DrawLampPole()
{
}

void CORE::DrawLamp()
{
}

void CORE::DrawFloor()
{
	objects->BindObject(3);

	generic_shader->ChangeUniformColor(61.0f, 245.0f, 0.0f);	

	for(float x = 0.0f; x < 256.0f; x += 16.0f)
	{
		for(float z = 54.0f; z > -256.0f; z += -16.0f)
		{
			MatrixStack.push(camera->DefaultCameraMatrix.MVP);
				TranslateModelMatrix(glm::vec3(x, 0.0f, z));
				ScaleModelMatrix(glm::vec3(16.0f, 0.0f, 16.0f));
				generic_shader->UpdateUniformModel(MatrixStack.top());
				objects->DrawSquare();
			MatrixStack.pop();
		}
	}
	
	for(float x = 0.0f; x > -256.0f; x -= 16.0f)
	{
		for(float z = 54.0f; z > -256.0f; z += -16.0f)
		{
			MatrixStack.push(camera->DefaultCameraMatrix.MVP);
				TranslateModelMatrix(glm::vec3(x, 0.0f, z));
				ScaleModelMatrix(glm::vec3(16.0f, 0.0f, 16.0f));
				generic_shader->UpdateUniformModel(MatrixStack.top());
