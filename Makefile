BUILD_DIR := build
SRC_DIRS := src tests
INC_DIR := include

CC := clang
CFLAGS := -std=c23 -g -Wall -Werror

vpath %.c $(SRC_DIRS)

OBJS := $(foreach dir, $(SRC_DIRS), $(patsubst %.c, $(BUILD_DIR)/%.o, $(notdir $(wildcard $(dir)/*.c))))

test: $(BUILD_DIR)/test
	./$(BUILD_DIR)/test

debug: $(BUILD_DIR)/test
	lldb ./$(BUILD_DIR)/test

$(BUILD_DIR)/test: $(OBJS)
	$(CC) $^ -o $@

$(BUILD_DIR)/%.o: %.c $(BUILD_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

.PHONY: init
init:
	make clean
	bear -- make test

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
