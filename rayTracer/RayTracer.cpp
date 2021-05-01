#include "RayTracer.h"


void RayTracer::AddLens(double distanceFromSource, double radius, double opticalPower, double deviationX, double deviationY)
{
	std::shared_ptr<Lens> lens = std::make_shared<Lens>(distanceFromSource, radius, opticalPower, deviationX, deviationY);
	InsertLens(lens);
	
}

void RayTracer::ChangeLens(int index, double distanceFromSource, double radius, double opticalPower, double deviationX, double deviationY)
{
	std::shared_ptr<Lens> lens = lenses[index];
	//Remove from index
	lens->ChangeLens(distanceFromSource, radius, opticalPower, deviationX, deviationY);
	InsertLens(lens);
}

void RayTracer::InsertLens(std::shared_ptr<Lens> lens)
{

	lenses.push_back(lens);
	
	//for(int i = 0; i < axisLength; i++)// ITERATOR
	//{
	//	if(lenses[i]->distanceFromSource <= lens->distanceFromSource)
	//	{
	//		if(lenses[i]->distanceFromSource == lens->distanceFromSource)
	//		{
	//			//THROW
	//		}
	//		else
	//		{
	//			lenses.push_back(lens); // INSERT WITH ITERATOR
	//			return;
	//		}
	//	}
	//	else if(i == axisLength)
	//	{
	//		lenses.push_back(lens);
	//		return;
	//	}
	//}
}

