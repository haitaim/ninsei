# Ninsei
Ninsei is a library for developing on the Game Boy Advance with C++.
## Preface
Fundamentally, this is more of a personal project by an amateur to get a little acquainted with embedded programming in C++.
As such, the quality of the code will probably be below par, and their may be flaws in the architecture of the libarary.
Suggestions from anyone who comes across this are greatly appreciated.
## Design
Compatibility with older versions of C++ will not be a concern, so C++20 features such as concepts are free to use.
However, given that modules are currently not supported by GCC or clang, the library will be written with header files.
This will probably be the case until the release of GCC 11 and a devkitARM update.
## Future
I'm unlikely to update this.
I guess I underestimated the scope of what was required and, more importantly, how to design it well.
If I do change this, here's what I'd do:
* Redesign the MMIO again
  * While the ability to chain functions is neat, remembering to end the chain with write_buffer() is not great
  * Instead, I'd probably just use scoped enums with overloaded bit functions.
It's familiar and, with consteval, compile time friendly.
The base class can stay though
* Rename it
  * Ninsei was something I came up with on a whim.
There's reasons why I don't like it anymore, but I'll just leave it at that

There isn't much to change, but I'd rather fool around with Tonclib first then continue work.
Speaking of which...
## Acknowlegements
* [Tonc](http://coranac.com/tonc/text/) is an excellent resource for learning about the GBA
* [GBATEK](http://problemkaputt.de/gbatek.htm) is something I didn't go too in depth with,
but the research gone into it is invaluable
