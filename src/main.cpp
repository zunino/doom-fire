#include <seidel/Seidel.hpp>
#include <fire.hpp>

int main() {
    sdl::SDL sdl(SDL_INIT_VIDEO);
    sdl::Window sdl_window{"DOOM Fire", WINDOW_WIDTH, WINDOW_HEIGHT};
    sdl::Clock sdl_clock{90};

    DoomFire doom_fire;

    bool running = true;
    SDL_Event event;
    while (running) {
        sdl_clock.startFrame();
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = false;
                }
            }
        }

        sdl_window.clear();

        doom_fire.update();
        doom_fire.draw(sdl_window);

        SDL_RenderPresent(sdl_window.renderer());
        SDL_Delay(sdl_clock.remainingFrameTime());

        sdl_clock.endFrame();
    }
}
