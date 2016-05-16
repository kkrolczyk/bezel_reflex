#include "special_effects.h"

void change_bg_color(Evas* evas, animator_callback_gui_shared_info_s* common_data)
{
	int color = get_random_range(0x11111188, 0xFFFFFFFF); // data_packed->game.bg_color_rgb_a;
	evas_object_color_set(common_data->gui.background, UNPACK_COLOR_ALPHA(color));
}

