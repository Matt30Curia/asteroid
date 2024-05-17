#ifndef ASTEROID_CONTAINER_H									 
#define ASTEROID_CONTAINER_H									 

#include "raylib.h"
#include "asteroid.h"

#define SCREEN_HEIGHT 800
#define SCREEN_WIDHT 800
#define ZERO_OFFSET 200

#define VELOCITY_ASTEROID 3


typedef struct {

	size_t max_size;
	size_t current_index;

	Asteroid* asteroids;
	
}AsteroidContainer;



AsteroidContainer* createAsteroids(size_t size);
int divideAsteroid(AsteroidContainer* asteroidContainer, int collider);
void updateAsteroids(AsteroidContainer* asteroidContainer);
void drawAsteroids(AsteroidContainer* asteroidContainer);
void freeAsteroids(AsteroidContainer* asteroidContainer);



#endif
