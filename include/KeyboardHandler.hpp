#include "SDL.h"

#ifndef DOUBLE_TROUBLE_KEYBOARDHANDLER_H
#define DOUBLE_TROUBLE_KEYBOARDHANDLER_H

class KeyboardHandler {
public:
    void static handleKeyboardEvent(SDL_Event event) { keyState[event.key.keysym.sym] = event.key.state; };

    bool static isPressed(int keyCode) { return (keyState[keyCode] == SDL_PRESSED); };

    bool static isReleased(int keyCode) { return (keyState[keyCode] == SDL_RELEASED); };

private:
    // im using 1024 statically here, because I didnt find a way to obtain the number of elements in the enum and I think 1024 is enough (I know i waste space here ;))
    bool inline static keyState[1024];
};

#endif //DOUBLE_TROUBLE_KEYBOARDHANDLER_H
