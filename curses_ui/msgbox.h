#pragma once

#include <string>
#include <vector>
#include "panel_obj.h"
#include "popup.h"

namespace curses_ui {
	class MsgBox : public Popup {
	public:
		static const unsigned char B_OK = 1;
		static const unsigned char B_CANCEL = 2;
		static const unsigned char B_YES = 4;
		static const unsigned char B_NO = 8;

		MsgBox(std::string&& text, unsigned char buttons);
		int show();

		static int show(std::string&& text, unsigned char buttons);

	private:
		typedef struct { int nlines; int ncols; int begin_y; int begin_x; } coord_info;
		MsgBox(std::string&& text, unsigned char buttons, coord_info info);
		inline coord_info calcSize(const std::string& text, unsigned char buttons) const;
		inline int calcButtonsWidth(unsigned char buttons) const;
		void drawButtons();

		std::string message;
		typedef struct { int value; std::string label; bool selected; } button_info;
		std::vector<button_info> button_infos;
		int buttons_width;
		int button_selected;
	};
}