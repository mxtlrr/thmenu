CC      := gcc
CFLAGS  := -g -std=gnu99 -Wall -Wextra

SRCS    := $(wildcard *.c)
BIN_DIR := bin/

TARGETS := $(SRCS:.c=.exe)
TARGETS := $(addprefix $(BIN_DIR)/, $(TARGETS))

all: $(TARGETS)

$(BIN_DIR)/%.exe: %.c | $(BIN_DIR)
	@echo "CC $<"
	@$(CC) $(CFLAGS) $< -o $@

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

clean:
	@rm -f $(TARGETS)