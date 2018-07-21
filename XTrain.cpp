#include "XTrain.h"


XWagon *XTrain::getWagAt(uint idx)
{
	try
	{
		return &__Wagons.at(idx);
	}
	catch (std::out_of_range ex)
	{
		qDebug() << ex.what();
		return 0;
	}
}

XWagon *XTrain::getCurrentWag()
{
	XWagon * wag = getWagAt(__current);
	return wag;
}

void XTrain::reset()
{
	__current = 0;
	__fake_current = 0;
}

int XTrain::go_forward(uint steps)
{
	if (__Wagons.size() == 0) return __current;
	__current = (__current + steps)%__Wagons.size();
	__steps+=steps ;
	return __current;
}

int XTrain::go_backward(uint steps)
{
	if (__Wagons.size() == 0) return __current;
	__current = ( __current + __Wagons.size() - steps%__Wagons.size() )%__Wagons.size();;
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
