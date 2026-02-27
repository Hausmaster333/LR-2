# mingw32-make для сборки на Windows
# make для сборки на Linux
program: main.cpp
	g++ main.cpp -o program

clean:
	rm *.o program