#include "xtrain.h"

void XTrain::reset()
{
	__steps = 0;
	__current = 0;
}

int XTrain::step_next()
{
	__current = __current + 1 < __Wagons.size() ? __current + 1 : 0;
	__steps++ ;
	return __steps;
}

int XTrain::step_prev()
{
	__current = __current - 1 == 0 ? 0 : __current - 1;
	__steps++ ;
	return __steps;
}

void XTrain::printTrain()
{
	std::cout << "\n";
	for (unsigned int i = 0; i < __Wagons.size(); i++)
	{
		std::cout  << "W_" << i << "_(" << __Wagons[i].getLight() << ")  ";
	}
	std::cout << "\n mask=" << getMask();
}

int XTrain::getMask() const
{
	int mask = 0;
	for (const auto &wag:__Wagons)
	{
		mask = wag.getLight() ? (mask<<1) + 1: (mask<<1);
	}
	return mask;
}
