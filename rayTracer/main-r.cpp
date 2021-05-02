// rayTracer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "MicroscopeAxis.h"

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>


int main()
{
	std::cout << "Hello world!\n";


	int create = 5;
	
	MicroscopeAxis* micAxis = new MicroscopeAxis();

	for(int i = 1; i < create + 1; i++)
	{
		std::cout << "Inserting lens: " << i << std::endl;

		micAxis->AddLens(i, i, i);
	}

	micAxis->AddLens(0.3, 6, 6);
	micAxis->AddLens(19, 7, 7);
	micAxis->RemoveLens(4);
	micAxis->ChangeLensDistanceFromSource(4, 20);

	
	
	for(int i = 0; i < micAxis->lensCount(); i++)
	{
		auto lens = micAxis->GetLens(i);
		std::cout << "LENS " << i + 1 << ": Radius = " << lens->radius() << " Distance = " << lens->distanceFromSource() << std::endl;
	}

	std::cout << std::endl;
	
	for(int i = 1; i < create + 1; i++)
	{
		std::cout << "Inserting ray: " << i << std::endl;

		micAxis->AddRay(i,i,i,i,i);
	}

	micAxis->RemoveRay(3);
	
	for(int i = 0; i < micAxis->rayCount(); i++)
	{
		auto ray = micAxis->GetRay(i);
		std::cout << "RAY " << i + 1 << ": Index = " << ray->index() << " posX = " << ray->position(0) << std::endl;
	}

	
	delete(micAxis);

	_CrtDumpMemoryLeaks();
}
