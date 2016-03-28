#include "menuitem.h"

using namespace std;
using namespace curses;

namespace wano {
	MenuItem::MenuItem(string text)
		: text{ text } {
	}

	void MenuItem::draw(Window* menu) {
		auto isUnderlined = false;
		for (auto c : text) {
			if (c == '&') {
				isUnderlined = true;
			}
			else {
				if (isUnderlined) {
					menu->attrOn(Color::Pair(2));
				}
				menu->addCh(c);
				if (isUnderlined) {
					menu->attrOff(Color::Pair(2));
					menu->attrOn(Color::Pair(1));
					isUnderlined = false;
				}
			}
		}
	}
}
