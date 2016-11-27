#ifdef __unix__
#include "curses_obj.h"
#include "term-nix.h"

namespace curses {
	namespace nix {
		termios termios_old;

		void setup_term() {
			if (tcgetattr(0, &termios_old) != 0)
				throw CursesException();
			termios termios_new = termios_old;
			termios_new.c_iflag &= ~IXON;
			termios_new.c_lflag &= ~ISIG;
			if (tcsetattr(0, TCSANOW, &termios_new) != 0)
				throw CursesException();
		}

		void restore_term() {
			if (tcsetattr(0, TCSANOW, &termios_old) != 0)
				throw CursesException();
		}
	}
}

#endif