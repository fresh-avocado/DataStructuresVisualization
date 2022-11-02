CPP = g++
CPPFLAGS = -std=c++20 -Wall -Wpedantic -Wextra -Wshadow -framework OpenGL -lglfw -DDEBUG -I /opt/X11/include -L /opt/X11/lib -lX11 -ljpeg -lpng -lz -lassimp -lfreetype -pthread -I /usr/local/Cellar/freetype/2.12.1/include/freetype2
VPATH = ./include:./include/glad:./include/stbi:./include/shaders:./include/model:./include/mesh:./include/pyramid:./include/helpers:./include/object:./include/window:./include/bst:./include/line:./include/textRenderer

all: main.o glad.o stbi.o shaders.o model.o mesh.o helpers.o pyramid.o window.o bst.o line.o textRenderer.o
	$(CPP) $(CPPFLAGS) ./o/main.o ./o/glad.o ./o/shaders.o ./o/model.o ./o/mesh.o ./o/stbi.o ./o/helpers.o ./o/pyramid.o ./o/window.o ./o/bst.o ./o/line.o ./o/textRenderer.o -o sout.out

main.o: main.cpp
	$(CPP) $(CPPFLAGS) -c main.cpp -o ./o/main.o

glad.o: glad.h glad.c
	$(CPP) $(CPPFLAGS) -c ./include/glad/glad.c -o ./o/glad.o

stbi.o: stbi.h
	$(CPP) $(CPPFLAGS) -c ./include/stbi/stbi.h -o ./o/stbi.o

shaders.o: shaders.hpp shaders.cpp
	$(CPP) $(CPPFLAGS) -c ./include/shaders/shaders.cpp -o ./o/shaders.o

model.o: model.hpp model.cpp
	$(CPP) $(CPPFLAGS) -c ./include/model/model.cpp -o ./o/model.o

mesh.o: object.hpp mesh.hpp mesh.cpp
	$(CPP) $(CPPFLAGS) -c ./include/mesh/mesh.cpp -o ./o/mesh.o

helpers.o: helpers.hpp helpers.cpp
	$(CPP) $(CPPFLAGS) -c ./include/helpers/helpers.cpp -o ./o/helpers.o

pyramid.o: object.hpp pyramid.hpp pyramid.cpp
	$(CPP) $(CPPFLAGS) -c ./include/pyramid/pyramid.cpp -o ./o/pyramid.o

window.o: window.hpp window.cpp
	$(CPP) $(CPPFLAGS) -c ./include/window/window.cpp -o ./o/window.o

bst.o: BST.hpp BST.cpp
	$(CPP) $(CPPFLAGS) -c ./include/bst/BST.cpp -o ./o/bst.o

line.o: line.hpp line.cpp
	$(CPP) $(CPPFLAGS) -c ./include/line/line.cpp -o ./o/line.o

textRenderer.o: textRenderer.hpp textRenderer.cpp
	$(CPP) $(CPPFLAGS) -c ./include/textRenderer/textRenderer.cpp -o ./o/textRenderer.o

clean:
	rm ./o/*.o a.out