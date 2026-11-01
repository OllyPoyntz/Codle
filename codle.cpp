/* Main entry point for the game.*/

/* System specific features:
Beep() is only available on Windows and Cygwin.
ANSI colour codes for terminals are only available on POSIX systems (Linux, Cygwin, MacOS, etc.).
Macros are used to detect these later in the code.
*/
#ifdef _WIN32
    #include <windows.h>
    #define beep Beep
#else
    #ifdef __CYGWIN__
        #include "windows.h"
        #define beep Beep
        #define __ansi__ 1
    
    #else
        #define __ansi__ 1
    #endif
#endif

// Macro defined as true when testing:
#define DEBUG false                                                                                                                                                                                                                                                                                                                                                                                                                                             


#include "game.hpp"

int main() {
    // Run some quick setup code:
    codle::setup();
    // And run the game loop...
    return codle::gameloop();
}