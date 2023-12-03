CODE_DIR = lib/code
INC_DIR = lib
CC=gcc
CFLAGS= 
MAIN = main.c
SRCS = $(CODE_DIR)/controlador_csv.c $(CODE_DIR)/controlador_registro.c $(CODE_DIR)/middleware.c $(CODE_DIR)/funcionalidades.c
INCLUDES= $(INC_DIR)/controlador_csv.h $(INC_DIR)/controlador_registro.h $(INC_DIR)/middleware.h $(INC_DIR)/funcionalidades.h
TARGET= programTrab

all:$(SRCS) $(INCLUDES)
	$(CC) $(CFLAGS) -o $(TARGET) $(MAIN) $(SRCS)


clean:
	rm -f $(TARGET)

run:
	./$(TARGET)