#ifndef ASTEROID_CONTAINER_H									 
#define ASTEROID_CONTAINER_H									 

#include "raylib.h"
#include "asteroid.h"

#define SCREEN_HEIGHT 800
#define SCREEN_WIDHT 800
#define ZERO_OFFSET 300

#define VELOCITY_ASTEROID 3


typedef struct {

	size_t max_size;
	size_t current_index;

	Asteroid* asteroids;
	
}AsteroidContainer;



AsteroidContainer* createAsteroids(size_t size);
void divideAsteroid(asteroidContainer* asteroidContainer, int collider);
void updateAsteroids(AsteroidContainer* asteroidContainer);
void DrawAsteroids(AsteroidContainer* asteroidContainer);




#endif
