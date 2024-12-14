CC = gcc
CFLAGS = -Wall -g
TARGET = metro

all: $(TARGET)

$(TARGET): main.c
    $(CC) $(CFLAGS) main.c -o $(TARGET)

clean:
    rm -f $(TARGET)
