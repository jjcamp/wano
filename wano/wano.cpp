#include "wano.h"

using namespace wano;
using namespace std;
using namespace curses;

int main() {
    auto win = InitScr();
    Raw();
    NoNL();
    win.keyPad(TRUE);
    NoEcho();
    Color::Start();


    auto eq = make_unique<EventQueue>(EventQueue());
    auto menu = Menu(eq.get());
    auto ta = TextArea(eq.get());
    ta.keyPad(TRUE);
    menu.draw();
    while (true) {
        int ch = ta.getCh();

        if (ch == 27) {
            break;
        }
        ta.handleCh(ch);
    }
    EndWin();

    return 0;
}

