./bin/Linux/main: src/main.cpp src/glad.c src/models/* src/screens/* src/utils/* include/utils/* include/interfaces/* include/screens/* include/models/*
	mkdir -p bin/Linux
	g++ -std=c++14 -Wall -Wno-unused-function -g -I ./include/ -o ./bin/Linux/main src/main.cpp src/glad.c src/models/* src/screens/* src/utils/* ./lib-linux/libglfw3.a -lrt -lm -ldl -lX11 -lpthread -lXrandr -lXinerama -lXxf86vm -lXcursor

.PHONY: clean run
clean:
	rm -f bin/Linux/main

run: ./bin/Linux/main
	cd bin/Linux && ./main
