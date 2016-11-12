#include "wano.h"
#include <iostream>

using namespace wano;
using namespace std;
using namespace curses;

int main() {
	auto win = Curses::InitScr();
	Curses::Raw();
	Curses::NoNL();
	Curses::NoEcho();
	win.keyPad(TRUE);
	Color::Start();

	auto eq = make_unique<EventQueue>(EventQueue());
	auto menu = Menu(eq.get());
	auto ta = TextArea(eq.get());
	ta.keyPad(TRUE);
	menu.draw();
	while (true) {
		ModifierState keyMods;
		int ch = getModCh(ta, &keyMods);
		if (keyMods & GETCH_ALT)
			menu.focus(ch);
		else if (ch == 27)
			break;
		else
			ta.handleCh(ch);
	}
	Curses::EndWin();

	return 0;
}

