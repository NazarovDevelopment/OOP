#include <iostream>

#include <cstdlib>


struct CoolPoint
{
	double x;
	double y;

	CoolPoint(const double& _x,const double& _y) :x(_x), y(_y){}

	bool operator ==(const CoolPoint& right){
		return (x == right.x) && (y == right.y);
	}

};


struct CoolRectangle
{
	CoolPoint upper_left;
	CoolPoint lower_right;

	CoolRectangle(const CoolPoint& ul, const CoolPoint& lr) :upper_left(ul), lower_right(lr){}

};


class CoolQuadTree
{
public:
	CoolQuadTree(const CoolRectangle& _b) :border(_b){}

private:
	CoolRectangle border;

	CoolQuadTree *upper_left;
	CoolQuadTree *upper_right;
	CoolQuadTree *lower_left;
	CoolQuadTree *lower_right;

};