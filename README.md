# Conway's Game of Life
> Conway's Game of Life is a cellular automaton that is played on a 2D square grid. Each square (or "cell") on the grid can be either alive or dead, and they evolve according to the following rules:
>- Any live cell with fewer than two live neighbours dies (referred to as underpopulation).
>- Any live cell with more than three live neighbours dies (referred to as overpopulation).
>- Any live cell with two or three live neighbours lives, unchanged, to the next generation.
>- Any dead cell with exactly three live neighbours comes to life.
#### - [Community website](https://conwaylife.com/)
## Install for Ubuntu 22.04
```
git clone https://github.com/mikkokiviniemi/game_of_life.git
sudo apt-get install libsdl2-dev
sudo apt-get install libsdl2-image-dev
cd game_of_life
cmake -S . -B build
make -C build
```
## Install for openSUSE Leap 15.5
```
git clone https://github.com/mikkokiviniemi/game_of_life.git
sudo zypper install libSDL2-devel
sudo zypper install libSDL2_image-devel
cd game_of_life
cmake -S . -B build
make -C build
```
## Running
### Basic
```
build/conway
```
### Different size (100x100)
```
build/conway -s 100 100
```
### Different pattern
```
build/conway -p "data/glider.txt
```
## Examples
### Info
<img src="https://github.com/mikkokiviniemi/game_of_life/blob/3a021a3adf90eed96d6fa10294df80dbc3072659/resources/conway_info.bmp" width="200">

### Running
<img src="https://github.com/mikkokiviniemi/game_of_life/blob/552d14a20ae00a1d07a52209a19689f8e75d92eb/examples/example.gif" width="200">

## Team
- [ElisaHoo](https://github.com/ElisaHoo)
- [holle1234](https://github.com/holle1234)
- [mikkokiviniemi](https://github.com/mikkokiviniemi)
