#---------------------------------------------------------------------
# File		: Makefile
# Content	: Program compilation rules
# Author	: Pedro de Oliveira Guedes
#---------------------------------------------------------------------

CC = gcc
LIBS = -lm
SRC = ./src
OBJ = ./obj
INC = ./include
BIN = ./bin
OBJS = $(OBJ)/main.o $(OBJ)/coordinates.o
HDRS = $(INC)/coordinates.h
CFLAGS = -pg -Wall -c -I $(INC)
EXE = $(BIN)/main

$(EXE): $(OBJS)
	$(CC) -pg -o $(EXE) $(OBJS) $(LIBS)

$(OBJ)/main.o: $(SRC)/main.c $(HDRS)
	$(CC) $(CFLAGS) $(SRC)/main.c -o $(OBJ)/main.o

$(OBJ)/coordinates.o: $(SRC)/coordinates.c $(HDRS)
	$(CC) $(CFLAGS) $(SRC)/coordinates.c -o $(OBJ)/coordinates.o

clean:
	rm -f $(OBJ)/*.o $(EXE)