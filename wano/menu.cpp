#include "menu.h"

using namespace std;
using namespace curses;

namespace wano {
	Menu::Menu(EventQueue* eq) :
		win(1, 0, 0, 0),
		items(),
		eq{ eq },
		docx{ 0 },
		docy{ 0 }
	{
		items.push_back(MenuItem("&File"));
		items.push_back(MenuItem("&Edit"));
		items.push_back(MenuItem("F&ormat"));
		items.push_back(MenuItem("&View"));
		items.push_back(MenuItem("&Help"));

		eq->addHandler<coord>(DOC_MOVE, [this](coord c) {
			this->updatePos(c.y, c.x);
		});
	}

	const Window& Menu::getWindow() {
		return win;
	}

	void Menu::draw() {
		win.move(0, 0);
		win.clrToEOL();
		// Menu Color
		Color::InitPair(1, Color::BLACK, Color::CYAN);
		// Hotkey letter color
		Color::InitPair(2, Color::RED, Color::CYAN);
		win.attrOn(Color::Pair(1));
		win.addCh(' ');
		for (const auto& i : items) {
			i.draw(win);
			win.addCh(' ');
		}
		// TODO: This is disgusting but I need it for further textarea work
		char buf[15];
		int len = sprintf_s(buf, "Ln %d, Col %d", docy, docx);
		int numSpaces = win.getMaxX() - (len + win.getX() + 1);
		for (int i = 0; i < numSpaces; i++) {
			win.addCh(' ');
		}
		for (int i = 0; i < len; i++) {
			win.addCh(buf[i]);
		}
		// Insert the last character to keep the cursor from moving and thus
		// going out of bounds
		win.insCh(' ');

		win.attrOff(Color::Pair(1));
		win.refresh();
	}

	void Menu::updatePos(const int ln, const int col) {
		docy = ln;
		docx = col;
		this->draw();
	}
}