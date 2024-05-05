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
CFLAGS = -pg -Wall -c -I $(INC)
CLIENT_OBJS = $(OBJ)/coordinates.o $(OBJ)/client.o $(OBJ)/network_config.o
CLIENT_HDRS = $(INC)/coordinates.h $(INC)/client.h $(INC)/network_config.h
CLIENT_EXE = $(BIN)/client
SERVER_OBJS = $(OBJ)/coordinates.o $(OBJ)/server.o $(OBJ)/network_config.o
SERVER_HDRS = $(INC)/coordinates.h $(INC)/server.h $(INC)/network_config.h
SERVER_EXE = $(BIN)/server

all: $(CLIENT_EXE) $(SERVER_EXE)

$(CLIENT_EXE): $(CLIENT_OBJS)
	$(CC) -pg -o $(CLIENT_EXE) $(CLIENT_OBJS) $(LIBS)

$(SERVER_EXE): $(SERVER_OBJS)
	$(CC) -pg -o $(SERVER_EXE) $(SERVER_OBJS) $(LIBS)

$(OBJ)/coordinates.o: $(SRC)/coordinates.c $(CLIENT_HDRS) $(SERVER_HDRS)
	$(CC) $(CFLAGS) $(SRC)/coordinates.c -o $(OBJ)/coordinates.o

$(OBJ)/client.o: $(SRC)/client.c $(CLIENT_HDRS)
	$(CC) $(CFLAGS) $(SRC)/client.c -o $(OBJ)/client.o

$(OBJ)/server.o: $(SRC)/server.c $(SERVER_HDRS)
	$(CC) $(CFLAGS) $(SRC)/server.c -o $(OBJ)/server.o

$(OBJ)/network_config.o: $(SRC)/network_config.c $(CLIENT_HDRS) $(SERVER_HDRS)
	$(CC) $(CFLAGS) $(SRC)/network_config.c -o $(OBJ)/network_config.o

clean:
	rm -f $(OBJ)/*.o $(BIN)/*