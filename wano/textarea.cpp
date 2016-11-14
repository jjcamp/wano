#include "textarea.h"

using namespace std;

namespace wano {
	TextArea::TextArea(EventQueue* eq, shared_ptr<Document> document) :
		Panel(0, 0, 1, 0),
		doc{ document },
		eq{ eq },
		docCurs{ 0, 0 },
		scrCurs{ 0, 0 },
		offset{ 0, 0 },
		scrSize{ this->getMaxX(), this->getMaxY() } {
		this->redrawDocument();
		this->moveScreenCursor();
	}

	TextArea::TextArea(EventQueue* eq) :
		TextArea(eq, make_shared<Document>(Document()))
	{}

	void TextArea::setDocument(shared_ptr<Document> document) {
		this->doc.reset();
		this->doc = document;
	}

	void TextArea::handleCh(const int ch) {
		switch (ch) {
		case KEY_RIGHT:
			docCurs = doc->cursRight();
			this->moveScreenCursor();
			break;
		case KEY_LEFT:
			docCurs = doc->cursLeft();
			this->moveScreenCursor();
			break;
		case KEY_DOWN:
			docCurs = doc->cursDown();
			this->moveScreenCursor();
			break;
		case KEY_UP:
			docCurs = doc->cursUp();
			this->moveScreenCursor();
			break;
		case KEY_END:
			docCurs = doc->cursEnd();
			this->moveScreenCursor();
			break;
		case KEY_HOME:
			docCurs = doc->cursHome();
			this->moveScreenCursor();
			break;
		case KEY_PPAGE: //PGUP
			docCurs = doc->cursUp(PAGE_SIZE);
			this->moveScreenCursor();
			break;
		case KEY_NPAGE: //PGDN
			docCurs = doc->cursDown(PAGE_SIZE);
			this->moveScreenCursor();
			break;
		case (char)'\n':
		case (char)'\r':
		case KEY_ENTER:
			docCurs = doc->newLine();
			this->redrawDocument(); // TODO: efficiency
			this->moveScreenCursor();
			break;
		case KEY_DC: //DEL
			docCurs = doc->delCh();
			this->moveScreenCursor();
			this->writeCurrentLine();
			break;
		case (char)'\b':
		case KEY_BACKSPACE:
			// TODO: Remove line break if at 0
			if (docCurs.x > 0) {
				docCurs = doc->cursLeft();
				docCurs = doc->delCh();
				this->moveScreenCursor();
				this->writeCurrentLine();
			}
			break;
		default:
			docCurs = doc->insCh(ch);
			this->moveScreenCursor();
			this->writeCurrentLine();
		}
	}

	void TextArea::moveScreenCursor() {
		// Test moving the screen cursor
		bool redraw = false;
		coord delta;
		delta.y = (docCurs.y - offset.y) - scrSize.y;
		if (delta.y >= 0) {
			offset.y += delta.y + 1;
			redraw = true;
		}
		else if (docCurs.y < offset.y) {
			offset.y = docCurs.y;
			redraw = true;
		}
		delta.x = (docCurs.x - offset.x) - scrSize.x;
		if (delta.x >= 0) {
			offset.x += delta.x + 1;
			redraw = true;
		}
		else if (docCurs.x < offset.x) {
			offset.x = docCurs.x;
			redraw = true;
		}
		if (redraw) {
			this->redrawDocument();
		}
		// Move the screen cursor relative to the document
		scrCurs.y = docCurs.y - offset.y;
		scrCurs.x = docCurs.x - offset.x;
		auto curLine = doc->readLine(docCurs.y);
		size_t tloc = 0;
		int expandTab = 0;
		while ((tloc = curLine.find('\t', tloc)) != string::npos) {
			if (scrCurs.x <= tloc)
				break;
			expandTab += TABSIZE - (tloc + expandTab) % TABSIZE - 1;
			tloc++;
		}
		scrCurs.x += expandTab;
		this->move(scrCurs.y, scrCurs.x);
		// Update document position display
		auto fakeCurs = docCurs;
		fakeCurs.x = scrCurs.x + offset.x;
		this->eq->fire<coord>(DOC_MOVE, fakeCurs);
	}

	void TextArea::writeCurrentLine() {
		this->move(scrCurs.y, 0);
		this->clrToEOL();
		auto str = doc->readLine(docCurs.y);
		for (auto i = offset.x; i < str.length(); i++) {
			if (this->getX() == this->getMaxX() - 1) {
				this->insCh(str[i]);
				break;
			}
			this->addCh(str[i]);
		}
		this->move(scrCurs.y, scrCurs.x);
	}

	void TextArea::redrawDocument() {
		// save document and screen cursors
		const auto tdc = docCurs;
		const auto tsc = scrCurs;
		// move document cursor to relative top of screen
		docCurs = doc->cursMove(tdc.x, offset.y);
		// loop and write the document at each line
		for (int i = 0; i < scrSize.y; i++) {
			scrCurs.y = i;
			this->writeCurrentLine();
			// move document cursor down and check for end of document
			auto prev = docCurs.y;
			if (prev == (docCurs = doc->cursDown()).y)
				break;
		}
		// set document and screen cursors back to normal
		docCurs = doc->cursMove(tdc.x, tdc.y);
		scrCurs = tsc;
	}
}