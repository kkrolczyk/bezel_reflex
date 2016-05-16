#include "gui.h"
#include "gui_utils.h"
#include "callbacks.h"
#include "game_engine.h"
#include "game_config.h"


void quit(animator_callback_gui_shared_info_s *common_data){

	debug_only("%s", "APP QUITS");
	ecore_main_loop_quit();

	/* cleanup */
	free(common_data->gui.dashes);
	animator_cleanup(common_data);
	ecore_evas_free(common_data->gui.ecore_evas);
	ecore_evas_shutdown();
	ecore_shutdown();
	exit(1);
}

bool create_gui(appdata_s* ad)
{
	init_constants();

	Evas *evas;
	Ecore_Evas *ecore_evas;
	Evas_Object *background;
	Evas_Object **dashes;
	Evas_Object *central_popup;

	/* instead of using this evas we have from application, replace it with ecore evas */
	// evas = evas_object_evas_get(ad->win);

	ecore_evas_init();
	ecore_evas = ecore_evas_new(NULL, 0, 0, WIDTH, HEIGHT, NULL);
	ecore_evas_title_set(ecore_evas, "Some internal title name, it seems.");
	ecore_evas_show(ecore_evas);
	evas = ecore_evas_get(ecore_evas);

	debug_only("%s","initialize_background");
	background = initialize_background(evas);
	debug_only("%s","initialize_popup");
	central_popup = initialize_popup(evas);
	debug_only("%s","initialize_dashes");
	dashes = initialize_dashes(evas);

	/* init common shared data */
	animator_callback_gui_shared_info_s common_data = {
			.gui = {evas, dashes, background, central_popup, ecore_evas},
			.game = GAME_DEFAULT_INIT,
			.rotation = {0, 0}
	};

	debug_only("%s","Setup bezel turn callback");
	eext_rotary_event_handler_add(callback_rotation_event, &common_data);
	debug_only("%s","Setup click background callback");
	evas_object_event_callback_add (background, EVAS_CALLBACK_MOUSE_DOWN, callback_click_event, &common_data);
	debug_only("%s","Setup exit from app via back key");
	eext_object_event_callback_add(background, EEXT_CALLBACK_BACK, quit, &common_data);

	debug_only("%s","Setup and run ecore_animator");
	animator_setup(&common_data);
	debug_only("%s","ecore_main_loop_begin()");
	ecore_main_loop_begin();

	/* cleanup - should never reach (cleanup ran by callback - back button) */

	free(dashes);
	animator_cleanup(&common_data);
	ecore_evas_free(ecore_evas);
	ecore_evas_shutdown();
	ecore_shutdown();
	return true;
}

