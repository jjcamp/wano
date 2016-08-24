#include "wano.h"
#include <iostream>

using namespace wano;
using namespace std;
using namespace curses;

int main() {
	auto win = InitScr();
	Raw();
	NoNL();
	win.keyPad(TRUE);
	NoEcho();
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
			cerr << "Alt-" << (char)ch << endl;
		else if (ch == 27)
			break;
		else
			ta.handleCh(ch);
	}
	EndWin();

	return 0;
}

