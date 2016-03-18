#include "menu.h"

using namespace std;
using namespace curses;

namespace wano {
	Menu::Menu(shared_ptr<EventQueue> eq) :
		Window(1, 0, 0, 0),
		items(),
		eq{ eq }
	{
		items.push_back(MenuItem("&File"));
		items.push_back(MenuItem("&Edit"));
		items.push_back(MenuItem("F&ormat"));
		items.push_back(MenuItem("&View"));
		items.push_back(MenuItem("&Help"));

		docx = 0;
		docy = 0;

		eq->addHandler<coord>(DOC_MOVE, [this](coord c) {
			this->updatePos(c.y, c.x);
		});
	}

	void Menu::draw() {
		this->move(0, 0);
		this->clrToEOL();
		// Menu Color
		Color::InitPair(1, Color::BLACK, Color::CYAN);
		// Hotkey letter color
		Color::InitPair(2, Color::RED, Color::CYAN);
		this->attrOn(Color::Pair(1));
		this->addCh(' ');
		for (auto i : items) {
			i.draw(this);
			this->addCh(' ');
		}
		// TODO: This is disgusting but I need it for further textarea work
		char buf[15];
		int len = sprintf_s(buf, "Ln %d, Col %d", docy, docx);
		int numSpaces = this->getMaxX() - (len + this->getX() + 1);
		for (int i = 0; i < numSpaces; i++) {
			this->addCh(' ');
		}
		for (int i = 0; i < len; i++) {
			this->addCh(buf[i]);
		}
		// Insert the last character to keep the cursor from moving and thus
		// going out of bounds
		this->insCh(' ');

		this->attrOff(Color::Pair(1));
		this->refresh();
	}

	void Menu::updatePos(int ln, int col) {
		docy = ln;
		docx = col;
		this->draw();
	}
}