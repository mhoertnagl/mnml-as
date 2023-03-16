CC = clang
CFLAGS = -std=c17 -g -Wall

TARGET = mnml-as

SRC_DIR = ./src
TST_DIR = ./test
OUT_DIR = ./build

LIBS += 

TST_LIBS += 

DEPS += -I$(SRC_DIR)

TST_DEPS += -I$(TST_DIR)

INC = $(shell find $(SRC_DIR) -name '*.h')
SRC = $(shell find $(SRC_DIR) -name '*.c')
OBJ = $(patsubst %.c, %.o, $(SRC))

TST_INC = $(shell find $(TST_DIR) -name '*.h')
TST_SRC = $(shell find $(TST_DIR) -name '*.c')
TST_OBJ = $(patsubst %.c, %.o, $(TST_SRC))

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(LIBS) $(DEPS) $^ -o $(OUT_DIR)/$@

%.o: %.c $(INC)
	$(CC) -c $(CFLAGS) $(LIBS) $(DEPS) $< -o $@

.PHONY: clean

clean:
	find . -type f -name '*.o' -delete
	rm -f $(OUT_DIR)/$(TARGET)
