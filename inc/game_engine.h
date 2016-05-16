#ifndef GAME_ENGINE_H_
#define GAME_ENGINE_H_

#include "common.h"

void animator_setup(animator_callback_gui_shared_info_s*);
void animator_cleanup(animator_callback_gui_shared_info_s*);

Eina_Bool animator_rotate_dashes(animator_callback_gui_shared_info_s*);
Eina_Bool animator_spawns_balls(animator_callback_gui_shared_info_s *data);


#endif /* GAME_ENGINE_H_ */
