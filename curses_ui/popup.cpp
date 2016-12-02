#include "popup.h"

using namespace std;
using namespace curses;

namespace curses_ui {
	Popup::Popup(const int nlines, const int ncols, const int begin_y, const int begin_x) :
		panel(nlines + 2, ncols + 2, begin_y > 0 ? begin_y - 1 : 0, begin_x > 0 ? begin_x - 1 : 0) {
		Colors::instance.addIfMissing(MENU_COLOR_KEY, Color::BLACK, Color::WHITE);
		Colors::instance.set(this->panel, MENU_COLOR_KEY);
		panel.border(0, 0, 0, 0, 0, 0, 0, 0);
		Colors::instance.unset(this->panel, MENU_COLOR_KEY);
		panel.move(1, 1);
		panel.keyPad(true);
	}

	Cursor Popup::beforeShow() {
		auto prevCursor = Curses::CursSet(Cursor::INVISIBLE);
		panel.show();
		return prevCursor;
	}

	void Popup::afterShow(curses::Cursor prevCursor) {
		panel.hide();
		Curses::CursSet(prevCursor);
		panel.update();
	}

	int Popup::show() {
		auto prevCursor = this->beforeShow();
		int ch;
		while ((ch = panel.getCh()) != 27) {}
		this->afterShow(prevCursor);
		return 0;
	}

	int Popup::show(function<int(int)> innerLoop) {
		auto prevCursor = this->beforeShow();
		int result;
		while ((result = innerLoop(panel.getCh())) == Result::CONTINUE);
		this->afterShow(prevCursor);
		return result;
	}
}