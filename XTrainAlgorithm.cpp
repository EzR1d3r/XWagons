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

void XBinaryAlgorithm::goForwardAndSwitch(XTrain &train, uint count)
{
	for (uint i = 1; i <= count; i++)
	{
		train.go_forward(1); //первый текущий вагон не переключаем
		train.getCurrentWag()->switchLight();
	}
}

void XBinaryAlgorithm::binary_search(XTrain &train, bool control_state)
{
	for (uint i = 1;; i*=2)
	{
		uint start = train.getFakeCurrent();
		goForwardAndSwitch(train, i);
		uint end = train.getFakeCurrent();
		train.go_backward( end );
		if (train.getCurrentWag()->getLight() != control_state)
		{
			if (i == 1)
			{
				__steps = train.getSteps();
				__wag_count = end;
				return;
			}
			else
			{
				train.go_forward( start );
				control_state = !control_state;
				binary_search(train, control_state);
				break;
			}
		}
		else
		{
			train.go_forward( end );
		}
	}
}

void XBinaryAlgorithm::to_count(XTrain train)
{
	if ( train.checkCount(0) ) return;
	train.reset();
	binary_search(train, train.getCurrentWag()->getLight());
}


void XBinaryAdvAlgorithm::to_count(XTrain train)
{
	if ( train.checkCount(0) ) return;
	train.reset();
	bool control_state = train.getCurrentWag()->getLight();

	for (uint i = 1;; i*=2)
	{
		uint start = train.getFakeCurrent();
		goForwardAndSwitch(train, i);
		uint end = train.getFakeCurrent();
		train.go_backward( end );
		if (train.getCurrentWag()->getLight() != control_state)
		{
			train.go_forward( start );
			goForwardAndSet(train, i, !control_state);
			train.go_backward( end );
			train.getCurrentWag()->setLight(control_state);
			train.go_forward( start );
			for (uint k = start; k <= end; k++)
			{
				if (train.getCurrentWag()->getLight() == control_state)
				{
					__steps = train.getSteps();
					__wag_count = train.getFakeCurrent() ? train.getFakeCurrent() : 1; //иначе при количестве 1, выдаёт 0
					return;
				}
				train.go_forward(1);
			}
			return;
		}
		else
		{
			train.go_forward( end );
		}
	}
}

void XBinaryAdvAlgorithm::goForwardAndSet(XTrain &train, uint count, bool light)
{
	for (uint i = 1; i <= count; i++)
	{
		train.getCurrentWag()->setLight(light);
		train.go_forward(1);
	}
}
