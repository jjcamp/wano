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
	unique_ptr<NamedDocument> namedDoc;
	if (argc > 1) {
		File openFile = File(argv[1]);
		doc = make_shared<Document>(openFile.createDocument());
		namedDoc = make_unique<NamedDocument>(doc, openFile);
	}
	else {
		doc = make_shared<Document>();
		namedDoc = make_unique<NamedDocument>(doc);
	}
	services::currentNamedDocument::set(*namedDoc);
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

