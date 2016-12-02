#include "submenu.h"

using namespace std;

namespace curses_ui {
	Submenu::Submenu(vector<MenuItem>&& items, int start_y, int start_x) :
		Submenu(forward<vector<MenuItem>>(items), getDimensions(items), start_y, start_x)
	{}

	Submenu::Submenu(vector<MenuItem>&& items, v2 dimensions, int start_y, int start_x) :
		Popup(dimensions.y, dimensions.x, start_y, start_x),
		items(forward<vector<MenuItem>>(items))	{
	}
	
	int Submenu::show() {
		auto result = SubmenuResult::EXIT;
		auto selectedItem = 0;
		items[selectedItem].selected = true;
		auto labelWidth = this->panel.getMaxX() - 2;
		auto prevCursor = this->beforeShow();
		for (auto i = 0; i < items.size(); i++) {
			this->panel.move(i + 1, 1);
			items[i].draw(&this->panel, labelWidth);
		}
		this->panel.update();
		int ch;
		while ((ch = this->panel.getCh()) != 27) {
			switch (ch) {
			case KEY_DOWN:
				if (selectedItem + 1 == items.size())
					continue;
				this->panel.move(selectedItem + 1, 1);
				items[selectedItem].selected = false;
				items[selectedItem].draw(&this->panel, labelWidth);
				panel.move(++selectedItem + 1, 1);
				items[selectedItem].selected = true;
				items[selectedItem].draw(&this->panel, labelWidth);
				this->panel.update();
				continue;
			case KEY_UP:
				if (selectedItem == 0)
					continue;
				this->panel.move(selectedItem + 1, 1);
				items[selectedItem].selected = false;
				items[selectedItem].draw(&this->panel, labelWidth);
				panel.move(--selectedItem + 1, 1);
				items[selectedItem].selected = true;
				items[selectedItem].draw(&this->panel, labelWidth);
				this->panel.update();
				continue;
			case KEY_LEFT:
				result = SubmenuResult::LEFT;
				break;
			case KEY_RIGHT:
				result = SubmenuResult::RIGHT;
				break;
			case (char)'\n':
			case (char)'\r':
			case KEY_ENTER:
				this->afterShow(prevCursor);
				items[selectedItem]();
				return SubmenuResult::EXIT;
			default:
				continue;
			}
			break;
		}
		this->afterShow(prevCursor);
		return result;
	}

	inline Submenu::v2 Submenu::getDimensions(vector<MenuItem>& items) {
		int cols = 0, lines = 0;
		for (auto& i : items) {
			lines++;
			if (i.length() > cols)
				cols = static_cast<int>(i.length());
		}
		return v2{ lines, cols };
	}
}