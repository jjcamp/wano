#ifdef _WIN32
#include "getmodch.h"

namespace curses {
	int getModCh(Window& win, ModifierState* modState) {
		PDC_save_key_modifiers(true);
		int ch = win.getCh();
		*modState = PDC_get_key_modifiers();
		// might need another solution, as this one breaks alt keycodes
		if (*modState & GETCH_ALT)
			ch -= 320; // translate to lowercase
		PDC_save_key_modifiers(false);

		return ch;
	}
}
#endif