CC = clang
CFLAGS = -std=c17 -g -Wall

TARGET = mnml-as
TST_TARGET = test.test

SRC_DIR = ./src
OUT_DIR = ./build
OBJ_DIR = $(OUT_DIR)/obj

TST_SRC_DIR = ./test
TST_OUT_DIR = ./build/tests
TST_OBJ_DIR = $(TST_OUT_DIR)/obj

LIBS += 
DEPS += -I$(SRC_DIR)

TST_LIBS += 
TST_DEPS += -I$(TST_SRC_DIR)

#------------------------------------------------------------------------------
# DO NOT EDIT BELOW THIS LINE
#------------------------------------------------------------------------------
INC = $(shell find $(SRC_DIR) -name '*.h')
SRC = $(shell find $(SRC_DIR) -name '*.c')
OBJ = $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(SRC:.c=.o))

TST_INC = $(shell find $(TST_SRC_DIR) -name '*.h')
TST_SRC = $(shell find $(TST_SRC_DIR) -name '*.c')
NMM_OBJ = $(filter-out %main.o, $(OBJ)) 
TST_OBJ = $(patsubst $(TST_SRC_DIR)/%, $(TST_OBJ_DIR)/%, $(TST_SRC:.c=.o))
NMM_TST_OBJ = $(filter-out %.test.o, $(TST_OBJ)) 
TST_TARGETS = $(patsubst $(TST_SRC_DIR)/%.test.c, $(TST_OUT_DIR)/%.test, $(TST_SRC)) # $(shell find $(TST_SRC_DIR) -name '*.test.c')

all: $(TARGET)

remake: clean all

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(LIBS) $^ -o $(OUT_DIR)/$@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC)
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $(LIBS) $(DEPS) $< -o $@

test: clean $(TST_TARGETS)

$(TST_OUT_DIR)/%.test: $(NMM_OBJ) $(NMM_TST_OBJ) $(TST_OBJ_DIR)/%.test.o
	$(CC) $(CFLAGS) $(LIBS) $(TST_LIBS) $^ -o $@
	$@

$(TST_OBJ_DIR)/%.o: $(TST_SRC_DIR)/%.c $(INC) $(TST_INC)
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $(LIBS) $(TST_LIBS) $(DEPS) $(TST_DEPS) $< -o $@

clean:
	@rm -rf $(OUT_DIR)

.PHONY: clean
