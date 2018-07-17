#pragma once

#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>


class XWagon
{
public:
	XWagon(): __light(false) {}
	XWagon(const XWagon& wag){std::cout << "copy wag " << wag.__light;}
	XWagon(bool bLight):__light (bLight){}
	inline bool getLight() const {return __light;}
	inline void setLight(bool bLight){__light = bLight;}
private:
	bool __light;
};

class XTrain
{
public:
	XTrain(int randomise){ srand( randomise ); }
	inline int getCurrent () const { return __current; }
	inline int getCount () const { return __count; }
	inline void setCurrent(int c){__current = c;}
	inline void setCount(int c){ __Wagons.resize(c); __count = c;}
	void reset();
	int step_next();
	int step_prev();

	bool setRandCount( int min, int max);
	void setRandLight();

	void printTrain();
	int getMask() const;
private:
	int __count = 0;
	int __current = 0;
	int __steps = 0;
	std::vector<XWagon> __Wagons;
};
