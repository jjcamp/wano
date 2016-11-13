#include "menuitem.h"

using namespace std;
using namespace curses;

namespace curses_ui {
	MenuItem::MenuItem(std::string&& label, std::string hotkey, std::function<void(void)> callback) :
		label(move(label)),
		hotkey{ hotkey },
		callback{ callback }
	{}

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
		int color_offset = 0;
		if (this->selected)
			color_offset = 2;

		win->attrOn(curses::Color::Pair(1 + color_offset));
		auto highlight = false;
		for (auto c : this->getLabel(length)) {
			if (c == '&') {
				highlight = true;
				continue;
			}
			if (highlight)
				win->attrOn(curses::Color::Pair(2 + color_offset));
			win->addCh(c);
			if (highlight) {
				win->attrOn(curses::Color::Pair(1 + color_offset));
				highlight = false;
			}
		}
		win->attrOff(curses::Color::Pair(1 + color_offset));
	}

	void MenuItem::operator()() {
		this->callback();
	}
}
