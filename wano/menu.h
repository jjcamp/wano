#pragma once

#include <vector>
#include <string>
#include "../curses_ui/curses_ui.h"

namespace wano {
	class Menu {
	public:
		Menu();
		const curses::Window& getWindow();
		void draw();
		void updatePos(const int ln, const int col);
		void focus(int ch);
	private:
		typedef struct { std::string label; char hotkey; curses_ui::Submenu submenu; } sub;

		std::vector<sub> items;
		int docx, docy;
		curses::Panel win;

		const std::string MENU_COLOR_KEY = "menu";
		const std::string MENU_HOTKEY_COLOR_KEY = "menu_hotkey";
	};
}