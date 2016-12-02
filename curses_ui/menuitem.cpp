#include "menuitem.h"
#include "colors.h"

using namespace std;
using namespace curses;

namespace curses_ui {
	MenuItem::MenuItem(std::string&& label, std::string hotkey, std::function<void(void)> callback) :
		label(move(label)),
		hotkey{ hotkey },
		callback{ callback } {
		Colors::instance.addIfMissing(MENU_COLOR_KEY, Color::BLACK, Color::WHITE);
		Colors::instance.addIfMissing(MENU_HOTKEY_COLOR_KEY, Color::WHITE, Color::BLACK);
		Colors::instance.addIfMissing(MENU_HIGHLIGHT_COLOR_KEY, Color::WHITE, Color::BLACK);
		Colors::instance.addIfMissing(MENU_HIGHLIGHT_HOTKEY_COLOR_KEY, Color::BLACK, Color::WHITE);
	}

	const size_t MenuItem::length() const {
		return MenuItem::lengthOfLabel(label) + hotkey.length() + 1;
	}

	const size_t MenuItem::lengthOfLabel(const string& label) {
		if (label.find('&', 0) == string::npos)
			return label.length();
		return label.length() - 1;
	}

	string MenuItem::getLabel(int length) const {
		string outstr = string(this->label);
		auto padding = length - (this->length() - 1);
		for (auto i = 0; i < padding; i++)
			outstr += ' ';
		outstr += hotkey;

		return outstr;
	}

	void MenuItem::draw(Window* win, int length) {
		auto nColor = MENU_COLOR_KEY;
		auto hkColor = MENU_HOTKEY_COLOR_KEY;
		if (this->selected) {
			nColor = MENU_HIGHLIGHT_COLOR_KEY;
			hkColor = MENU_HIGHLIGHT_HOTKEY_COLOR_KEY;
		}

		Colors::instance.set(*win, nColor);		
		auto hotkeyed = false;
		for (auto c : this->getLabel(length)) {
			if (c == '&') {
				hotkeyed = true;
				continue;
			}
			if (hotkeyed)
				Colors::instance.set(*win, hkColor);
			win->addCh(c);
			if (hotkeyed) {
				Colors::instance.set(*win, nColor);
				hotkeyed = false;
			}
		}
		Colors::instance.unset(*win, nColor);
	}

	void MenuItem::operator()() {
		this->callback();
	}
}
