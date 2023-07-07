# Conway's Game of Life
[Community website](https://conwaylife.com/)
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
```
build/conway
```

## Examples
<img src="https://github.com/mikkokiviniemi/game_of_life/blob/3a021a3adf90eed96d6fa10294df80dbc3072659/resources/conway_info.bmp" width="200">
<img src="https://github.com/mikkokiviniemi/game_of_life/blob/771b4747b847a133686a50356a1e675244d7d7c9/examples/example2.png" width="200">
<img src="https://github.com/mikkokiviniemi/game_of_life/blob/771b4747b847a133686a50356a1e675244d7d7c9/examples/example3.png" width="200">


## Team
- [ElisaHoo](https://github.com/ElisaHoo)
- [holle1234](https://github.com/holle1234)
- [mikkokiviniemi](https://github.com/mikkokiviniemi)
