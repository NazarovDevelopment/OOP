#include "quadtree.h"

bool CoolRectangle::point_in(const CoolPoint& point)
{
	return upper_left <= point && lower_right >= point;
}
