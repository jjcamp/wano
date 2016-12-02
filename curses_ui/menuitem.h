#pragma once

#include <functional>
#include <iostream>
#include "panel_obj.h"

namespace curses_ui {
	class MenuItem {
	public:
		MenuItem(std::string&& label, std::string hotkey, std::function<void(void)> callback);
		bool selected = false;
		const size_t length() const;
		static const size_t lengthOfLabel(const std::string& label);
		std::string getLabel(int length) const;
		void draw(curses::Window* win, int length);
		void operator()();

	private:
		std::string label;
		std::string hotkey;
		std::function<void(void)> callback;

		const std::string MENU_COLOR_KEY = "menu";
		const std::string MENU_HOTKEY_COLOR_KEY = "menu_hotkey";
		const std::string MENU_HIGHLIGHT_COLOR_KEY = "menu_highlight";
		const std::string MENU_HIGHLIGHT_HOTKEY_COLOR_KEY = "menu_highlight_hotkey";
	};
}