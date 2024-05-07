CC = clang
CFLAGS = -Wall -g

all : asteroids

asteroids: asteroid.o spaceship.o bullet.o
	gcc -o asterois main.c asteroid.o spaceship.o bullet.o  -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

asteroid.o : asteroid.h
	gcc -c asteroid.h -lraylib -lGL -lm -lpthread -ldl -lrt -lX11


