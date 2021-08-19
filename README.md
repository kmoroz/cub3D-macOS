![codam logo](https://www.datocms-assets.com/4526/1560770259-logocodamblack-copy.svg)

## ❔ Basic Overview

`cub3D` is inspired by Wolfenstein 3D, the first ever first-person shooter. The goal of this project is to implement a dynamic view inside a maze from a first person perspective by utilizing ray-casting. It is obligatory to use `miniLibX`, a graphics library developed by 42Network.

## 📜 Game Configuration

It is necessary to provide a `.cub` file to compile the game. The program takes it as a first argument. The file contains the following information:

### ❕ Mandatory Part

| Identifier | Description | Example |
| --- | --- | --- |
| NO | North-facing wall texture path | `NO ./path_to_the_north_texture` |
| SO | South-facing wall texture path | `SO ./path_to_the_south_texture` |
| WE | West-facing wall texture path | `WE ./path_to_the_west_texture` |
| EA | East-facing wall texture path | `EA ./path_to_the_east_texture` |
| F | Floor colour in RGB format | `F 220,100,0` |
| C | Ceiling colour in RGB format | `C 225,30,0` |
| 1111 <br />1001 <br />1N01 <br />1111 | A closed map (surronded by walls). It must be composed of only 4 possible characters: `0` for an empty space, `1` for a wall, `2` for a sprite (bonus) and `N`, `S`, `E` or `W` for the player’s start position and spawning orientation. |      ``1111111111111111111111111`` <br />``1000000000110000000000001`` <br />``1011000001110000000000001`` <br />``1001000000000000000000001`` <br />``11111111101100000111111111111`` <br />``100000000011000001110111111111111`` <br />``11110111111111011100000012001`` <br />``11110111111111011101010010201`` <br />``11000000110101011100000010001 ``<br />``10000000000000001100000000001`` <br />``10000000000000001101010010001`` <br />``11000001110101011111011110N0111`` <br />``11110111 1110101 101111010001`` <br />``11111111 1111111 111111111111`` <br />

### 🎰 Bonus / Optional

| Identifier | Description | Example |
| --- | --- | --- |
| S | Sprite texture path (bonus) | `S ./path_to_the_sprite_texture` |
| R | Game window resolution (optional) | `R 1920 1080` |

## 🔲 Game Compilation

Run the following in the root directory:
1. `make`
2. ``./cub3D map.cub``
3. ????
4. PROFIT!!!

## 🍄 Game Demo
![cub3D](readme.gif)