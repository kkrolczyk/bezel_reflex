#ifndef COMMON_H_
#define COMMON_H_

#define TAG "Bezel Reflex"
/* temporary options */
#define ball_bounces_not_disappears
// #define does_not_want_inertion
// #define DEBUG_IMAGE_LOADING

/* game_config: define USES_ELM_EVAS or USES_ECORE_EVAS */
#define USES_ECORE_EVAS
#define DEBUG
#ifdef DEBUG
#define DEBUG_TEST 1
#else
#define DEBUG_TEST 0
#endif
#define debug_only(fmt, ...) do { if (DEBUG_TEST) dlog_print(DLOG_DEBUG, TAG,"\n" fmt "\n", __VA_ARGS__); } while (0)

#define UNPACK_COLOR(int_rgba) (int_rgba >> 24) & 0xFF,\
				(int_rgba >> 16) & 0xFF,\
				(int_rgba >>  8) & 0xFF

#define UNPACK_COLOR_ALPHA(int_rgba) (int_rgba >> 24) & 0xFF,\
				(int_rgba >> 16) & 0xFF,\
				(int_rgba >>  8) & 0xFF,\
				(int_rgba) & 0xFF


#include <dlog.h>
#include <Elementary.h>
#include <efl_extension.h>
#include "Evas.h"

char* resources_path;
int MAX_PATH_LEN;

void init_constants(void);
void check_error();
int get_random_range(int, int);
int get_random(void);

typedef enum {
	RIGHT, LEFT
} rotation_dir_e;

typedef enum {
	BALL_TO_REMOVE,
	BALL_TYPE_NORMAL,
	BALL_TYPE_POWERUP,
	BALL_TYPE_PENALTY
} ball_type_e;

typedef enum {
	BALL_BOUNCES_FROM_DASH_AND_CENTER,
	BALL_DIES_ON_DASH,
} game_mode_e;

typedef struct {
	rotation_dir_e direction;
	int steps;
} rotation_info_s;

typedef  struct {
	Evas *evas;
	void* dashes;
	Evas_Object *background;
	Evas_Object *display_score;
	Ecore_Evas *ecore_evas;
} gui_state_s;

typedef struct {
	int x;
	int y;
	int size;
	int angle;
	int speed;
	void *parent;			/* todo: name pointer to animator_callback_gui_shared_info_s better */
	union {
		int color_rgb_a;
		const char *filename;
	};
	ball_type_e type;
	Evas_Object *self;
	Ecore_Animator* animator;
} ball_info_s;

/* keeps stuff like score and difficulty */
typedef struct {
	long score;
	game_mode_e game_mode;

	int bg_color_rgb_a;				/* difficulty: might go crazy at higher levels */
	int turning_speed;				/* difficulty: turns slower at higher levels */
	double rotation_degree;			/* difficulty: turns less degrees at higher levels */
	int distance_from_last_shot;	/* difficulty: further distance required at higher levels. Basic - shoots always same place */
	int balls_cnt;					/* TODO: not yet used - needed in difficulty */
} game_info_s;

typedef struct {
	gui_state_s gui;
	game_info_s game;
	rotation_info_s rotation;
	Ecore_Animator* dash_animator;
	Ecore_Animator* balls_animator;
} animator_callback_gui_shared_info_s;

typedef struct {
	int x; int y;
} point_s;

point_s move_point_on_angle(int base_x, int base_y, float angle, int length);

#endif /* COMMON_H_ */

