#pragma once

#include "QDebug"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>

typedef unsigned int uint;

struct std_rand
{
	std_rand(){ srand( time(0) );}
	uint operator()(uint min, uint max){return (min + rand()%(max + 1 - min)); }
};

class XWagon
{
public:
	XWagon(): __light(false) {}
	XWagon(bool bLight):__light (bLight){}
	inline bool getLight() const {return __light;}
	inline void setLight(bool bLight){__light = bLight;}
	inline void switchLight() { setLight(!__light); }
private:
	bool __light;
};

class XTrain
{
public:
	XWagon * getWagAt (uint idx);
	XWagon * getCurrentWag ();
	inline uint getCurrentWagIDX() const { return __current; }
	inline uint getCount () const { return __Wagons.size(); }
	inline void setCurrent(uint c){__current = c;}
	inline int getFakeCurrent () const { return __fake_current;}
	inline uint getSteps () const {return __steps;}
	inline void setCount(uint c){ __Wagons.resize(c); }
	inline bool checkCount(uint count) const {return __Wagons.size() == count;}
	void reset();
	int go_forward(uint steps);
	int go_backward(uint steps);

	template<typename rand_func = std_rand > void setRandLight(rand_func _rand = std_rand())
	{
		for (auto &wag:__Wagons) wag.setLight( _rand(0, 1) );
	}
	void printTrain();
	int getMask() const;
private:
	uint __steps = 0;
	uint __current = 0;
	int __fake_current = 0;
	std::vector<XWagon> __Wagons;
};
