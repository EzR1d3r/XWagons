#include <cmath>
#include "XTrainAlgorithm.h"

void XDirectAlgorithm::to_count(XTrain train)
{
	if ( train.checkCount(0) ) return;
	train.reset();
	bool control_state = train.getCurrentWag()->getLight();

	while (true)
	{
		train.go_forward(1);
		if (train.getCurrentWag()->getLight() == control_state)
		{
			train.getCurrentWag()->switchLight();
			__wag_count = train.getFakeCurrent();
			train.go_backward( __wag_count );

			if ( train.getCurrentWag()->getLight() != control_state )
			{
				__steps = train.getSteps();
				return;
			}
			else
			{
				train.go_forward( __wag_count );
			}
		}
	}
}

void XBinaryAlgorithm::search(XTrain train, uint extent, bool control_state)
{
	for (uint i = 0; i < std::pow(2, extent); i++)
	{
		train.go_forward( i );
		train.getCurrentWag()->switchLight();
	}
}

void XBinaryAlgorithm::to_count(XTrain train)
{
	if (!train.getCurrentWag()) return;
	train.reset();
	bool control_state = train.getCurrentWag()->getLight();
}

