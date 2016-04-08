#pragma once

#include <memory>
#include "curses_obj.h"
#include "document.h"

// TODO: Normally the size of the textarea
const auto PAGE_SIZE = 10;

namespace wano {
	class TextArea : public curses::Window {
	public:
		TextArea(EventQueue* eq);
		void handleCh(const int ch);
		Document doc;

	private:
		coord docCurs;
		coord offset;
		coord scrCurs;
		coord scrSize;
		void writeCurrentLine();
		void moveScreenCursor();
		void redrawDocument();

		EventQueue* eq;
	};
}
