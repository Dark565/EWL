# EverWord Library

## EWL is an another answer to SDL or SFML for a fast and easy multimedia library.
#### The library has four different submodules compilled to another shared objects:


- **System**

> Offers basic core functions like managing with threads, playing with the time or getting CPU informations;


- **Graphics**

> Visual fragments. Creating windows, manipulating with pixmaps and image rendering;


- **Audio**

> Part for audio guys who wanna drown out the silence. Gives audio buffers, abbility of playing and registering sounds and simple audio effects;


- **Formats**

> Library's IO manager and native converter. It takes the seal for importing/exporting media. Required by Graphics and Audio.

## How to play with it

#### To compile the library you have to make a few steps

- Prepare the build configuration. Give the execute permissions for `autogen.sh` and run it. This will create a `.config` file for you, when you can choose some config sets in.

- Generate `Makefile`. Write `./autogen.sh` the second time.

- Build the library. Type `make -j <threads count>`

- And finally install it via `sudo make install`

- Done. Be enjoy with the word, which hasn't got a beginning :)
