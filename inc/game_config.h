#ifndef GAME_CONFIG_H_
#define GAME_CONFIG_H_

#include "common.h"

const int WIDTH;
const int HEIGHT;
const int CENTER_X;
const int CENTER_Y;
const int DASH_LEN;
const int DASH_THICKNESS;
const int DASHES_COUNT;
/* hack warning (single element assumed, later expanded) */
const char* BALLS_FILENAMES[];

typedef struct {
	char *filename;
	int x;
	int y;
	double rotation;
} dash_info_s;

/* hack warning (single element assumed, later expanded) */
dash_info_s DASHES_INIT[];
game_info_s GAME_DEFAULT_INIT;
ball_info_s BALL_DEFAULT_INIT;

#endif /* GAME_CONFIG_H_ */
