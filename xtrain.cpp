#include "xtrain.h"

void XTrain::reset()
{
	__current = 0;
}

int XTrain::next_wag()
{
	__current = __current + 1 < __Wagons.size() ? __current + 1 : 0;
//	__steps++ ;
	return __current;
}

int XTrain::prev_wag()
{
	__current = __current - 1 == 0 ? 0 : __current - 1;
//	__steps++ ;
	return __current;
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
