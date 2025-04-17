# Makefile for easy_conf

CC = gcc
AR = ar
CFLAGS = -Wall -Wextra -O2

SRC = src/easy_conf.c src/utility.c
OBJ = $(SRC:.c=.o)
LIB = libeasy_conf.a
INSTALL_LIB_DIR = /usr/local/lib
INSTALL_INC_DIR = /usr/local/include

all: $(LIB)

$(LIB): $(OBJ)
	$(AR) rcs $@ $^

install: $(LIB)
	install -m 644 $(LIB) $(INSTALL_LIB_DIR)/
	install -m 644 easy_conf.h $(INSTALL_INC_DIR)/

uninstall:
	rm -f $(INSTALL_LIB_DIR)/$(LIB)
	rm -f $(INSTALL_INC_DIR)/easy_conf.h

clean:
	rm -f $(OBJ) $(LIB)

.PHONY: all install uninstall clean
