#pragma once

#include <memory>
#include <stdexcept>
#define PDC_WIDE
#include <curses.h>

// nCurses contains a border macro, which we don't use, so undefine it to prevent errors
#undef border

namespace curses {
	using chType = chtype;

	struct CursesException : public std::exception {
		const char* what() const throw() {
			return "Curses Exception";
		}
	};

	struct Color {
		static constexpr int BLACK = COLOR_BLACK;
		static constexpr int BLUE = COLOR_BLUE;
		static constexpr int GREEN = COLOR_GREEN;
		static constexpr int RED = COLOR_RED;
		static constexpr int CYAN = COLOR_CYAN;
		static constexpr int MAGENTA = COLOR_MAGENTA;
		static constexpr int YELLOW = COLOR_YELLOW;
		static constexpr int WHITE = COLOR_WHITE;

		static constexpr int Pair(int n) { return COLOR_PAIR(n); }

		static void Start();
		static void InitPair(short pair, short f, short b);
	};

	class Window {
	public:
		Window(const int nlines, const int ncols, const int begin_y, const int begin_x);
		Window(WINDOW* win);
		void leaveOk(const bool bf);
		void noDelay(const bool bf);
		void addCh(const chType ch);
		void insCh(const chType ch);
		int getCh() const;
		void addStr(const char* cstr);
		void move(const int y, const int x);
		void refresh();
		void attrOn(const chType attrs);
		void attrOff(const chType attrs);
		void keyPad(const bool bf);
		void clrToEOL();
		int getMaxX() const;
		int getMaxY() const;
		int getX() const;
		int getY() const;
		void border(chType ls, chType rs, chType ts, chType bs, chType tl,	chType tr, chType bl, chType br);
	private:
		std::unique_ptr<WINDOW, int(*)(WINDOW*)> win;
	};

	class Curses {
	public:
		static Window InitScr();
		static void Raw();
		static void NoEcho();
		static void EndWin();
		static void NoNL();
	};
}