![codam logo](https://www.datocms-assets.com/4526/1560770259-logocodamblack-copy.svg)

## ❔ Basic Overview

`cub3D` is inspired by Wolfenstein 3D, the first ever first-person shooter. The goal of this project is to implement a dynamic view inside a maze from a first person perspective by utilizing ray-casting. It is obligatory to use `miniLibX`, a graphics library developed by 42Network.

## 📜 Game Configuration

It is nececcary to provide a `.cub` file to compile the game. It contains the following information:

### ❕ Mandatory Part

| Identifier | Description | Example |
| --- | --- | --- |
| NO | North-facing wall texture path | `NO ./path_to_the_north_texture` |
| SO | South-facing wall texture path | `SO ./path_to_the_south_texture` |
| WE | West-facing wall texture path | `WE ./path_to_the_west_texture` |
| EA | East-facing wall texture path | `EA ./path_to_the_east_texture` |
| F | Floor colour in RGB format | `F 220,100,0` |
| C | Ceiling colour in RGB format | `C 225,30,0` |
