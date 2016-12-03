#include "menu.h"
#include "textarea.h"
#include "events.h"
#include "file.h"
#include "document.h"
#include "nameddocument.h"
#include "services.h"
#include "hotkeys.h"
#include "configure.h"
#include "commonfunctions.h"

using namespace wano;
using namespace std;
using namespace curses;

bool exit_wano = false;

int main(int argc, char* argv[]) {
	auto win = Curses::InitScr();
	Curses::Raw();
	Curses::NoNL();
	Curses::NoEcho();
	win.keyPad(TRUE);
	Color::Start();

	configureColors();
	auto hotkeys = Hotkeys::defaults();
	services::events::get().addHandler<bool>(EXIT_WANO, [] (auto b) { exit_wano = b; });

	auto menu = Menu();
	unique_ptr<NamedDocument> namedDoc;
	if (argc > 1) {
		File openFile = File(argv[1]);
		namedDoc = make_unique<NamedDocument>(NamedDocument::fromFile(openFile));
	}
	else
		namedDoc = make_unique<NamedDocument>(make_shared<Document>());
	services::currentNamedDocument::set(*namedDoc);
	auto ta = TextArea(namedDoc->document());
	ta.keyPad(TRUE);
	menu.draw();
	while (!exit_wano) {
		ModifierState keyMods;
		int ch = getModCh(ta, &keyMods);
		if (keyMods & GETCH_ALT)
			menu.focus(ch);
		else if (keyMods & GETCH_CTRL)
			hotkeys.handleCh(ch);
		else
			ta.handleCh(ch);
	}
	Curses::EndWin();

	return 0;
}

