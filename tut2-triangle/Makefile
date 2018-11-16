#simple Makefile

tut01: main.o
	g++ `pkg-config --libs glfw3` -o $@ -lGL -lGLEW -Wall $^

main.o: main.cpp
	g++ -c main.cpp

clean: 
	rm tut01 main.o
