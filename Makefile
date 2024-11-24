CC = gcc
CFLAG = -Wall
CPACKAGE = `pkg-config --libs --cflags raylib`
OBJS = obj/asteroid.o obj/main.o obj/bullet.o obj/asteroid_container.o obj/spaceship.o obj/collision.o
SRCS = src/*.c
RAYLIB_PATH = "/home/user/Scrivania/raylib"
BIN = asteroid


all: $(BIN)

$(BIN): $(OBJS)
	$(CC)  $(CPACKAGE) -o $(BIN) $(OBJS)

obj/%.o: src/%.c
	$(CC) -g  $(CPACKAGE) -c $< -o $@

html:
	emcc -o web/$(BIN).html $(SRCS) $(WFLAG) $(RAYLIB_PATH)/src -I $(RAYLIB_PATH)/src/external -L. -L $(RAYLIB_PATH)/src -s USE_GLFW=3 -s ASYNCIFY --preload-file asset web/libraylib.a
clean:
	rm -f obj/*.o
	rm -f web/*.html
	rm -f web/*.js
	rm -f web/*.wasm
	rm -f ./$(BIN)
	rm -f *~
