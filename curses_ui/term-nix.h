#pragma once

#ifdef __unix__
#include <unistd.h>
#include <termios.h>

namespace curses {
	namespace nix {
		void setup_term();
		void restore_term();
	}
}
#else
// These should get optimized away in release builds
namespace curses {
	namespace nix {
		inline void setup_term() { return; }
		inline void restore_term() { return; }
	}
}
#endif