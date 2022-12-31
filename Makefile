CC=gcc
FLAGSBIN=-I./include -ansi -std=c11 -c
FLAGSLINK=-o code.elf

SRC=src/main.c src/map.c src/display.c src/player.c src/position.c src/rooms.c
OBJ=obj/main.o obj/map.o obj/display.o obj/player.o obj/position.o obj/rooms.o
LIBSOURCE=lib/cvector/cvector.c
LIBOBJ=lib/libcontainers.so

LIB_INC_FLAG=-I./lib/cvector/
LIBLINK=-L./lib -lcontainers -Wl,-rpath,./lib -lncurses

# objects binary files

obj/main.o: src/main.c
	$(CC) $(FLAGSBIN) src/main.c -o obj/main.o

obj/map.o: src/map.c
	$(CC) $(FLAGSBIN) src/map.c -o obj/map.o

obj/display.o: src/display.c
	$(CC) $(FLAGSBIN) src/display.c -o obj/display.o

obj/player.o: src/player.c
	$(CC) $(FLAGSBIN) src/player.c -o obj/player.o

obj/position.o: src/position.c
	$(CC) $(FLAGSBIN) src/position.c -o obj/position.o

obj/rooms.o: src/rooms.c
	$(CC) $(FLAGSBIN) src/rooms.c -o obj/rooms.o

# build dynamic library

lib/containers.o: $(LIBSOURCE)
	$(CC) -fPIC -c $(LIBSOURCE) -o lib/containers.o

lib/libcontainers.so: lib/containers.o
	$(CC) -shared -o $(LIBOBJ) lib/containers.o

# link sources

code.elf: obj $(OBJ) $(LIBOBJ)
	$(CC) $(OBJ) $(FLAGSLINK) $(LIBLINK)

# create dir for collecte object files

obj:
	mkdir obj