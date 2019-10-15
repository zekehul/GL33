#simple Makefile

tut02: main.o shader.o
	g++ `pkg-config --libs glfw3` -o $@ -lGL -lGLEW -Wall $^

main.o: main.cpp
	g++ -c main.cpp

shader.o: ../common/shader.cpp
	g++ -c ../common/shader.cpp

clean: 
	rm tut01 main.o
