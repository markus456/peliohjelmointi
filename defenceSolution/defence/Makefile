CC = g++
CFLAGS = -c -I/usr/include/SDL2 -std=c++11 -D SYSTEM_LIBS
LDFLAGS = -lSDL2 -lSDL2_ttf -lSDL2_image

OBJECTS = main.o System.o Bullet.o Tiili.o TileMap.o Tower.o ui.o Road.o Controller.o Enemy.o Player.o
EXECUTABLE = defence

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJECTS): %.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm $(EXECUTABLE) $(OBJECTS)
