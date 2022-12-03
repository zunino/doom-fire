# DOOM Fire

This is an implementation of a fire animation effect that should resemble that
used by the
[1995 Playstation port of the original DOOM game](https://youtu.be/YJB0gfP-GRY?t=12).
A basic outline of how it works:

- A color palette is generated via linear interpolation based on an initial set
  of basic colors.
- The fire is represented by a 2D-array of indices that reference values from
  the palette.
- Initially, the bottom row of cells is filled with the most intense color in
  the palette (the source of the fire).
- Upon each animation update, the fire cells are traversed and if they refer to
  any color other than black, a cell above it is modified to refer to the next
  (less intense) color in the palette.
- The actual cell that is updated is chosen randomly and takes "wind" into
  consideration.

## Dependencies

- [SDL2](https://www.libsdl.org/)
    - [SDL2-TTF](https://github.com/libsdl-org/SDL_ttf)
    - [SDL2-Image](https://github.com/libsdl-org/SDL_image)
- [Seidel](https://github.com/zunino/seidel) (included in this repository)

For Debian-based distros:

```sh
sudo apt install -y libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev
```

## Building and executing

```sh
make run
```

Note: The included _Makefile_ uses g++, but you should be able to build with any
compiler supporting C++17.

## Controls

The &larr; and &rarr; keys can be used to change the direction and intensity of
the wind while the simulation is running.

Press `ESC` to exit.
