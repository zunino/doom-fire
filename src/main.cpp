#include <cmath>
#include <memory>
#include <sstream>
#include <iomanip>

#include <SDL2/SDL_render.h>
#include <seidel/SDL.hpp>
#include <seidel/Window.hpp>
#include <seidel/Clock.hpp>
#include <seidel/Text.hpp>
#include <seidel/Texture.hpp>

#include <fire.hpp>

namespace {
    const SDL_Color FONT_COLOR{255, 255, 255, 255};
}

struct WindControl {
    static const std::size_t WINDOMETER_WIDTH = 201;
    static const std::size_t MARKER_WIDTH = 9;
    static const std::size_t MARKER_INCREMENT_WIDTH = 20;
    static constexpr std::size_t MARKER_ZERO_POS = (WINDOW_WIDTH - MARKER_WIDTH) / 2;
    WindControl(const DoomFire& doom_fire, sdl::Window& sdl_window, const sdl::Writer& sdl_writer)
    : doom_fire{doom_fire},
      sdl_window{sdl_window},
      sdl_writer{sdl_writer},
      windometer{sdl_window.renderer(), "res/windometer.png"},
      marker{sdl_window.renderer(), "res/windometer-marker.png"},
      windometer_src_rect{0, 0, 201, 6},
      windometer_dst_rect{(WINDOW_WIDTH - WINDOMETER_WIDTH) / 2, 38, 201, 6},
      marker_src_rect{0, 0, 9, 9},
      marker_dst_rect{MARKER_ZERO_POS, 36, 9, 9} {
    }
    void draw() {
        int wind_strength = this->doom_fire.wind_strength();
        this->marker_dst_rect.x = MARKER_ZERO_POS + wind_strength * MARKER_INCREMENT_WIDTH;
        sdl_writer.writeBlended("WIND", 380, 4);
        SDL_RenderCopy(this->sdl_window.renderer(), this->windometer, &this->windometer_src_rect, &this->windometer_dst_rect);
        SDL_RenderCopy(this->sdl_window.renderer(), this->marker, &this->marker_src_rect, &this->marker_dst_rect);
    }
private:
    const DoomFire& doom_fire;
    sdl::Window& sdl_window;
    const sdl::Writer& sdl_writer;
    sdl::Texture windometer;
    sdl::Texture marker;
    const SDL_Rect windometer_src_rect;
    const SDL_Rect windometer_dst_rect;
    const SDL_Rect marker_src_rect;
    SDL_Rect marker_dst_rect;
};

int main() {
    sdl::SDL sdl(SDL_INIT_VIDEO);
    sdl::Window sdl_window{"DOOM Fire", WINDOW_WIDTH, WINDOW_HEIGHT};
    sdl::Clock sdl_clock{60};

    sdl::Text sdl_text{sdl_window.renderer()};
    sdl::Font sdl_font{"res/doom.ttf", 30};
    sdl::Writer sdl_writer = sdl_text.writer(sdl_font, FONT_COLOR);

    DoomFire doom_fire;
    WindControl wind_control{doom_fire, sdl_window, sdl_writer};

    bool running = true;
    SDL_Event event;
    while (running) {
        sdl_clock.startFrame();
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        running = false;
                        break;
                    case SDLK_LEFT:
                        doom_fire.increase_wind_left();
                        break;
                    case SDLK_RIGHT:
                        doom_fire.increase_wind_right();
                        break;
                }
            }
        }

        sdl_window.clear();

        doom_fire.update();
        doom_fire.draw(sdl_window);
        wind_control.draw();

        SDL_RenderPresent(sdl_window.renderer());
        SDL_Delay(sdl_clock.remainingFrameTime());
        sdl_clock.endFrame();
    }
}
