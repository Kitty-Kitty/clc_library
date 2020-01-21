

PRJ_NAME = "novigo css project"
TARGET = vdu_simple_demo

DIR_INC = ./include
DIR_SRC = ./src
DIR_LIB = ./lib
DIR_OBJ = ./obj
DIR_BIN = ./bin

CROSS_COMPILE = arm-hisiv400-linux-
CC = $(CROSS_COMPILE)g++
strip = $(CROSS_COMPILE)strip

ifeq ($(CROSS_COMPILE), arm-hisiv400-linux-)
	DIR_LIB = ./lib/arm-hisiv400
	DIR_BIN = ./bin
else
	DIR_LIB = ./lib
endif

BIN_TARGET = $(DIR_BIN)/$(TARGET)

$(info, "cross compile[$(CC)].library[$(DIR_LIB)].")
CFLAGS=  -g -I$(DIR_INC) -L$(DIR_LIB) -DDAEMON_MODE
LFLAGS=  -lcp_vdu -lQt5Charts -lQt5Svg -lQt5Widgets -lQt5Core -lQt5Gui -lEGL -lGLESv1_CM -lGLESv2 -lmali 

SRC = $(wildcard $(DIR_SRC)/*.c)
OBJ = $(patsubst %.c,$(DIR_OBJ)/%.o,$(notdir $(SRC))) 

all: chdir $(BIN_TARGET)

chdir:
	mkdir -p $(DIR_OBJ) $(DIR_BIN)

$(BIN_TARGET):$(OBJ)
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJ)  -o $@
	
$(DIR_OBJ)/%.o:$(DIR_SRC)/%.c
	$(CC) $(CFLAGS) $(LFLAGS) -c  $< -o $@

.PHONY:clean
clean:
	rm -f $(DIR_BIN)/$(TARGET)*
	rm -f $(DIR_OBJ)/*
	rm -f *.o
