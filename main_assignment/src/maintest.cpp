
#include "../core.h"


int main(int argc, char** argv)
{
	CORE::Initialise();	
	CORE::MainLoop();
	CORE::CleanUp();

	return 0;
}

