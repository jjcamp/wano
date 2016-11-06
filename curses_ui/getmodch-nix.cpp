#ifdef __unix__
#include "getmodch.h"
#include <vector>

#include <iostream>

namespace curses {
	int getModCh(Window& win, ModifierState* modState) {
		const size_t MAX_SCANCODE_LENGTH = 4;
		auto input = std::vector<int>();
		input.push_back(win.getCh());
		win.noDelay(true);
		for (int i = 1; i < MAX_SCANCODE_LENGTH; i++) {
			int ch;
			if (!win.tryGetCh(&ch))
				break;
			input.push_back(ch);
		}
		win.noDelay(false);

		*modState = 0;

		if (input.size() == 2 && input[0] == 27) {
			*modState |= GETCH_ALT;
			return input[1];
		}
		return input[0];
	}
}
#endif