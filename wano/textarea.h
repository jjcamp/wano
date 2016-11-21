#pragma once

#include <memory>
#include "../curses_ui/curses_ui.h"
#include "document.h"
#include "services.h"

// TODO: Normally the size of the textarea
const auto PAGE_SIZE = 10;

namespace wano {
	class TextArea : public curses::Panel {
	public:
		TextArea(std::shared_ptr<Document> document);
		void setDocument(std::shared_ptr<Document> document);
		void handleCh(const int ch);
		std::shared_ptr<Document> doc;
		void redrawDocument();

	private:
		coord docCurs;
		coord offset;
		coord scrCurs;
		coord scrSize;
		void writeCurrentLine();
		void moveScreenCursor();
	};
}
