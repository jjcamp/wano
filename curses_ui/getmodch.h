#pragma once

#include <curses.h>
#include "curses_obj.h"

namespace curses {
	// Doing this very c-like because I think it works smoother
	// Also, doing bitwise operations on scoped enums requires
	// overloading each operator, so not gonna bother here
	using ModifierState = unsigned long;
	enum ModifierStateEnum {
		GETCH_SHIFT = 1,	// These mirror PDC_KEY_MODIFER_*
		GETCH_CTRL = 2,
		GETCH_ALT = 4,
		GETCH_NUMLOCK = 8
	};

	int getModCh(Window& win, ModifierState* modState);
}
