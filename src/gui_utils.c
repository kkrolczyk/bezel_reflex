#include "gui_utils.h"
#include "game_config.h"

Evas_Object* initialize_popup(Evas* evas)
{
	Evas_Object* central = evas_object_text_add(evas);
	evas_object_text_text_set(central, "click & go!");
	evas_object_text_font_set(central, "ARIAL", 30);
	evas_object_color_set(central, 255, 0, 0, 255);
	evas_object_move(central, CENTER_X-70, CENTER_Y);
	evas_object_resize(central, 30, 30);
	evas_object_show(central);
	return central;
}

Evas_Object* initialize_background(Evas* evas)
{
	/* White background, with no alpha (opaqe) */
	Evas_Object* background = evas_object_rectangle_add(evas);
	evas_object_color_set(background, UNPACK_COLOR_ALPHA(0xFFFFFFFF));
	evas_object_resize(background, WIDTH, HEIGHT);
	evas_object_show(background);
	return background;
}


void initial_dash_rotation(Evas_Object *dash, Evas_Coord x, Evas_Coord y, double rotation)
{
	/* initial placement rotation. Place dash/rectangle and rotate around each's center */
	Evas_Map *dash_map;
	if (0 != rotation){
		dash_map = evas_map_new(4);
		evas_map_util_points_populate_from_object(dash_map, dash);
		evas_map_util_rotate(dash_map, rotation, x + DASH_LEN/2, y + DASH_LEN/2);
		evas_object_map_set(dash, dash_map);
		evas_object_map_enable_set(dash, EINA_TRUE);
		/* evas_map_util_object_move_sync_set(dash_map, TRUE); */
		evas_map_free(dash_map);
	}
}

Evas_Object** initialize_dashes(Evas* evas)
{
	char path[MAX_PATH_LEN];
	Evas_Object **dashes = malloc(sizeof(Evas_Object*)*DASHES_COUNT);
	if(NULL == dashes){
		dlog_print(DLOG_FATAL, TAG, "\n failed to allocate memory for dashes! \n");
		exit(-1); /* todo: cleanup required, or system provides? */
	}

	/* Initialize dashes - using DASHES_INIT from game_config.c */
	for (int i=0;i<DASHES_COUNT;i++){
		snprintf(path, MAX_PATH_LEN, "%s/%s", resources_path, DASHES_INIT[i].filename);
	#if defined(USES_ECORE_EVAS)
		dashes[i] = evas_object_image_add(evas);
		evas_object_image_file_set(dashes[i], path, NULL);
		// check_error(dashes[i]);
		// Required: set starting position & size of at image object area.
		// But actually fails to load svg, for some reason
		evas_object_image_fill_set(dashes[i], 0, 0, DASH_LEN, DASH_THICKNESS);
		// Required: set size
		evas_object_resize(dashes[i], DASH_LEN, DASH_THICKNESS);
	#elif defined(USES_ELM_EVAS)
		dashes[i] = elm_image_add(ad->conform);
		elm_image_file_set(dashes[i], path, NULL);
		check_error(dashes[i]);
		// NOT Required: set position on image object area
		evas_object_size_hint_weight_set(dashes[i], EVAS_HINT_FILL, EVAS_HINT_FILL);
		// Required: set size
		evas_object_resize(dashes[i], DASH_LEN, DASH_THICKNESS);
	#endif
		// Required: set position
		evas_object_move(dashes[i], DASHES_INIT[i].x, DASHES_INIT[i].y);

		// needed by me - save key data, to match "filenaname" when ball hits it
		evas_object_data_set(dashes[i], "filename", DASHES_INIT[i].filename);

		// Setup initial rotation
		initial_dash_rotation(dashes[i], DASHES_INIT[i].x, DASHES_INIT[i].y, DASHES_INIT[i].rotation);

		evas_object_show(dashes[i]);
	}
	return dashes;
}

Eina_Bool popup_zoom_effect(Evas_Object *popup, double pos)
{
	Evas_Map *map;
	int x, y, w, h;
	double zoom = (pos * 1.0) + 0.2;
	map = evas_map_new(4);

	evas_object_geometry_get(popup, &x, &y, &w, &h);
	evas_map_util_points_populate_from_object(map, popup);
	evas_map_util_zoom(map, zoom, zoom, x + w / 2, y + h / 2);
	evas_object_map_set(popup, map);
	evas_object_map_enable_set(popup, EINA_TRUE);
	evas_map_free(map);

	if (pos == 1.0) {
		evas_object_hide(popup);
	}
	return EINA_TRUE;
}

void popup_stay(void* object, char* text)
{
	popup_text(object, text);
	ecore_animator_timeline_add(1.1, evas_object_show, object);
}

void popup_text(void* object, char* text)
{
	int hacky_x_offset = (strlen(text) + 1) * 6;
	evas_object_text_text_set(object, text);
	evas_object_show(object);
	evas_object_move(object, CENTER_X-hacky_x_offset, CENTER_Y);
	ecore_animator_timeline_add(1.0, popup_zoom_effect, object);
}
