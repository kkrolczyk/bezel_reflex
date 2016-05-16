#ifndef BALLS_MANAGEMENT_H_
#define BALLS_MANAGEMENT_H_

#include "common.h"

Eina_Bool animator_move_ball(ball_info_s* common_data);

void create_ball(animator_callback_gui_shared_info_s* common_data);
void delete_ball(ball_info_s* ball);
void morph_ball(ball_info_s* ball);
void repaint_ball(ball_info_s* ball);

Eina_Bool item_in_allowed_range(ball_info_s* ball);

#endif /* BALLS_MANAGEMENT_H_ */
