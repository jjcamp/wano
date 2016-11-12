#pragma once

#include <vector>
#include "popup.h"
#include "menuitem.h"

namespace curses_ui {
	class Submenu : public Popup {
	public:
		struct SubmenuResult : Result {
			static constexpr int LEFT = 2;
			static constexpr int RIGHT = 3;
		};

		Submenu(std::vector<MenuItem>&& items, int start_y, int start_x);
		int show();

	private:
		typedef struct { const int y; const int x; } v2;

		Submenu(std::vector<MenuItem>&& items, v2 dimensions, int start_y, int start_x);
		inline v2 getDimensions(std::vector<MenuItem>& items);
		std::vector<MenuItem> items;
	};
}