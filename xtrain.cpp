#include "xtrain.h"

void XTrain::setRandCount(unsigned int min, unsigned int max)
{
	srand( time(0) );
	m_Wagons.resize( min + rand()%(max - min) );
}
