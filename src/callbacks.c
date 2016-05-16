#include "callbacks.h"

void enable_dash_rotate(animator_callback_gui_shared_info_s* common_data)
{
	ecore_animator_thaw(common_data->dash_animator);
	#ifdef does_not_want_inertion
	ecore_timer_add(1, ecore_animator_freeze, common_data->dash_animator);
	#endif
}

Eina_Bool callback_rotation_event(animator_callback_gui_shared_info_s* common_data, Eext_Rotary_Event_Info *ev)
{
   if (ev->direction == EEXT_ROTARY_DIRECTION_CLOCKWISE)
   {
      //dlog_print(DLOG_DEBUG, TAG, "ROTARY HANDLER: Rotary device rotated in clockwise direction");
      common_data->rotation.direction = RIGHT;
      common_data->rotation.steps++;
      enable_dash_rotate(common_data);
   }
   else
   {
      //dlog_print(DLOG_DEBUG, TAG, "Rotary device rotated in counter clockwise direction");
      common_data->rotation.direction = LEFT;
      common_data->rotation.steps++;
      enable_dash_rotate(common_data);
   }

   return EINA_FALSE;
   /*
    * From documentation:
    * The rotary event handlers are treated "first come first served".
    * It means that the first registered handler is called first when rotary events happens.
    * If the handler returns EINA_TRUE, the next handler is called.
    * Otherwise, EFL Extension stops delivering the rotary events.
    */
}

void callback_click_event(animator_callback_gui_shared_info_s* common_data, Evas* evas, Evas_Object *obj, void *event_info) {
	ecore_animator_thaw(common_data->balls_animator);
}
