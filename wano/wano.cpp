#include "wano.h"

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


	auto eq = make_shared<EventQueue>(EventQueue());
	auto menu = Menu(eq);
	auto ta = TextArea(eq);
	ta.keyPad(TRUE);
	menu.draw();
	while (true) {
		int ch = ta.getCh();

		if (ch == 27) {
			break;
		}
		ta.handleCh(ch);
	}
	EndWin();

    return 0;
}

