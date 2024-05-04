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
OBJS = $(OBJ)/main.o $(OBJ)/coordinates.o $(OBJ)/client.o $(OBJ)/server.o
HDRS = $(INC)/coordinates.h $(INC)/client.h $(INC)/server.h
CFLAGS = -pg -Wall -c -I $(INC)
EXE = $(BIN)/main

$(EXE): $(OBJS)
	$(CC) -pg -o $(EXE) $(OBJS) $(LIBS)

$(OBJ)/main.o: $(SRC)/main.c $(HDRS)
	$(CC) $(CFLAGS) $(SRC)/main.c -o $(OBJ)/main.o

$(OBJ)/coordinates.o: $(SRC)/coordinates.c $(HDRS)
	$(CC) $(CFLAGS) $(SRC)/coordinates.c -o $(OBJ)/coordinates.o

$(OBJ)/client.o: $(SRC)/client.c $(HDRS)
	$(CC) $(CFLAGS) $(SRC)/client.c -o $(OBJ)/client.o

$(OBJ)/server.o: $(SRC)/server.c $(HDRS)
	$(CC) $(CFLAGS) $(SRC)/server.c -o $(OBJ)/server.o

clean:
	rm -f $(OBJ)/*.o $(EXE)