#pragma once

#include <functional>
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

	private:
		std::string label;
		std::string hotkey;
		std::function<void(void)> callback;
	};
}