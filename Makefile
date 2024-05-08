CC = cc
CFLAG = -Wall
CPACKAGE = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
OBJS = obj/asteroid.o obj/main.o obj/bullet.o obj/asteroid_container.o obj/spaceship.o obj/collision.o
BIN = asteroid



all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAG) $(CPACKAGE) -o $(BIN) $(OBJS)

obj/%.o: src/%.c
	$(CC) $(CFLAG) -c $< -o $@


clean:
	rm -f obj/*.o
	rm -f ./$(BIN)
	rm -f *~
