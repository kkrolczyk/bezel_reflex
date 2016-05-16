#include "game_config.h"

const int DASH_LEN = 168;
const int DASH_THICKNESS = 10;

// emulator offset (correction due to round emulator coords)
#if defined(USES_ELM_EVAS)

	#define emulator_round
	#ifdef emulator_round
		#define OFFSET_X 0
		#define OFFSET_Y -50
		const int WIDTH = 360;
		const int HEIGHT = 360;
	#elif emulator_square
		#define OFFSET_X 0-50
		#define OFFSET_Y 0-50
		const int WIDTH = 320;
		const int HEIGHT = 320;
	#else
		#define OFFSET_X 0
		#define OFFSET_Y 50
		const int WIDTH = 360;
		const int HEIGHT = 360;
	#endif

	const int CENTER_X=(WIDTH/2 - OFFSET_X);
	const int CENTER_Y=(HEIGHT/2 - OFFSET_Y);


		/* careful, rotates around ENDING point ...ALWAYS it is needed to add/remove to both x/y:
		 * half of length ?
		 * rotation ?
		 * distance from center ?
		 * a) when in center - and rotated 90 deg, x should be x = x + len/2
		 */
		dash_info_s DASHES_INIT[] = {

									{"BlackDash.png",			 55-OFFSET_X,			 35-OFFSET_Y,		333},
									{"BlueDash.png",			175-OFFSET_X,			 35-OFFSET_Y,		 27},
									{"GrayDash.png", 			255-OFFSET_X,			135-OFFSET_Y,		 73},
									{"PurpleDash.png",			235-OFFSET_X,			258-OFFSET_Y,		-53},
									{"GreenDash.png",			CENTER_X-DASH_LEN/2,	315-OFFSET_Y,		  0},
									{"RedDash.png",				 -5-OFFSET_X,			258-OFFSET_Y,		 53},
									{"YellowDash.png",			-25-OFFSET_X,			135-OFFSET_Y,		-73},

									/*
									// Test 0 = cross in center
									{"GrayDash.png",   CENTER_X, CENTER_Y,   0},
									{"GrayDash.png",   CENTER_X, CENTER_Y,  45},
									{"GrayDash.png",   CENTER_X, CENTER_Y,  90},

									// Test 1a = cross in center when rotating around center of self
									{"BlackDash.png",   CENTER_X - DASH_LEN/2, CENTER_Y,   0},
									{"BlackDash.png",   CENTER_X - DASH_LEN/2, CENTER_Y,  90},

									// Test 1b = cross in center when rotating around center of screen
									{"BlackDash.png",   CENTER_X - DASH_LEN/2, CENTER_Y,   0},
									{"BlackDash.png",   CENTER_X, CENTER_Y - DASH_LEN/2,  90},

									// Test 3 = crosses at offsets
									{"RedDash.png",   -100 + CENTER_X, CENTER_Y - 50,   0},
									{"RedDash.png",   -100 + CENTER_X + DASH_LEN/2, CENTER_Y - 50 + DASH_LEN/2,  90},
									{"GreenDash.png",        CENTER_X, CENTER_Y - 50,   0},
									{"GreenDash.png",  -50 + CENTER_X, CENTER_Y - DASH_LEN,  90},

									// Test 4 = should have common point, also, after offset change - it relations should stay the same
									{"PurpleDash.png",   100-OFFSET_X,   150-OFFSET_Y,   45},
									{"BlueDash.png",     100-OFFSET_X,   150-OFFSET_Y,   10},
									{"YellowDash.png",   100-OFFSET_X,   150-OFFSET_Y,    0},
									*/

									};

#elif defined(USES_ECORE_EVAS)
	#define OFFSET_X 0
	#define OFFSET_Y -10
	const int WIDTH = 360;
	const int HEIGHT = 360;
	const int CENTER_X = (WIDTH/2);
	const int CENTER_Y = (HEIGHT/2);

	dash_info_s DASHES_INIT[] = {

//								{"BlackDash.png",			 75-OFFSET_X,			 25-OFFSET_Y,		333},
//								{"BlueDash.png",			155-OFFSET_X,			 25-OFFSET_Y,		 27},
//								{"GrayDash.png", 			200-OFFSET_X,			 92-OFFSET_Y,		 77},
//								{"PurpleDash.png",			275-OFFSET_X,			240-OFFSET_Y,		-53},
//								{"GreenDash.png",			CENTER_X-DASH_LEN/2,	315-OFFSET_Y,		  0},
//								{"RedDash.png",				-45-OFFSET_X,			240-OFFSET_Y,		 53},
//								{"YellowDash.png",			 30-OFFSET_X,			 92-OFFSET_Y,		-77},

// changed to 6 elements
	#define SKEW_OFFSET_UP 42
	#define SKEW_OFFSET_DOWN 23

			{"dash_blue.png",		CENTER_X-OFFSET_X-DASH_LEN/2,	 	18-OFFSET_Y,										  0},
			{"dash_green.png",		CENTER_X-OFFSET_X-DASH_LEN/2,		315-OFFSET_Y,										  0},

			{"dash_purple.png",		 295-OFFSET_X,						CENTER_Y-OFFSET_Y+SKEW_OFFSET_DOWN,					-60},
			{"dash_red.png",		-100-OFFSET_X,						CENTER_Y-OFFSET_Y+SKEW_OFFSET_DOWN,					 60},

			{"dash_gray.png", 		 160-OFFSET_X,						CENTER_Y-OFFSET_Y-DASH_LEN/2-SKEW_OFFSET_UP,		 60},
			{"dash_yellow.png",		  35-OFFSET_X,						CENTER_Y-OFFSET_Y-DASH_LEN/2-SKEW_OFFSET_UP,		-60},
	};
	#undef SKEW_OFFSET_UP
	#undef SKEW_OFFSET_DOWN
	// converting css coords to this => swap X/Y   +  offset  + ??
	// need proper length + css gives coords as end coords x,y here we need starting coords

#endif
const char* BALLS_FILENAMES[] = {"ball_blue.png", "ball_gray.png","ball_purple.png",
								 "ball_green.png","ball_red.png","ball_yellow.png"};

const int DASHES_COUNT = sizeof(DASHES_INIT)/sizeof(DASHES_INIT[0]);
const int BALL_DEFAULT_SIZE = 25;


ball_info_s BALL_DEFAULT_INIT = {
		.x = CENTER_X-BALL_DEFAULT_SIZE/2,
		.y = CENTER_Y-BALL_DEFAULT_SIZE/2,
		.size = BALL_DEFAULT_SIZE,
		.angle = 0,
		.speed = 3,
		//.color_rgb_a = 0xFFFFFFFF, /* rgb + alpha, black, solid(opaqe) */
		.type = BALL_TYPE_NORMAL,
		.filename = "fallback_error.png"
};

game_info_s GAME_DEFAULT_INIT = {
		.score = 0l,
		.game_mode = BALL_BOUNCES_FROM_DASH_AND_CENTER,
		.turning_speed = 5,				/* 1 = fluent turning */
		.rotation_degree = 120,			/* 100 = fluent turning */
		.distance_from_last_shot = 1,
		.balls_cnt = 0,
		.bg_color_rgb_a = 0x000000FF, /* white, solid(opaqe) */
};
