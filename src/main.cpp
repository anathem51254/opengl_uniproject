
#include "../headers/core.h"


int main(int argc, char** argv)
{
	CORE *core = new CORE;
	core->Start();
	delete core;
	
	return 0;
}
