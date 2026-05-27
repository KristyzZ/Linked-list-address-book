CC := gcc
CFLAGS := -Wall -Wextra -Wpedantic -std=c11 -MMD -MP -I../lib

LDLIBS := -llinkedlist
LDFLAGS := -L../lib -Wl,-rpath,'$$ORIGIN/lib'

BUILD_DIR := ../

TARGET := address_book
SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)
DEPS := $(OBJS:.o=.d)

.PHONY: all clean

all: $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $@

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(DEPS) $(BUILD_DIR)/$(TARGET)

-include $(DEPS)
