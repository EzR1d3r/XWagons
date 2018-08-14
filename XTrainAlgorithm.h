#include "XTrain.h"

class XTrainAlgorithm
{
public:
	XTrainAlgorithm():__wag_count(0), __steps(0){}
	inline uint getSteps() const { return __steps; }
	inline uint getCount() const { return __wag_count; }
	virtual void to_count(XTrain train) = 0;
protected:
	uint __wag_count;
	uint __steps;
};

class XDirectAlgorithm:public XTrainAlgorithm
{
public:
	virtual void to_count (XTrain train) override;
};

class XBinaryAlgorithm:public XTrainAlgorithm
{
public:
	virtual void to_count (XTrain train) override;
protected:
	void goForwardAndSwitch(XTrain &train, uint count);
private:
	void binary_search(XTrain &train, bool control_state);
};


class XBinaryAdvAlgorithm:public XBinaryAlgorithm
{
public:
	virtual void to_count (XTrain train) override;
protected:
	void goForwardAndSet(XTrain &train, uint count, bool light);
};
