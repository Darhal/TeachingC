TARGET_EXEC ?= test_exec
CFLAGS 		?= -g -Og -Wno-unused-result -fsanitize=address
COMPILER 	?= gcc

BUILD_DIR 	?= ./build
SRC_DIRS 	?= ./

SRCS 		:= $(shell find $(SRC_DIRS) -name "*.c")
OBJS 		:= $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS 		:= $(OBJS:.o=.d)

$(TARGET_EXEC): $(OBJS)
	$(COMPILER) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(COMPILER) $(CFLAGS) -c $< -o $@

run: $(TARGET_EXEC)
	./$(TARGET_EXEC)

.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)
	$(RM) -r $(TARGET_EXEC)

-include $(DEPS)

MKDIR_P ?= mkdir -p
