Wano
====
Wano aims to be a portable nano clone that uses the familiar windows-like shortcuts.

Building
----
Wano has been built with VS2015 and Clang 3.4, but should be able to be built with any compiler that supports C++14. On Windows, Wano also requires a pre-compiled PDCurses .lib file in the `lib/` directory along with its headers.

Major TODOs
----
* ~~Create an event system~~ *DONE*
* ~~Get alt-key working on linux~~
* Decouple textarea from document with event system
* Implement menus
* ~~Convert project to CMAKE or GN or GYP.~~ *Mostly done*
