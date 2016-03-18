#include "textarea.h"

namespace wano {
	TextArea::TextArea(shared_ptr<EventQueue> eq) :
		Window(0, 0, 1, 0),
		doc(eq),
		eq{ eq }
	{
		docCurs.x = 0;
		docCurs.y = 0;
		scrCurs = docCurs;
		offset.x = 0;
		offset.y = 0;
		scrSize.x = this->getMaxX();
		scrSize.y = this->getMaxY();
	}

	void TextArea::handleCh(int ch) {
		switch (ch) {
		case KEY_RIGHT:
			docCurs = doc.cursRight();
			this->moveScreenCursor();
			break;
		case KEY_LEFT:
			docCurs = doc.cursLeft();
			this->moveScreenCursor();
			break;
		case KEY_DOWN:
			docCurs = doc.cursDown();
			this->moveScreenCursor();
			break;
		case KEY_UP:
			docCurs = doc.cursUp();
			this->moveScreenCursor();
			break;
		case KEY_END:
			docCurs = doc.cursEnd();
			this->moveScreenCursor();
			break;
		case KEY_HOME:
			docCurs = doc.cursHome();
			this->moveScreenCursor();
			break;
		case KEY_PPAGE: //PGUP
			docCurs = doc.cursUp(PAGE_SIZE);
			this->moveScreenCursor();
			break;
		case KEY_NPAGE: //PGDN
			docCurs = doc.cursDown(PAGE_SIZE);
			this->moveScreenCursor();
			break;
		case (char)'\n':
		case (char)'\r':
		case KEY_ENTER:
			docCurs = doc.newLine();
			this->moveScreenCursor();
			break;
		case KEY_DC: //DEL
			docCurs = doc.delCh();
			this->moveScreenCursor();
			this->writeCurrentLine();
			break;
		case (char)'\b':
		case KEY_BACKSPACE:
			// TODO: Remove line break if at 0
			if (docCurs.x > 0) {
				docCurs = doc.cursLeft();
				docCurs = doc.delCh();
				this->moveScreenCursor();
				this->writeCurrentLine();
			}
			break;
		default:
			docCurs = doc.insCh(ch);
			this->moveScreenCursor();
			this->writeCurrentLine();
		}
	}

	void TextArea::moveScreenCursor() {
		// Test moving the screen cursor
		bool redraw = false;
		if (docCurs.y - offset.y >= scrSize.y) {
			offset.y++;
			redraw = true;
		}
		else if (docCurs.y - offset.y < 0) {
			offset.y--;
			redraw = true;
		}
		if (redraw) {
			this->redrawDocument();
		}
		// Move the screen cursor relative to the document
		scrCurs.y = docCurs.y - offset.y;
		scrCurs.x = docCurs.x - offset.x;
		this->move(scrCurs.y, scrCurs.x);
	}

	void TextArea::writeCurrentLine() {
		this->move(scrCurs.y, 0);
		this->clrToEOL();
		auto str = doc.readLine(docCurs.y);
		for (auto c : str) {
			this->addCh(c);
		}
		this->move(scrCurs.y, scrCurs.x);
	}

	void TextArea::redrawDocument() {
		// save document and screen cursors
		const auto tdc = docCurs;
		const auto tsc = scrCurs;
		// move document cursor to relative top of screen
		docCurs = doc.cursMove(tdc.x, offset.y);
		// loop and write the document at each line
		for (int i = 0; i < scrSize.y; i++) {
			scrCurs.y = i;
			this->writeCurrentLine();
			docCurs = doc.cursDown();
		}
		// set document and screen cursors back to normal
		docCurs = doc.cursMove(tdc.x, tdc.y);
		scrCurs = tsc;
	}
}