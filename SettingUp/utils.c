#include <math.h>
#include "cprocessing.h"

int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y)
{
	float x_range_lower = area_center_x - (area_width / 2);
	float x_range_upper = area_center_x + (area_width / 2);
	float y_range_lower = area_center_y - (area_height / 2);
	float y_range_upper = area_center_y + (area_height / 2);
	if (click_x >= x_range_lower && click_x <= x_range_upper) {
		if (click_y >= y_range_lower && click_y <= y_range_upper) {
			return 1;
		}
	} 
	return 0;
}

int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y)
{
}
