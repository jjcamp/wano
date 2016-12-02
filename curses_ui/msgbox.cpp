#include "msgbox.h"

using namespace std;
using namespace curses;

namespace curses_ui {
	MsgBox::MsgBox(std::string&& text, unsigned char buttons, coord_info info) :
		Popup(info.nlines, info.ncols, info.begin_y, info.begin_x),
		message(forward<string>(text)),
		button_infos() {
		Colors::instance.addIfMissing(MENU_COLOR_KEY, Color::BLACK, Color::WHITE);
		Colors::instance.addIfMissing(MENU_HIGHLIGHT_COLOR_KEY, Color::WHITE, Color::BLACK);

		Colors::instance.set(this->panel, MENU_COLOR_KEY);
		panel.addStr(message.c_str());
		for (auto i = 0; i < info.ncols - message.length(); ++i)
			panel.addCh(' ');

		if ((buttons & B_OK) == B_OK)
			button_infos.push_back(button_info{ Result::OKAY, "OK", false });
		if ((buttons & B_CANCEL) == B_CANCEL)
			button_infos.emplace_back(button_info{ Result::EXIT, "CANCEL", false });

		if (button_infos.size() == 0)
			button_infos.push_back(button_info{ Result::OKAY, "OK", false });

		button_selected = button_infos.size() - 1;
		button_infos[button_selected].selected = true;

		Colors::instance.unset(this->panel, MENU_COLOR_KEY);

		buttons_width = this->calcButtonsWidth(buttons);
		this->drawButtons();
	}

	MsgBox::MsgBox(std::string&& text, unsigned char buttons) :
		MsgBox(forward<string>(text), buttons, calcSize(text, buttons))
	{}

	int MsgBox::show() {
		return Popup::show([this](auto ch) {
			switch (ch) {
			case 27:
				return Result::EXIT;
			case KEY_LEFT:
				if (button_selected == 0)
					return Result::CONTINUE;
				button_infos[button_selected].selected = false;
				button_infos[--button_selected].selected = true;
				this->drawButtons();
				this->panel.update();
				doupdate();  // thought this was implicit with PDCurses, need to investigate
				return Result::CONTINUE;
			case KEY_RIGHT:
				if (button_selected == button_infos.size() - 1)
					return Result::CONTINUE;
				button_infos[button_selected].selected = false;
				button_infos[++button_selected].selected = true;
				this->drawButtons();
				this->panel.update();
				doupdate();
				return Result::CONTINUE;
			case '\r':
			case '\n':
			case KEY_ENTER:
				return button_infos[button_selected].value;
			default:
				return Result::CONTINUE;
			}
		});
	}

	MsgBox::coord_info MsgBox::calcSize(const string& text, unsigned char buttons) const {
		const int MAX_WIDTH = COLS * 2 / 3;
		int len = text.length();
		int lines = len / MAX_WIDTH;
		if (len % MAX_WIDTH > 0)
			lines++;
		lines++; // buttons
		int blen = MsgBox::calcButtonsWidth(buttons);
		len = len > blen ? len : blen;
		len = len < MAX_WIDTH ? len : MAX_WIDTH;
		int start_y = (LINES - lines) / 2;
		int start_x = (COLS - len) / 2;
		return coord_info{ lines, len, start_y, start_x };
	}

	int MsgBox::calcButtonsWidth(unsigned char buttons) const {
		auto result = 0;
		auto num_buttons = 0;
		if ((buttons & B_OK) == B_OK) {
			result += 4;
			num_buttons++;
		}
		if ((buttons & B_CANCEL) == B_CANCEL) {
			result += 8;
			num_buttons++;
		}
		if (num_buttons == 0) {
			result = 4;
			num_buttons++;
		}
		result += num_buttons - 1;
		return result;
	}

	void MsgBox::drawButtons() {
		panel.move(panel.getMaxY() - 2, 1);
		Colors::instance.set(this->panel, MENU_COLOR_KEY);
		auto padding = panel.getMaxX() - 2 - buttons_width;
		for (auto front = padding / 2; front < padding; --padding)
			panel.addCh(' ');
		for (auto i = 0; i < button_infos.size(); ++i) {
			panel.addCh('[');
			if (button_infos[i].selected)
				Colors::instance.set(this->panel, MENU_HIGHLIGHT_COLOR_KEY);
			panel.addStr(button_infos[i].label.c_str());
			if (button_infos[i].selected)
				Colors::instance.set(this->panel, MENU_COLOR_KEY);
			panel.addCh(']');
			if (i != button_infos.size() - 1)
				panel.addCh(' ');
		}
		for (; padding > 0; --padding)
			panel.addCh(' ');
		Colors::instance.unset(this->panel, MENU_COLOR_KEY);
	}

	int MsgBox::show(std::string&& text, unsigned char buttons) {
		return MsgBox(forward<string>(text), buttons).show();
	}
}