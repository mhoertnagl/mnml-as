# mu.h - Minimalist unit testing framework.
# Copyright (C) 2023  Mathias Hörtnagl <mathias.hoertnagl[ÄT]gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

CC = clang
CFLAGS = -std=c17 -g -Wall

# Binary
#------------------------------------------------------------------------------
TARGET = mnml-as									# Binary target name.

SRC_DIR = ./src										# Binary source root directory.
OUT_DIR = ./build									# Binary build root directory.
OBJ_DIR = $(OUT_DIR)/obj					# Subdirectory for all source object files.

LIBS += 													# Binary source library dependencies.
DEPS += -I$(SRC_DIR)							# Binary source header file dependencies.

# Unit testing
#------------------------------------------------------------------------------
TST_SRC_DIR = ./test							# Unit tests source root directory.
TST_OUT_DIR = ./build/tests				# Unit tests build root directory.
TST_OBJ_DIR = $(TST_OUT_DIR)/obj	# Subdirectory for all unit test object files.

TST_LIBS += 											# Unit tests library dependencies.
TST_DEPS += -I$(TST_SRC_DIR)			# Unit tests header file dependencies.

#------------------------------------------------------------------------------
# DO NOT EDIT BELOW THIS LINE
#------------------------------------------------------------------------------
INC = $(shell find $(SRC_DIR) -name '*.h')
SRC = $(shell find $(SRC_DIR) -name '*.c')
OBJ = $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(SRC:.c=.o))

TST_INC = $(shell find $(TST_SRC_DIR) -name '*.h')
TST_SRC = $(shell find $(TST_SRC_DIR) -name '*.c')
# Exclude binary main object file.
NMM_OBJ = $(filter-out %main.o, $(OBJ)) 
TST_OBJ = $(patsubst $(TST_SRC_DIR)/%, $(TST_OBJ_DIR)/%, $(TST_SRC:.c=.o))
# Exclude unit test main object files.
NMM_TST_OBJ = $(filter-out %.test.o, $(TST_OBJ)) 
# Gather all unit test files. 
# All files with *.test.c are considered unit test files.
TST_TARGETS = $(patsubst $(TST_SRC_DIR)/%.test.c, $(TST_OUT_DIR)/%.test, $(TST_SRC))

# Creates the binary.
all: $(TARGET)

# Cleans the build directory then rebuilds the binary.
remake: clean all

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(LIBS) $^ -o $(OUT_DIR)/$@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC) 
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $(LIBS) $(DEPS) $< -o $@

# Run all unit tests.
test: clean $(TST_TARGETS)

$(TST_OUT_DIR)/%.test: $(NMM_OBJ) $(NMM_TST_OBJ) $(TST_OBJ_DIR)/%.test.o
	$(CC) $(CFLAGS) $(LIBS) $(TST_LIBS) $^ -o $@
	$@

$(TST_OBJ_DIR)/%.o: $(TST_SRC_DIR)/%.c $(INC) $(TST_INC)
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $(LIBS) $(TST_LIBS) $(DEPS) $(TST_DEPS) $< -o $@

# Full clean. 
# Removes the build directory.
clean:
	@rm -rf $(OUT_DIR)

.PHONY: clean
