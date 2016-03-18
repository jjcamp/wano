#pragma once

#include <memory>
#include <stdexcept>
#define PDC_WIDE
#include <curses.h>

namespace curses {
	struct CursesException : public std::exception {
		const char* what() const throw() {
			return "Curses Exception";
		}
	};

	struct Color {
		static const int BLACK = COLOR_BLACK;
		static const int BLUE = COLOR_BLUE;
		static const int GREEN = COLOR_GREEN;
		static const int RED = COLOR_RED;
		static const int CYAN = COLOR_CYAN;
		static const int MAGENTA = COLOR_MAGENTA;
		static const int YELLOW = COLOR_YELLOW;
		static const int WHITE = COLOR_WHITE;

		static inline int Pair(int n) { return COLOR_PAIR(n); }

		static void Start();
		static void InitPair(short pair, short f, short b);
	};

	class Window {
	public:
		Window(int nlines, int ncols, int begin_y, int begin_x);
		Window(WINDOW* win);
		void leaveOk(bool bf);
		void addCh(int ch);
		void insCh(int ch);
		int getCh();
		void move(int y, int x);
		void refresh();
		void attrOn(int attrs);
		void attrOff(int attrs);
		void keyPad(bool bf);
		void clrToEOL();
		int getMaxX();
		int getMaxY();
		int getX();
		int getY();
	private:
		std::unique_ptr<WINDOW, int(*)(WINDOW*)> win;
	};

	Window InitScr();
	void Raw();
	void NoEcho();
	void EndWin();
	void NoNL();
}