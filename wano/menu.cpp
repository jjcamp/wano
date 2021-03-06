#include <sstream>
#include "menu.h"
#include "services.h"
#include "commonfunctions.h"

using namespace std;
using namespace curses;
using namespace curses_ui;

namespace wano {
	Menu::Menu() :
		win(1, 0, 0, 0),
		items(),
		docx{ 1 },
		docy{ 1 } {
		Colors::instance.addIfMissing(MENU_COLOR_KEY, Color::BLACK, Color::WHITE);
		Colors::instance.addIfMissing(MENU_HOTKEY_COLOR_KEY, Color::WHITE, Color::BLACK);

		// If a panel is the same number of lines as another one fits
		// inside the other, (pd?)curses will not redraw.
		auto fileMenuItems = vector<MenuItem>{
			MenuItem("&New", "Ctrl+N", [] {}),
			MenuItem("&Open", "Ctrl+O", [] {}),
			MenuItem("&Save", "Ctrl+S", functions::saveCurrentDocument),
			MenuItem("Save &As", "", [] {}),
			MenuItem("E&xit", "", [] { services::events::get().fire(EXIT_WANO, true); })
		};

		auto editMenuItems = vector<MenuItem>{
			MenuItem("&Undo", "Ctrl+Z", [] {}),
			MenuItem("R&edo", "Ctrl+Y", [] {})
		};

		auto helpMenuItems = vector<MenuItem>{
			MenuItem("&About", "", [] { MsgBox::show("About wano", MsgBox::B_OK); })
		};

		items.push_back(sub{ "&File", 'f', Submenu(move(fileMenuItems), 2, 1) });
		items.push_back(sub{ "&Edit", 'e', Submenu(move(editMenuItems), 2, 6) });
		items.push_back(sub{ "&Help", 'h', Submenu(move(helpMenuItems), 2, 11) });

		services::events::get().addHandler<coord>(DOC_MOVE, [this](auto c) {
			this->updatePos(c.y + 1, c.x + 1);
		});
	}

	const Window& Menu::getWindow() {
		return win;
	}

	void Menu::draw() {
		win.move(0, 0);
		win.clrToEOL();
		Colors::instance.set(win, MENU_COLOR_KEY);
		win.addCh(' ');
		for (const auto& i : items) {
			auto hotkeyed = false;
			for (const auto& c : i.label) {
				if (c == '&') {
					hotkeyed = true;
					continue;
				}
				if (hotkeyed)
					Colors::instance.set(win, MENU_HOTKEY_COLOR_KEY);
				win.addCh(c);
				if (hotkeyed) {
					Colors::instance.set(win, MENU_COLOR_KEY);
					hotkeyed = false;
				}
			}
			win.addCh(' ');
		}
		// TODO roll into separate function so less needs to be redrawn
		auto posStream = ostringstream();
		posStream << "Ln " << docy << ", Col " << docx;
		auto posString = posStream.str();
		auto numSpaces = win.getMaxX() - (posString.length() + win.getX() + 1);
		for (auto i = 0; i < numSpaces; i++)
			win.addCh(' ');
		win.addStr(posString.c_str());
		win.insCh(' ');

		Colors::instance.unset(win, MENU_COLOR_KEY);
		win.refresh();
	}

	void Menu::updatePos(const int ln, const int col) {
		docy = ln;
		docx = col;
		this->draw();
	}

	void Menu::focus(int ch) {
		auto res = Submenu::SubmenuResult::CONTINUE;
		auto curSub = 0;
		for (; curSub < items.size(); curSub++) {
			if (ch == items[curSub].hotkey) {
				res = items[curSub].submenu.show();
				break;
			}
		}
		while (res != Submenu::SubmenuResult::EXIT) {
			switch (res) {
			case Submenu::SubmenuResult::RIGHT:
				if (curSub + 1 != items.size())
					curSub++;
				res = items[curSub].submenu.show();
				continue;
			case Submenu::SubmenuResult::LEFT:
				if (curSub != 0)
					curSub--;
				res = items[curSub].submenu.show();
				continue;
			}
		}
	}
}