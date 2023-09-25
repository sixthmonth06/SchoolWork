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
	float x = click_x - circle_center_x;
	float y = click_y - circle_center_y;
	float distance = x * x + y * y; //not using square root, use square of distance to compare instead
	if (distance <= (diameter/2) * (diameter/2)) {
		return 1;
	}
	return 0;
}

int AreCirclesIntersecting(float c1_x, float c1_y, float r1, float c2_x, float c2_y, float r2)
{
	CP_Vector positionOne = CP_Vector_Set(c1_x, c1_y);
	CP_Vector positionTwo = CP_Vector_Set(c2_x, c2_y);
	float distance = CP_Vector_Distance(positionOne, positionTwo);

	if (distance < r1 + r2) {
		return 1;
	}
	return 0;
}

int wall_collision(CP_Vector position, CP_Vector direction, 
	CP_Vector movement_speed, float diameter, int width, int height) {

	CP_Vector dir = CP_Vector_Scale(direction, diameter/2);
	CP_Vector change_in_position = CP_Vector_Add(dir, movement_speed);
	CP_Vector new_position = CP_Vector_Add(position, change_in_position);
	if (new_position.x <= 3 || new_position.x >= width - 3) {
		return 1;
	}
	if (new_position.y <= 3 || new_position.y >= height - 3) {
		return 1;
	}
	return 0;
}


