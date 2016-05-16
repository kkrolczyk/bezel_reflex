#ifndef GUI_UTILS_H_
#define GUI_UTILS_H_

#include "common.h"

Evas_Object* initialize_popup(Evas* evas);
Evas_Object* initialize_background(Evas* evas);
Evas_Object** initialize_dashes(Evas* evas);


void popup_text(void* temporary, char* text);
void popup_stay(void* temporary, char* text);

#endif /* GUI_UTILS_H_ */
