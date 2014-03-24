#include "quadtree.h"

void CoolQuadTree::separate()
{
	CoolPoint center(border.lower_right.x / 2 - border.upper_left.x / 2, border.lower_right.y / 2 - border.upper_left.y / 2);

	CoolRectangle q1(border.upper_left, center);
	CoolRectangle q2(CoolPoint(border.upper_left.x, center.y), CoolPoint(center.x,border.lower_right.y));
	CoolRectangle q3(CoolPoint(center.x,border.upper_left.y),CoolPoint(border.lower_right.x,center.y));
	CoolRectangle q4(center,border.lower_right);

	upper_left = new CoolQuadTree(q1);
	lower_left= new CoolQuadTree(q2);
	upper_right = new CoolQuadTree(q3);
	lower_right = new CoolQuadTree(q4);
}

bool CoolQuadTree::insert(const CoolPoint& point)
{
	if (!border.point_in(point))
	{
		return false;
	}

	if (points.size < NUMBER_POINT){
		points.push_back(point);
	}
}
