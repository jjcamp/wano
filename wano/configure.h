#pragma once

#include "../curses_ui/curses_ui.h"

namespace wano {
	void configureColors() {
		curses_ui::Colors::instance.add("menu", curses::Color::BLACK, curses::Color::CYAN);
		curses_ui::Colors::instance.add("menu_hotkey", curses::Color::RED, curses::Color::CYAN);
		curses_ui::Colors::instance.add("menu_highlight", curses::Color::WHITE, curses::Color::BLACK);
		curses_ui::Colors::instance.add("menu_highlight_hotkey", curses::Color::CYAN, curses::Color::BLACK);
	}
}