#include "game_engine.h"
#include "game_config.h"
#include "balls_management.h"

static const double REFRESH_SPEED = 1.0/50;

void animator_setup(animator_callback_gui_shared_info_s* common_data)
{
	debug_only("%s","animator_setup");
	ecore_animator_frametime_set(REFRESH_SPEED);
	common_data->dash_animator = ecore_animator_add(animator_rotate_dashes, common_data);
	common_data->balls_animator = ecore_animator_add(animator_spawns_balls, common_data);
	ecore_animator_freeze(common_data->dash_animator);
	ecore_animator_freeze(common_data->balls_animator);
}

void animator_cleanup(animator_callback_gui_shared_info_s* data_packed)
{
	ecore_animator_del(data_packed->dash_animator);
	ecore_animator_del(data_packed->balls_animator);
	//TODO: anyone needs evas_object_del(); ?
}

Eina_Bool animator_rotate_dashes(animator_callback_gui_shared_info_s *common_data)
{
	int i;
	static int curr_step = 1;
	if (common_data->rotation.direction == LEFT){
		curr_step--;
	} else {
		curr_step++;
	}
	double angle = curr_step * common_data->game.rotation_degree * common_data->game.turning_speed * REFRESH_SPEED;
	Evas_Coord x,y,w,h;
	Evas_Object **dashes = common_data->gui.dashes; /* array! */
	Evas_Map *dashes_maps[DASHES_COUNT];
	for (i=0;i<DASHES_COUNT;i++)
	{
		dashes_maps[i] = evas_map_new(4);
		evas_object_geometry_get(dashes[i], &x, &y, &w, &h);
		evas_map_util_points_populate_from_object(dashes_maps[i], dashes[i]);
		evas_map_util_rotate(dashes_maps[i], DASHES_INIT[i].rotation, x + DASH_LEN/2, y + DASH_LEN/2);
		evas_map_util_rotate(dashes_maps[i], angle, CENTER_X, CENTER_Y);
		evas_object_map_set(dashes[i], dashes_maps[i]);
		evas_object_map_enable_set(dashes[i], EINA_TRUE);
		evas_map_free(dashes_maps[i]);
	}

	#ifdef does_not_want_inertion
		if (--common_data->steps == 0)
	#endif
			ecore_animator_freeze(common_data->dash_animator);

	return ECORE_CALLBACK_RENEW;
}

Eina_Bool animator_spawns_balls(animator_callback_gui_shared_info_s *common_data){
	create_ball(common_data);
	ecore_animator_freeze(common_data->balls_animator); //spawn single ball and stop
	return ECORE_CALLBACK_RENEW;
}
