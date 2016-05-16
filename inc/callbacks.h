#ifndef CALLBACKS_H_
#define CALLBACKS_H_

#include "common.h"

Eina_Bool callback_rotation_event(animator_callback_gui_shared_info_s *data, Eext_Rotary_Event_Info *ev);
void callback_click_event(animator_callback_gui_shared_info_s* data, Evas * evas, Evas_Object *obj, void *event_info);

#endif /* CALLBACKS_H_ */
