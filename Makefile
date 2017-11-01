
CC= g++
CPPFLAGS:= -g -std=c++11 -Wall -Wextra -pedantic -Iinclude/
LINKER_FLAGS= -lSDL2

OBJ= obj/
SRC= src/
BIN= bin/
INC= include/

all: Canvas.o
	${CC} ${SRC}main.cpp ${CPPFLAGS} ${LINKER_FLAGS} -o ${BIN}gilvapaint ${OBJ}*

run:
	@./bin/gilvapaint

# ===================== Image.o ========================
Canvas.o:
	${CC} ${SRC}Canvas.cpp ${CPPFLAGS} -c -o ${OBJ}Canvas.o
