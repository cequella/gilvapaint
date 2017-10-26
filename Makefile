
CC= g++
CPPFLAGS:= -std=c++11 -Wall -Wextra -pedantic -Iinclude/

OBJ= obj/
SRC= src/
BIN= bin/
INC= include/

all:
	${CC} ${CPPFLAGS} ${SRC}main.cpp -o ${BIN}gilvapaint

# ===================== Image.o ========================
Canvas.o:
	${CC} ${CPPFLAGS} -c ${SRC}Canvas.cpp -o ${OBJ}Canvas.o
