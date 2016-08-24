#include "curses_obj.h"

using namespace std;

namespace curses {
	Window Curses::InitScr() {
		return move(Window(initscr()));
	}

	void Curses::Raw() {
		if (raw() == ERR) {
			throw CursesException();
		}
	}

	void Curses::NoEcho() {
		if (noecho() == ERR) {
			throw CursesException();
		}
	}

	void Curses::EndWin() {
		if (endwin() == ERR) {
			throw CursesException();
		}
	}

	void Curses::NoNL() {
		if (nonl() == ERR) {
			throw CursesException();
		}
	}
	
	Window::Window(WINDOW* win) :
		win(win, delwin)
	{}

	Window::Window(const int nlines, const int ncols, const int begin_y, const int begin_x) :
		win(newwin(nlines, ncols, begin_y, begin_x), delwin)
	{}

	void Window::addCh(const chType ch) {
		if (waddch(win.get(), ch) == ERR) {
			throw CursesException();
		}
	}

	void Window::insCh(const chType ch) {
		if (winsch(win.get(), ch) == ERR) {
			throw CursesException();
		}
	}

	int Window::getCh() const {
		auto ch = wgetch(win.get());
		if (ch == ERR) {
			throw CursesException();
		}
		return ch;
	}

	void Window::addStr(const char* cstr) {
		if (waddstr(win.get(), cstr) == ERR) {
			throw CursesException();
		}
	}

	void Window::refresh() {
		if (wrefresh(win.get()) == ERR) {
			throw CursesException();
		}
	}

	void Window::move(const int y, const int x) {
		if (wmove(win.get(), y, x) == ERR) {
			throw CursesException();
		}
	}

	void Window::leaveOk(const bool bf) {
		if (leaveok(win.get(), bf) == ERR) {
			throw CursesException();
		}
	}

	void Window::noDelay(const bool bf) {
		if (nodelay(win.get(), bf) == ERR) {
			throw CursesException();
		}
	}

	void Window::attrOn(const chType attrs) {
		if (wattron(win.get(), attrs) == ERR) {
			throw CursesException();
		}
	}

	void Window::attrOff(const chType attrs) {
		if (wattroff(win.get(), attrs) == ERR) {
			throw CursesException();
		}
	}

	void Window::keyPad(const bool bf) {
		if (keypad(win.get(), bf) == ERR) {
			throw CursesException();
		}
	}

	void Window::clrToEOL() {
		if (wclrtoeol(win.get()) == ERR) {
			throw CursesException();
		}
	}

	// This works for PDCurses, but may not work for NCurses
	int Window::getMaxX() const {
		return getmaxx(win.get());
	}

	int Window::getMaxY() const {
		return getmaxy(win.get());
	}

	int Window::getX() const {
		return getcurx(win.get());
	}

	int Window::getY() const {
		return getcury(win.get());
	}

	void Window::border(chType ls, chType rs, chType ts, chType bs, chType tl, chType tr, chType bl, chType br) {
		if (wborder(win.get(), ls, rs, ts, bs, tl, tr, bl, br) == ERR) {
			throw CursesException();
		}
	}

	void Color::Start() {
		if (start_color() == ERR) {
			throw CursesException();
		}
	}

	void Color::InitPair(short pair, short f, short b) {
		if (init_pair(pair, f, b) == ERR) {
			throw CursesException();
		}
	}
}