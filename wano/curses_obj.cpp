#include "curses_obj.h"

using namespace std;

namespace curses {
	Window InitScr() {
		return initscr();
	}

	void Raw() {
		if (raw() == ERR) {
			throw new CursesException();
		}
	}

	void NoEcho() {
		if (noecho() == ERR) {
			throw new CursesException();
		}
	}

	void EndWin() {
		if (endwin() == ERR) {
			throw new CursesException();
		}
	}

	void NoNL() {
		if (nonl() == ERR) {
			throw new CursesException();
		}
	}

	Window::Window(WINDOW* win) :
		win(win, delwin)
	{}

	Window::Window(int nlines, int ncols, int begin_y, int begin_x) :
		win(newwin(nlines, ncols, begin_y, begin_x), delwin)
	{}

	void Window::addCh(int ch) {
		if (waddch(win.get(), ch) == ERR) {
			throw new CursesException();
		}
	}

	void Window::insCh(int ch) {
		if (winsch(win.get(), ch) == ERR) {
			throw new CursesException();
		}
	}

	int Window::getCh() {
		auto ch = wgetch(win.get());
		if (ch == ERR) {
			throw new CursesException();
		}
		return ch;
	}

	void Window::refresh() {
		if (wrefresh(win.get()) == ERR) {
			throw new CursesException();
		}
	}

	void Window::move(int y, int x) {
		if (wmove(win.get(), y, x) == ERR) {
			throw new CursesException();
		}
	}

	void Window::leaveOk(bool bf) {
		if (leaveok(win.get(), bf) == ERR) {
			throw new CursesException();
		}
	}

	void Window::attrOn(int attrs) {
		if (wattron(win.get(), attrs) == ERR) {
			throw new CursesException();
		}
	}

	void Window::attrOff(int attrs) {
		if (wattroff(win.get(), attrs) == ERR) {
			throw new CursesException();
		}
	}

	void Window::keyPad(bool bf) {
		if (keypad(win.get(), bf) == ERR) {
			throw new CursesException();
		}
	}

	void Window::clrToEOL() {
		if (wclrtoeol(win.get()) == ERR) {
			throw new CursesException();
		}
	}

	// This works for PDCurses, but may not work for NCurses
	int Window::getMaxX() {
		return getmaxx(win.get());
	}

	int Window::getMaxY() {
		return getmaxy(win.get());
	}

	int Window::getX() {
		return getcurx(win.get());
	}

	int Window::getY() {
		return getcury(win.get());
	}

	void Color::Start() {
		if (start_color() == ERR) {
			throw new CursesException();
		}
	}

	void Color::InitPair(short pair, short f, short b) {
		if (init_pair(pair, f, b) == ERR) {
			throw new CursesException();
		}
	}
}