#ifndef GUI_H_
#define GUI_H_

#include "common.h"
#include <stdbool.h>

typedef struct appdata {
	Evas_Object *win;
#if defined(USES_ELM_EVAS)
	Evas_Object *conform;
#endif
} appdata_s;

bool create_gui(/*appdata_s* app_data*/);
void quit(animator_callback_gui_shared_info_s*);
#endif /* GUI_H_ */
