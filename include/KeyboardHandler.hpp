#include "SDL.h"

#ifndef DOUBLE_TROUBLE_KEYBOARDHANDLER_H
#define DOUBLE_TROUBLE_KEYBOARDHANDLER_H

class KeyboardHandler {
public:
    void static handleKeyboardEvent(SDL_Event event) { keyState[event.key.keysym.sym] = event.key.state; };

    bool static isPressed(int keyCode) { return (keyState[keyCode] == SDL_PRESSED); };

    bool static isReleased(int keyCode) { return (keyState[keyCode] == SDL_RELEASED); };

private:
    // Unfortunately I need so many entries bc the arrow symbols return this numbers in sdl
    bool inline static keyState[1073742000] = {SDL_RELEASED};
};

#endif //DOUBLE_TROUBLE_KEYBOARDHANDLER_H
