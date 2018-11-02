<h1> <b>Ever-Word Library</b> - In a heavy progress </h1>
<br>
EWL is an another answer to SDL or SFML for a fast and easy multimedia library.
The library has five different submodules compilled to another shared objects:<br>
- <b>System</b>
Offers basic core functions like managing with threads, playing with the time or getting CPU informations;

- <b>Graphics</b>
Visual fragments. Creating windows, manipulating with pixmaps and image rendering;

- <b>Audio</b>
Part for audio guys who wanna drown out the silence. Gives audio buffers, abbility of playing and registering sounds and simple audio effects;

- <b>Formats</b>
Library's IO manager and native converter. It takes the seal for importing/exporting media. Required by Graphics and Audio.

<h1> How to play with it </h1>
<br>
The first you have to do is configure build data.
Run your terminal emulator. Then give the execute permissions for `autogen.sh` and run it.
It should create `.config` file for you. It has some configuration settings you can change.
If you finish this, you can create Makefile. Do to it, run `./configure` or `autogen.sh` second time.
Finally you can compile project by typing `make -j <threads count>` and install it by `sudo make install`.
Done. You compilled the library. Good job :)
