
CC= g++
CPPFLAGS:= -g -std=c++11 -Wall -Wextra -pedantic -Iinclude/
LINKER_FLAGS= -lSDL2

OBJ= obj/
SRC= src/
BIN= bin/
INC= include/

all: 
	${CC} ${SRC}main.cpp ${CPPFLAGS} ${LINKER_FLAGS} -o ${BIN}gilvapaint ${OBJ}* `sdl2-config --cflags --libs`

run:
	@./bin/gilvapaint

# ===================== Image.o ========================
Canvas.o:
	${CC} ${SRC}Canvas.cpp ${CPPFLAGS} -c -o ${OBJ}Canvas.o

Window.o:
	${CC} ${SRC}Window.cpp ${CPPFLAGS} -c -o ${OBJ}Window.o

MouseListener.o:
	${CC} ${SRC}MouseListener.cpp ${CPPFLAGS} -c -o ${OBJ}MouseListener.o

MouseEvent.o:
	${CC} ${SRC}MouseEvent.cpp ${CPPFLAGS} -c -o ${OBJ}MouseEvent.o
