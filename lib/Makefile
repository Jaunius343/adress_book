CFLAGS := -Wall -Werror -fpic

INCLUDE_DIR := ../include

LIBRARY := libaddress_book.so
HEADER := address_book.h
SRC := $(wildcard *.c)
OBJ := $(SRC:.c=.o)
INC := -I$(INCLUDE_DIR)
DESTDIR_LIB = /usr/local/lib
DESTDIR_H = /usr/local/include

.PHONY: all clean install uninstall

all: $(LIBRARY)

$(LIBRARY): $(OBJ)
	$(CC) $(CFLAGS) -shared -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

install: $(LIBRARY)
	install -D -m 644 $(LIBRARY) $(DESTDIR_LIB)/$(LIBRARY)
	install -D -m 644 $(INCLUDE_DIR)/$(HEADER) $(DESTDIR_H)/$(HEADER)

uninstall:
	rm -f $(DESTDIR_LIB)/$(LIBRARY)
	rm -f $(DESTDIR_H)/$(HEADER)

clean:
	rm -f $(LIBRARY) $(OBJ)
