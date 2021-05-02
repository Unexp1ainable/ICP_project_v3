// rayTracer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "RayTracer.h"

//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>


int main()
{
	std::cout << "Hello world!\n";

	RayTracer* rayTracer = new RayTracer();

	for(int i = 1; i < 5; i++)
	{
		rayTracer->AddLens(i, i, i);
	}


	auto lens = rayTracer->lenses[0];
	std::cout << "LENS " << 1 << ": " << lens->radius << std::endl;
	
	for(int i = 0; i < 4; i++)
	{
		auto lens = rayTracer->lenses[i];
		std::cout << "LENS " << i + 1 << ": " << lens->radius << std::endl;
	}

	delete(rayTracer);

	//_CrtDumpMemoryLeaks();
	
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   3. Use the Output window to see build output and other messages
//   2. Use the Team Explorer window to connect to source control
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
