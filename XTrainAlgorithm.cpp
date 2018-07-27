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

void XBinaryAlgorithm::switchFromCurrentWag(XTrain &train, uint count)
{
	for (uint i = 1; i <= count; i++)
	{
		train.go_forward(1); //первый текущий вагон не переключаем
		train.getCurrentWag()->switchLight();
	}
}

void XBinaryAlgorithm::search(XTrain &train, bool control_state)
{
	for (uint i = 1;; i*=2)
	{
		uint start = train.getFakeCurrent();
		switchFromCurrentWag(train, i);
		uint end = train.getFakeCurrent();
		train.go_backward( end );
		if (train.getCurrentWag()->getLight() != control_state)
		{
			qDebug() << start << " - " << end;
			train.go_forward( start );
			search(train, !control_state);
			return;
		}
		else
		{
			train.go_forward(end);
		}
	}
}

void XBinaryAlgorithm::to_count(XTrain train)
{
	if ( train.checkCount(0) ) return;
	train.reset();
	search(train, train.getCurrentWag()->getLight());
}

