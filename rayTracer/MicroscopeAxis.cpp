#include "MicroscopeAxis.h"


void MicroscopeAxis::AddLens(double distanceFromSource, double radius, double opticalPower, double deviationX, double deviationY)
{
	std::shared_ptr<Lens> lens = std::make_shared<Lens>(distanceFromSource, radius, opticalPower, deviationX, deviationY);
	InsertLens(lens);
}



void MicroscopeAxis::ChangeLensDistanceFromSource(int index, double distance)
{
	if(index > _lensCount - 1)
	{
		//THROW
	}
	
	_lenses[index]->SetDistanceFromSource(distance);
	std::shared_ptr<Lens> lens = _lenses[index];
	RemoveLens(index);
	InsertLens(lens);
}


void MicroscopeAxis::InsertLens(const std::shared_ptr<Lens>& lens)
{
	int i = 0;
	for(std::vector<std::shared_ptr<Lens>>::iterator it = _lenses.begin(); it != _lenses.end(); it++ , i++)
	{
		if(_lenses[i]->distanceFromSource() >= lens->distanceFromSource())
		{
			if(_lenses[i]->distanceFromSource() == lens->distanceFromSource())
			{
				//THROW
			}else
			{
				_lenses.insert(it, lens);
				_lensCount++;
				return;
			}
		}
	}
	_lenses.push_back(lens);
	_lensCount++;
}

void MicroscopeAxis::RemoveLens(int index)
{
	if(_lensCount == 0)
	{
		//THROW
	}

	int i = 0;
	for(std::vector<std::shared_ptr<Lens>>::iterator it = _lenses.begin(); it != _lenses.end(); it++, i++)
	{
		if(i == index)
		{
			_lenses.erase(it);
			_lensCount--;
			return;
		}
	}
	
}


const std::shared_ptr<Lens> MicroscopeAxis::GetLens(int index)
{
	if(index > _lensCount - 1)
	{
		//THROW
	}
	return _lenses[index];
}

void MicroscopeAxis::AddRay(double angleX, double angleY, double positionX, double positionY, double sourceDistance)
{
	std::shared_ptr<Ray> ray = std::make_shared<Ray>(angleX, angleY, positionX, positionY, sourceDistance,this->_rayCount);
	_rays.push_back(ray);
	_rayCount++;
}

void MicroscopeAxis::RemoveRay(int index)
{
	if(_rayCount <= 0)
	{
		//THROW
	}

	int i = 0;
	for(std::vector<std::shared_ptr<Ray>>::iterator it = _rays.begin(); it != _rays.end(); it++, i++)
	{
		if(i == index)
		{
			_rays.erase(it);
			_rayCount--;
			return;
		}
	}
}

const std::shared_ptr<Ray> MicroscopeAxis::GetRay(int index)
{
	if(index > _rayCount - 1)
	{
		//THROW
	}
	return _rays[index];
}



