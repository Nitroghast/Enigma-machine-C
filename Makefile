CC      = gcc
CFLAGS  = -Wall -Wextra -Iheaders -MMD -MP
TARGET  = enigma
OBJS    = main.o libraries/errorFunctions.o libraries/inputFunctions.o libraries/encodingFunctions.o

ifeq ($(OS),Windows_NT)
    TARGET := $(TARGET).exe
endif

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

-include $(OBJS:.o=.d)

clean:
	rm -f $(OBJS) $(OBJS:.o=.d) $(TARGET)

.PHONY: clean