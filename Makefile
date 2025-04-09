BUILD_DIR := build
SRC_DIR := src
INC_DIR := include

CC := clang
CFLAGS := -std=c11 -g -Wall -Werror

OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(wildcard $(SRC_DIR)/*.c))

test: $(BUILD_DIR)/test
	./$(BUILD_DIR)/test

debug: $(BUILD_DIR)/test
	lldb ./$(BUILD_DIR)/test

.PHONY: test
test: $(BUILD_DIR)/test

$(BUILD_DIR)/test: $(OBJS)
	$(CC) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(BUILD_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
