# src/cmds/Makefile

SRCS = $(wildcard *.c)
OBJS = $(SRCS:%.c=$(BUILD_DIR)/cmds/%.o)

.PHONY: all clean

all: $(OBJS)

$(BUILD_DIR)/cmds/%.o: %.c
	@[ -d $(BUILD_DIR)/cmds ] || mkdir -p $(BUILD_DIR)/cmds
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@rm -rf $(BUILD_DIR)/cmds
