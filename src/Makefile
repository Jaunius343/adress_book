CFLAGS = -Wall -Wextra -std=c11 -I$(INC_DIR)
LDFLAGS = -L$(LIB_DIR) -laddress_book

LIB_DIR := ../lib
INC_DIR := ../include
SRC_DIR := .
BIN_DIR := ../bin

SRCS := $(wildcard $(SRC_DIR)/*.c)

OBJS := $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(SRCS))

EXECUTABLE := address_book
EXEC_DIR := ../$(EXECUTABLE)

.PHONY: all clean

all: $(EXEC_DIR)

$(EXEC_DIR): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR):
	mkdir -p $@

clean:
	rm -f $(BIN_DIR)/*.o $(EXEC_DIR)
