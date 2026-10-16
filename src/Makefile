CC ?= $(CROSS_COMPILE)gcc

TARGET = network_monitor

CFLAGS += -Iinclude

SRC = \
	src/main.c \
	src/interface.c \
	src/traffic.c \
	src/connectivity.c \
	src/cpu.c \
	src/memory.c \
	src/disk.c \
	src/process.c \
	src/logger.c \
	src/config.c \
        src/alerts.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) -lncurses

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
