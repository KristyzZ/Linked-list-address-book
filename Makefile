CC = gcc
CFLAGS = -Wall -Wextra -std=c11

TARGET_EXEC := address_book
SRCS := main.c linked_list.c
OBJS := $(SRCS:.c=.o)

all: $(TARGET_EXEC)

$(TARGET_EXEC): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET_EXEC)
	

