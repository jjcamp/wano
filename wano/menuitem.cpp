#include "menuitem.h"

using namespace std;
using namespace curses;

namespace wano {
	MenuItem::MenuItem(string text)
		: text{ text } {
	}

	void MenuItem::draw(Window& menuWindow) const {
		auto isUnderlined = false;
		for (auto c : text) {
			if (c == '&') {
				isUnderlined = true;
			}
			else {
				if (isUnderlined) {
					menuWindow.attrOn(Color::Pair(2));
				}
				menuWindow.addCh(c);
				if (isUnderlined) {
					menuWindow.attrOff(Color::Pair(2));
					menuWindow.attrOn(Color::Pair(1));
					isUnderlined = false;
				}
			}
		}
	}
}
