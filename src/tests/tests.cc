#include <SDL2/SDL.h>
#include <sdl2pp/sdl2pp.h>
#include "testing.h"

void test_window(test::Test* test) {
    sdl2::SdlContext sdlContext;
    sdl2::Window window("Test Window", 800, 600);
    SDL_Delay(1000);
}

void test_color(test::Test* test) {

}

int main(int argc, char* argv[]) {
    test::Harness h;

    h += { "Window", test_window };
    h += { "Color", test_color };

    h();

    return 0;
}