#Optimisations for speed and size, as well as warning about terrible code:
#(Note: -O3 is only necessary in applications where speed is critical, which is not the case here.)
COMPILER_FLAGS=-O2 -Os -s -Wall -Wextra -std=c++11

#Compilers for different platforms:
LINUX_COMPILER=g++
WIN32_COMPILER=x86_64-w64-mingw32-g++

#Windows-exclusive flags to avoid DLL nonsense:
WIN_FLAGS=-static -static-libgcc -static-libstdc++

#Remove compiled binaries:
clean:
	rm -f codle codle.exe

#Compile for Linux:
codle: codle.cpp game.hpp algo.hpp guess.hpp
	$(LINUX_COMPILER) codle.cpp -o codle $(COMPILER_FLAGS)

#Compile for Windows:
codle.exe: codle.cpp game.hpp algo.hpp guess.hpp
	$(WIN32_COMPILER) codle.cpp -o codle.exe $(COMPILER_FLAGS) $(WIN_FLAGS)

#Compile everything:
all: clean codle codle.exe
	echo "Executables successfully built."
