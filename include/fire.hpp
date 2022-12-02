#ifndef AZ_FIRE_HPP
#define AZ_FIRE_HPP

#include <cstddef>

#include <seidel/Seidel.hpp>

inline constexpr std::size_t WINDOW_WIDTH = 800;
inline constexpr std::size_t WINDOW_HEIGHT = 600;

inline constexpr std::size_t CELL_WIDTH = 2;
inline constexpr std::size_t CELL_HEIGHT = 4;

inline constexpr std::size_t FIRE_ROWS = WINDOW_HEIGHT / CELL_HEIGHT;
inline constexpr std::size_t FIRE_COLS = WINDOW_WIDTH / CELL_WIDTH;

inline constexpr std::size_t COLOR_INTERPOLATION_STEPS = 8;

struct DoomFire {
    DoomFire();
    DoomFire(const std::vector<SDL_Color>& basic_colors);
    void update();
    void draw(sdl::Window& window);
private:
    std::vector<SDL_Color> fire_palette;
    std::size_t fire[FIRE_ROWS][FIRE_COLS];
};

#endif
