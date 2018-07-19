#pragma once

#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>

typedef unsigned int uint;

template <uint min, uint max> struct std_rand
{
	std_rand(){ srand( time(0) );}
	uint operator()(){return (min + rand()%(max + 1 - min)); }
};

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
	inline int getCurrent () const { return __current; }
	inline int getCount () const { return __Wagons.size(); }
	inline void setCurrent(int c){__current = c;}
	inline void setCount(int c){ __Wagons.resize(c); }
	void reset();
	int step_next();
	int step_prev();

	template<typename rand_func = std_rand<0,1>> void setRandLight(rand_func _rand = std_rand<0,1>())
	{
		for (auto &wag:__Wagons) wag.setLight( _rand() );
	}
	void printTrain();
	int getMask() const;
private:
	unsigned int __current = 0;
	unsigned int __steps = 0;
	std::vector<XWagon> __Wagons;
};
