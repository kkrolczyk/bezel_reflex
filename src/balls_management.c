#include "balls_management.h"
#include "game_config.h"
#include "gui_utils.h"

#define DIST_FROM_CENTER(x,y) sqrt((x-CENTER_X)*(x-CENTER_X) + (y-CENTER_Y)*(y-CENTER_Y))

Eina_Bool animator_move_ball(ball_info_s* ball)
{
	point_s p = move_point_on_angle(ball->x, ball->y, ball->angle, ball->speed);
	evas_object_move(ball->self, p.x, p.y);
	ball->x = p.x;
	ball->y = p.y;
	animator_callback_gui_shared_info_s *common_data = ((animator_callback_gui_shared_info_s*)ball->parent);

	if(common_data->game.game_mode == BALL_BOUNCES_FROM_DASH_AND_CENTER){
		if (DIST_FROM_CENTER(p.x, p.y) < 15){
			ball->angle = 0; // reverse angle again, ball already morphed
			return ECORE_CALLBACK_RENEW;
		}
	}

	if(item_in_allowed_range(ball)){
		return ECORE_CALLBACK_RENEW;
	} else {
		if (ball->type == BALL_TO_REMOVE){
			delete_ball(ball);
			return ECORE_CALLBACK_CANCEL; // I have no balls ;]
		} else {
			switch (common_data->game.game_mode) {
				case BALL_BOUNCES_FROM_DASH_AND_CENTER:
					morph_ball(ball);
					ball->angle = 180; // reverses ball direction
					return ECORE_CALLBACK_RENEW;
					break; //not reached.

				case BALL_DIES_ON_DASH: // fall through
				default:
					delete_ball(ball);
					return ECORE_CALLBACK_CANCEL;
			}
			return ECORE_CALLBACK_CANCEL; // should reach never.
		}
	}
}


Eina_Bool item_in_allowed_range(ball_info_s* ball)
{
	static const double max_allowed_radius = 180;
	static const double bounce_offset = 53;
	animator_callback_gui_shared_info_s *common_data = ((animator_callback_gui_shared_info_s*)ball->parent);

	Eina_List 	*list;
	Eina_List 	*l;
	Eina_List 	*l_next;
	void		*data_obj;
	char		*filename_dash = NULL;
	char		*filename_ball = NULL;
	char		*test_me = NULL;
	int 	  	ball_size = ball->size;
	int 		x = ball->x;
	int 		y = ball->y;


	if (DIST_FROM_CENTER(x,y) > max_allowed_radius - bounce_offset)
	{
		list = evas_objects_at_xy_get( common_data->gui.evas, x+ball_size/2, y+ball_size/2+10, 1, 0);
		EINA_LIST_FOREACH_SAFE(list, l, l_next, data_obj)
		{
			test_me = evas_object_data_get(data_obj, "filename");
			if (NULL != test_me){
				if (strncmp(test_me, "ball", 4))
					filename_ball = test_me;
				else if (strncmp(test_me, "dash", 4))
					filename_dash = test_me;
			}
		}
		if (filename_dash && filename_ball){ // ball reached dash


			/* TODO: ugly ugly, manage popup and score better */
			char result[32];
			long *score = &(common_data->game.score); /*synchronization?*/
			Evas_Object	*display = common_data->gui.display_score;

			if (strncmp(filename_dash+4, filename_ball+4, 50) == 0){ // COLOR MATCH
				snprintf(result, 30, "%ld", ++(*score));
				popup_text(display, result);
			}
			else {												 	// NO COLOR MATCH
				snprintf(result, 30, "Game over:\n%ld", *score);
				popup_stay(display, result);
				*score = 0;
				ball->type = BALL_TO_REMOVE;
			}
		} else {

			dlog_print(DLOG_FATAL, TAG, "\n %s  %s   %d   %d \n", filename_dash, filename_ball,  x, y);
		}

		return EINA_FALSE;
	}
	else
		return EINA_TRUE;
}

void morph_ball(ball_info_s* ball)
{
	int game_mode = ((animator_callback_gui_shared_info_s*)ball->parent)->game.game_mode;
	// randomize ball
	switch (game_mode){
		case BALL_DIES_ON_DASH:
			/* todo: according to difficulty settings, ball->parent->game.difficulty ? */
			ball->size = get_random_range(20, 30);
			ball->angle = get_random_range(0, 360);
			ball->speed = get_random_range(2, 6);
			ball->type = get_random_range(1, 3);
			break;
		default:
			;
			/* do nothing */
	}

	ball->filename = BALLS_FILENAMES[get_random_range(0, DASHES_COUNT-1)];
	evas_object_data_set(ball->self, "filename", ball->filename);
	repaint_ball(ball);
}

void repaint_ball(ball_info_s* ball)
{
	/* TODO: actually, DO NOT create this img objects but keep them in memory and swap */
	/* TODO: Diff-colored-balls_and_WITH_powerup_and_penalty */
	char path[MAX_PATH_LEN];
	snprintf(path, MAX_PATH_LEN, "%s/%s", resources_path, ball->filename);
	evas_object_image_file_set(ball->self, path, NULL);
	//check_error(ball->self);
	evas_object_image_fill_set(ball->self,  0, 0, ball->size, ball->size);
	evas_object_resize(ball->self, ball->size, ball->size);
	/* keep ball color/filename for fast recognition if hit proper dash color */
	evas_object_data_set(ball->self, "filename", ball->filename);
}

void delete_ball(ball_info_s* ball)
{
	evas_object_del(ball->self);
	ecore_animator_del(ball->animator);
	free(ball);
	((animator_callback_gui_shared_info_s*)ball->parent)->game.balls_cnt--;
}


void create_ball(animator_callback_gui_shared_info_s* common_data)
{
	ball_info_s* ball = malloc(sizeof(ball_info_s));
	if(NULL == ball)
	{
		dlog_print(DLOG_FATAL, TAG, "\n failed to allocate ball memory! \n");
		return;
	}
	else
	{
		memcpy(ball, &BALL_DEFAULT_INIT, sizeof(BALL_DEFAULT_INIT));

		/* TODO: passing structs vs getters api */
		ball->parent = common_data;
		common_data->game.balls_cnt++;


		morph_ball(ball);
		ball->self = evas_object_image_filled_add (((animator_callback_gui_shared_info_s*)ball->parent)->gui.evas);
		repaint_ball(ball);

	/*
	 * say i wanted to use rectangles, not images...
	 *  ball->self = evas_object_rectangle_add(evas);
	 *  evas_object_color_set(ball->self, UNPACK_COLOR_ALPHA(ball->color_rgb_a));
	 *  ball->color_rgb_a = get_random_range(0x11111188, 0xFFFFFFFF);
	 *  evas_object_resize(ball->self, ball->size, ball->size);
	 *  evas_object_data_set(ball->self, "color", ball->color_rgb_a);
	 */
		evas_object_move(ball->self, CENTER_X-ball->size/2, CENTER_Y-ball->size/2);
		evas_object_show(ball->self);

		ball->animator = ecore_animator_add(animator_move_ball, ball);
	}
}
