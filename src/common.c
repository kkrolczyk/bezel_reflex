#include "common.h"

#include <app.h>
#include <time.h>
#include <stdlib.h>

void init_constants()
{
	resources_path = app_get_resource_path();
	srand(time(NULL));
	MAX_PATH_LEN = 256;
}

#ifdef DEBUG_IMAGE_LOADING
void check_error(Evas_Object *obj)
{
	Evas_Load_Error err = evas_object_image_load_error_get(obj);
	dlog_print(DLOG_DEBUG, TAG, "\n******************************************\n");
	if (err != EVAS_LOAD_ERROR_NONE){
		dlog_print(DLOG_DEBUG, TAG, "Error: could not load image from %p", obj);
	} else {
		dlog_print(DLOG_DEBUG, TAG, "OK, image loaded properly from %p", obj);
	}
	dlog_print(DLOG_DEBUG, TAG, "\n******************************************\n");
}
#else
	void check_error(){} // preferably optimized out
#endif

int get_random()
{
	return rand();
}

int get_random_range(int min_num, int max_num)
{
	int low_num = 0, hi_num = 0;
	if (min_num < max_num){
		low_num = min_num;
		hi_num = max_num + 1;
	} else {
		low_num = max_num + 1;
		hi_num = min_num;
	}
	return (rand() % (hi_num - low_num)) + low_num;
}

point_s move_point_on_angle(int base_x, int base_y, float angle, int length)
{
	point_s new_point; /* stack */
	new_point.x = sin((M_PI * angle) / 180) * length + base_x;
	new_point.y = cos((M_PI * angle) / 180) * length + base_y;
	return new_point;
}
