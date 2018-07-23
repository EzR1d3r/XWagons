#include "XTrainAlgorithm.h"

void XDirectAlgorithm::to_count(XTrain train)
{
	if (!train.getCurrentWag()) return;
	train.reset();
	bool control_state = train.getCurrentWag()->getLight();
	uint counter = 0;
	uint steps_to_control_wag = 0;

	while (true)
	{
		train.go_forward(1);
		counter++;
		steps_to_control_wag++;
		if (train.getCurrentWag()->getLight() == control_state)
		{
			train.getCurrentWag()->switchLight();
			train.go_backward( steps_to_control_wag );
			counter += steps_to_control_wag;

			if ( train.getCurrentWag()->getLight() != control_state )
			{
				__wag_count = steps_to_control_wag;
				__steps = counter;
				return;
			}
			else
			{
				train.go_forward( steps_to_control_wag );
				counter += steps_to_control_wag;
			}
		}
	}
}

void XBinaryAlgorithm::to_count(XTrain train)
{
	if (!train.getCurrentWag()) return;
	train.reset();
	bool control_state = train.getCurrentWag()->getLight();
	uint counter = 0;
	uint steps_to_control_wag = 0;
}
