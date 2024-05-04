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


//--------------- Implemented function -----------------//

AsteroidContainer* createAsteroids(size_t size){

    const int height = SCREEN_HEIGHT;
    const int width = SCREEN_WIDHT;

    Vector2 direction;
    Vector2 position;

    Asteroid* asteroids = (Asteroid*)malloc(size * 4 * sizeof(Asteroid));

    // Check if memory allocation was successful
    if (asteroids == NULL) {
        printf("Memory allocation failed from createAsteroids\n");
        return nullptr;
    }

	int side; //give the screen size for asteroid spawn
	
    for (int i = 0; i < numAsteroid; i++) {

        side = GetRandomValue(0, 3);
        position  = sideFuncs[side].positionFunc();
        direction = sideFuncs[side].directionFunc();
        
        if (i < num) 
            asteroids[i] = initAsteroid(position, Vector2Scale(direction, VELOCITY_ASTEROID), LARGE, false);
        else 
            asteroids[i] = initAsteroid(position, Vector2Scale(direction, VELOCITY_ASTEROID), LARGE, true);
        
    }

    AsteroidContainer* containerTmp = (AsteroidContainer)malloc(sizeof(AsteroidContainer));

	containerTmp->asteroids = asteroids;
	containerTmp->max_size = size * 4;
	containerTmp->current_index = size;

    return containerTmp;
}

void divideAsteroid(asteroidContainer* asteroidContainer, int collider) {

    Vector2 initalPos = asteroidContainer->asteroids[collider].position;
    Vector2 direction;
    asteroidContainer->curr_index += 1;
    
    if (asteroidContainer->curr_index < asteroidContainer->total_size){
       
       if (asteroidContainer->asteroids[collider].ray == LARGE) {
         
          direction = Vector2Scale(sideFuncs[GetRandomValue(0, 3)].directionFunc(), VELOCITY_ASTEROID ) ;
          asteroidContainer->asteroids[asteroidContainer->curr_index] = initAsteroid(initalPos, direction, MEDIUM, false);
          
          direction = Vector2Scale(direction, -1);
          asteroidContainer->asteroids[collider] = initAsteroid( initalPos, direction, MEDIUM, false);
          
       }

       else if (asteroidContainer->asteroids[collider].ray == MEDIUM) {

          direction = Vector2Scale(sideFuncs[GetRandomValue(0, 3)].directionFunc(), VELOCITY_ASTEROID );
          asteroidContainer->asteroids[collider] = initAsteroid(initalPos, direction, SMALL, false);

          direction = Vector2Scale(direction, -1);
          asteroidContainer->asteroids[asteroidContainer->curr_index] =  initAsteroid(initalPos, direction, SMALL, false);
       }

    }
    de_index = collider;
    
   
}


void updateAsteroid(AsteroidContainer* asteroidContainer) {

    Asteroid* asteroids = asteroidContainer->asteroids;
    size_t size = asteroidContainer->max_size;


    for (int i = 0; i < size; i++) {

        Vector2 direction = Vector2Scale(asteroids[i].direction, GetFrameTime());

        // Aggiorna la posizione dell'asteroide in base alla sua velocità
        asteroids[i].position = Vector2Add(asteroids[i].position, direction);

        for (int j = 0; j < EDGES_SIZE; j++) {
            // Aggiorna le coordinate dei punti dell'asteroide
            asteroids[i].edges[j] = Vector2Add(direction, asteroids[i].edges[j]);
        }

        // Verifica se l'asteroide è uscito dai bordi della schermata
        if (asteroids[i].edges[EDGES_SIZE - 1].x > SCREEN_WIDHT  + ZERO_OFFSET ||
            asteroids[i].edges[EDGES_SIZE - 1].x < -ZERO_OFFSET ||
            asteroids[i].edges[EDGES_SIZE - 1].y > SCREEN_HEIGHT + ZERO_OFFSET ||
            asteroids[i].edges[EDGES_SIZE - 1].y < -ZERO_OFFSET) {

            // Riappare l'asteroide su un lato casuale
            int side = GetRandomValue(0, 3);
            Vector2 newPosition = sideFuncs[side].positionFunc();
            resetEdges(&asteroids[i], asteroids[i].position, newPosition);
 

            asteroids[i].position = newPosition;
            asteroids[i].direction = Vector2Scale(sideFuncs[side].directionFunc(), VELOCITY_ASTEROID);
        }

        
    }
}


void DrawAsteroids(AsteroidContainer* asteroidContainer)
{
    Asteroid* asteroid = asteroidContainer->asteroids;

    for (int i = 0; i < asteroidContainer->max_size; i++) {
        
        if (asteroid[i].isDestroyed == false) {
            // Disegna i bordi del poligono
            for (int j = 0; j < EDGES_SIZE; j++) {

                int nextIndex = (j + 1) % EDGES_SIZE;
                //printf("edges x: %f \n edges y: %f \n", asteroid[i].edges[j].x, asteroid[i].edges[j].y);
                DrawLineV(asteroid[i].edges[j], asteroid[i].edges[nextIndex], WHITE);
            }
        }
    }
}



#endif
