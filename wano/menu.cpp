#include "menu.h"

using namespace std;
using namespace curses;
using namespace curses_ui;

namespace wano {
	Menu::Menu() :
		win(1, 0, 0, 0),
		items(),
		docx{ 1 },
		docy{ 1 } {
		// If a panel is the same number of lines as another one fits
		// inside the other, (pd?)curses will not redraw.
		
		auto fileMenuItems = vector<MenuItem>{
			MenuItem("&New", "Ctrl+N", [] {}),
			MenuItem("&Open", "Ctrl+O", [] {}),
			MenuItem("&Save", "Ctrl+S", [] {
				auto& ndoc = services::currentNamedDocument::get();
				if (!ndoc.hasFile())
					return;
				ndoc.toFile();
			}),
			MenuItem("Save &As", "", [] {}),
			MenuItem("E&xit", "", [] {})
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
		// Menu Color
		Color::InitPair(1, Color::BLACK, Color::CYAN);
		// Hotkey letter color
		Color::InitPair(2, Color::RED, Color::CYAN);
		// Highlighted Color
		Color::InitPair(3, Color::CYAN, Color::BLACK);
		// Highlighted Hotkey Color
		Color::InitPair(4, Color::WHITE, Color::BLACK);
		win.attrOn(Color::Pair(1));
		win.addCh(' ');
		for (const auto& i : items) {
			auto highlight = false;
			for (const auto& c : i.label) {
				if (c == '&') {
					highlight = true;
					continue;
				}
				if (highlight)
					win.attrOn(Color::Pair(2));
				win.addCh(c);
				if (highlight) {
					win.attrOn(Color::Pair(1));
					highlight = false;
				}
			}
			win.addCh(' ');
		}
		// TODO roll into separate function so less needs to be redrawn
		auto posStream = ostringstream();
		posStream << "Ln " << docy << ", Col " << docx;
		auto posString = posStream.str();
		int numSpaces = win.getMaxX() - (posString.length() + win.getX() + 1);
		for (auto i = 0; i < numSpaces; i++)
			win.addCh(' ');
		win.addStr(posString.c_str());
		win.insCh(' ');

		win.attrOff(Color::Pair(1));
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