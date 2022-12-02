#include <vector>
#include <cmath>

#include <fire.hpp>

namespace {
    std::vector<SDL_Color> default_colors{
        {0, 0, 0},      // black
        {255, 0, 0},    // red
        {255, 165, 0},  // orange
        {255, 255, 0},  // yellow
        {255, 255, 255} // white
    };
}
    
std::vector<SDL_Color> make_palette(const std::vector<SDL_Color>& basic_colors) {
    std::vector<SDL_Color> palette;
    for (std::size_t i = 0; i < basic_colors.size() - 1; ++i) {
        const SDL_Color& c1 = basic_colors[i];
        const SDL_Color& c2 = basic_colors[i + 1];
        for (std::size_t s = 0; s < COLOR_INTERPOLATION_STEPS + 1; ++s) {
            float fraction = s / float(COLOR_INTERPOLATION_STEPS + 1);
            unsigned char r = std::lerp(c1.r, c2.r, fraction);
            unsigned char g = std::lerp(c1.g, c2.g, fraction);
            unsigned char b = std::lerp(c1.b, c2.b, fraction);
            palette.push_back(SDL_Color{r, g, b, 255});
        }
    }
    palette.push_back(basic_colors.back());
    return palette;
}

DoomFire::DoomFire()
: DoomFire(default_colors) {
}

DoomFire::DoomFire(const std::vector<SDL_Color>& basic_colors)
: fire{} {
    this->fire_palette = make_palette(basic_colors);
    for (std::size_t col = 0; col < FIRE_COLS; ++col) {
        this->fire[FIRE_ROWS - 1][col] = this->fire_palette.size() - 1;
    }
}

void DoomFire::update() {
    for (std::size_t row = 1; row < FIRE_ROWS; ++row) {
        for (std::size_t col = 0; col < FIRE_COLS; ++col) {
            std::size_t curr_color_idx = this->fire[row][col];
            if (curr_color_idx != 0) {
                std::size_t col_idx = col - sdl::random(0, 1) % FIRE_COLS;
                this->fire[row - 1][col_idx] = curr_color_idx - sdl::random(0, 1);
            }
        }
    }
}

void DoomFire::draw(sdl::Window &window) {
    for (std::size_t row = 0; row < FIRE_ROWS; ++row) {
        int y = row * CELL_HEIGHT;
        for (std::size_t col = 0; col < FIRE_COLS; ++col) {
            const SDL_Color& c = this->fire_palette[this->fire[row][col]];
            int x = col * CELL_WIDTH;
            SDL_Rect cell_rect{x, y, CELL_WIDTH, CELL_HEIGHT};
            SDL_SetRenderDrawColor(window.renderer(), c.r, c.g, c.b, 255);
            SDL_RenderFillRect(window.renderer(), &cell_rect);
        }
    }
}
