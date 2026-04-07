CC = gcc

CFLAGS = -Wall -g

TARGET = c_unplugged

OBJS = main.o list.o album.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c functions.h
	$(CC) $(CFLAGS) -c main.c

list.o: list.c functions.h
	$(CC) $(CFLAGS) -c list.c

album.o: album.c functions.h
	$(CC) $(CFLAGS) -c album.c

clean:
	rm -f $(TARGET) $(OBJS)