CFLAGS := -Wall -Wextra -Wpedantic -std=c11 -O2
LDFLAGS :=

TARGET_EXEC := address_book

SRCS := main.c linked_list.c
OBJS := $(SRCS:.c=.o)
DEPS := $(OBJS:.o=.d)

.PHONY: all clean run

all: $(TARGET_EXEC)

$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

-include $(DEPS)


clean:
	rm -f $(OBJS) $(DEPS) $(TARGET_EXEC)
