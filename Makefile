CC = cc
CFLAG = -Wall
CPACKAGE = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
OBJS = obj/asteroid.o obj/main.o obj/bullet.o obj/asteroid_container.o obj/spaceship.o obj/collision.o
SRCS = src/main.c src/bullet.c src/asteroid.c src/asteroid_container.c src/spaceship.c src/collision.c
WFLAG = -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces -Wunused-result -Os -I. -I
RAYLIB_PATH = ""
BIN = asteroid


all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAG) $(CPACKAGE) -o $(BIN) $(OBJS)

obj/%.o: src/%.c
	$(CC) $(CFLAG) -c $< -o $@

html:
	emcc -o web/$(BIN).html $(SRCS) $(WFLAG) $(RAYLIB_PATH)/src -I $(RAYLIB_PATH)/src/external -L. -L $(RAYLIB_PATH)/src -s USE_GLFW=3 -s ASYNCIFY --preload-file asset web/libraylib.a
clean:
	rm -f obj/*.o
	rm -f web/*.html
	rm -f web/*.js
	rm -f web/*.wasm
	rm -f ./$(BIN)
	rm -f *~
