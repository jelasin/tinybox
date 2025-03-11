# src/utils/Makefile

SRCS = $(wildcard *.c)
OBJS = $(SRCS:%.c=$(BUILD_DIR)/utils/%.o)

.PHONY: all clean

all: $(OBJS)

$(BUILD_DIR)/utils/%.o: %.c
	@[ -d $(BUILD_DIR)/utils ] || mkdir -p $(BUILD_DIR)/utils
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@rm -rf $(BUILD_DIR)/utils