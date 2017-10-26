
CC= g++
CPPFLAGS:= -std=c++11 -Wall -Wextra -pedantic -Iinclude/

OBJ= obj/
SRC= src/
BIN= bin/
INC= include/

all: Canvas.o
	${CC} ${CPPFLAGS} ${SRC}main.cpp -o ${BIN}gilvapaint ${OBJ}*

run:
	@./bin/gilvapaint

# ===================== Image.o ========================
Canvas.o:
	${CC} ${CPPFLAGS} -c ${SRC}Canvas.cpp -o ${OBJ}Canvas.o
