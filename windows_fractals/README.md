# install SDL - for command line
https://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/index.php

# compilation - in every directory
- with SDL
	make SDL=true
-without SDL
	make SDL=false

# running
	target.exe w h maxIter
	ex: mandel.exe 400 300 500

WITHOUT MAKE
- with SDL
g++ *.cpp -IC:/mingw_dev_lib/include/SDL2 -LC:\mingw_dev_lib\lib -g -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -o mandel.exe

-without SDL
g++ mandel.cpp -g -o mandel.exe