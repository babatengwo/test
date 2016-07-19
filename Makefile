TARGET=capture7
CC=gcc
OBJS=main.o v4l.o
DESTDIR=

all:$(TARGET)
$(TARGET):$(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

main.o:main.c v4l.h
	$(CC) -c -o main.o main.c

v4lcto.o:v4l.c v4l.h
	$(CC) -c -o v4l.o v4l.c
.PHONY:install
install:
	cp -f $(TARGET) $(DESTDIR)
.PHONY:clean
clean:
	rm -rf *.o *~ $(TARGET)
