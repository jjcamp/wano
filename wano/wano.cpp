#include "wano.h"

using namespace wano;
using namespace std;
using namespace curses;

int main(int argc, char* argv[]) {
	auto win = Curses::InitScr();
	Curses::Raw();
	Curses::NoNL();
	Curses::NoEcho();
	win.keyPad(TRUE);
	Color::Start();

	auto menu = Menu();
	shared_ptr<Document> doc;
	if (argc > 1) {
		File openFile = File(argv[1]);
		if (!openFile.exists())
			doc = make_shared<Document>();
		else
			doc = make_shared<Document>(openFile.createDocument());
	}
	else
		doc = make_shared<Document>();
	services::currentDocument::set(doc);
	auto ta = TextArea(doc);
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

