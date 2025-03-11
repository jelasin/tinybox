# src/Makefile

.PHONY: all clean

SUB_DIRS := cmds utils

all: $(BUILD_DIR)/main.o
	$(CC) $(CFLAGS) $(BUILD_DIR)/main.o $(BUILD_DIR)/cmds/*.o $(BUILD_DIR)/utils/*.o -o $(TARGET)

$(BUILD_DIR)/main.o: main.c
	$(foreach dir, $(SUB_DIRS), $(MAKE) -C $(dir) all;)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(BUILD_DIR)/main.o
	$(foreach dir, $(SUB_DIRS), $(MAKE) -C $(dir) clean;)
