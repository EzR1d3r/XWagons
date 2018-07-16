#include <vector>
#include <cstdlib>
#include <ctime>


class XWagon
{
public:
	XWagon(){ srand(time(0)); m_bLigt = rand()%2; }
	XWagon(bool bLight):m_bLigt(bLight){}
	inline bool getLight() const {return m_bLigt;}
	inline void setLight(bool bLight){m_bLigt = bLight;}
private:
	bool m_bLigt;
};

class XTrain
{
public:
	inline void getCurrent () const { return __current; }
	inline void getCount () const { return __count; }
	inline void setCurrent(int c){__current = c;}
	inline void setCount(int c){ m_Wagons.resize(c); __count = c;}
	inline void reset(){m_Wagons.clear();}

	void setRandCount (unsigned int min, unsigned int max);
private:
	int __count;
	int __current;
	std::vector<XWagon> m_Wagons;
};
