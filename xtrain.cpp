#include "xtrain.h"

void XTrain::reset()
{
	__current = 0;
	__fake_current = 0;
}

int XTrain::go_forward(uint steps)
{
	__current = (__current + steps)%__Wagons.size();
	__steps+=steps ;
	return __current;
}

int XTrain::go_backward(uint steps) //uint..........
{
	__current = ( (__current - steps)%__Wagons.size() + __Wagons.size() )%__Wagons.size();
	qDebug() << __current;
	qDebug() << ( (0 - 1)%20 +20 )%20;
	__steps+=steps ;
	return __current;
}

void XTrain::printTrain()
{
	std::cout << "\n";
	for (uint i = 0; i < __Wagons.size(); i++)
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
