// Platform-dependant code here
#pragma once
#include "curses_obj.h"
#include <string>

namespace wano {

	// Checks to see if character is ALT-encoded
	inline bool isAlt(const curses::chType ch) {
#ifdef PDCURSES
		return std::string(keyname(ch)).find("ALT_") != std::string::npos;
#else
		return std::string(keyname(ch)).find("M-") != std::string::npos;
#endif // PDCURSES
	}
}