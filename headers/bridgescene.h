#ifndef BRIDGESCENE_H
#define BRIDGESCENE_H

#include "../headers/bridgescene.h"

class BRIDGESCENE
{
	public:
		BRIDGESCENE ();
		~BRIDGESCENE ();

		bool 	AnimateGateOneOpen;
		bool 	AnimateGateOneClose;

		bool	AnimateGateTwoOpen;
		bool	AnimateGateTwoClose;

		void 	InitScene();
		void	DrawScene();

	private:

		float	AnimateAngleOne;
		float	AnimateAngleTwo;

		void	DrawFloor();
		void	DrawRails();
		void	DrawBeams();
		void	DrawUnderBeams();
		void	DrawLegs();
		void	DrawLegSupport();
		void	DrawGateOne();
		void	DrawGateTwo();

		void 	DrawLampPole();
		void	DrawLamp();

};

#endif
