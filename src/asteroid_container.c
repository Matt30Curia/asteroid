#include "../includes/asteroid_container.h"

typedef struct{
    Vector2(*positionFunc)(void);
    Vector2(*directionFunc)(void);
}  SideSpawnFuncs;


Vector2 positionFuncTop(void)   { return (Vector2){ (float)GetRandomValue(0, SCREEN_HEIGHT + ZERO_OFFSET), -50 }; }
Vector2 positionFuncLeft(void)  { return (Vector2){ -50, (float)GetRandomValue(0, SCREEN_WIDHT + ZERO_OFFSET), }; }
Vector2 positionFuncRight(void) { return (Vector2){ (float)SCREEN_WIDHT + ZERO_OFFSET, (float)GetRandomValue(0, (float)SCREEN_HEIGHT + ZERO_OFFSET) }; }
Vector2 positionFuncBottom(void){ return (Vector2){ (float)GetRandomValue(0, SCREEN_WIDHT + ZERO_OFFSET), (float)SCREEN_HEIGHT + ZERO_OFFSET }; }

Vector2 directionTop(void) { return (Vector2){ (float)GetRandomValue(-50, 50), (float)GetRandomValue(10, 50) }; }
Vector2 directionBottom(void) { return (Vector2){ (float)GetRandomValue(-50, 50), (float)GetRandomValue(-50, -10) }; }
Vector2 directionLeft(void) { return (Vector2){ (float)GetRandomValue(10, 50) , (float)GetRandomValue(-50, 50) }; }
Vector2 directionRight(void) { return (Vector2){ (float)GetRandomValue(-50, -10) , (float)GetRandomValue(-50, 50) }; }

SideSpawnFuncs sideFuncs[] = {
        { positionFuncTop, directionTop },
        { positionFuncLeft, directionLeft },
        { positionFuncRight, directionRight },
        { positionFuncBottom, directionBottom },
};


AsteroidContainer* createAsteroids(size_t size){

    Vector2 direction;
    Vector2 position;
    size_t max_size = size * 5;
    Asteroid* asteroids = (Asteroid*)malloc(max_size * sizeof(Asteroid));

    // Check if memory allocation was successful
    if (asteroids == NULL) {
        printf("Memory allocation failed from createAsteroids\n");
        return NULL;
    }

	int side; //give the screen size for asteroid spawn

    for (int i = 0; i < max_size; i++) {

        side = GetRandomValue(0, 3);
        position  = sideFuncs[side].positionFunc();
        direction = sideFuncs[side].directionFunc();

        if (i < size)
            asteroids[i] = *initAsteroid(position, Vector2Scale(direction, VELOCITY_ASTEROID), LARGE, false);
        else
            asteroids[i] = *initAsteroid(position, Vector2Scale(direction, VELOCITY_ASTEROID), LARGE, true);

    }

    AsteroidContainer* containerTmp = (AsteroidContainer*)malloc(sizeof(AsteroidContainer));

	containerTmp->asteroids = asteroids;
	containerTmp->max_size = max_size;
	containerTmp->current_index = size;

    return containerTmp;
}


void reallocAsteroids(AsteroidContainer* asteroidContainer, size_t size){

    Vector2 direction;
    Vector2 position;
    size_t max_size = size * 5;
    Asteroid* asteroids = (Asteroid*)realloc(asteroidContainer->asteroids, max_size* sizeof(Asteroid));

    // Check if memory allocation was successful
    if (asteroids == NULL) {
        printf("Memory allocation failed from createAsteroids\n");
    }

	int side; //give the screen size for asteroid spawn

    for (int i = 0; i < max_size; i++) {

        side = GetRandomValue(0, 3);
        position  = sideFuncs[side].positionFunc();
        direction = sideFuncs[side].directionFunc();

        if (i < size)
            asteroids[i] = *initAsteroid(position, Vector2Scale(direction, VELOCITY_ASTEROID), LARGE, false);
        else
            asteroids[i] = *initAsteroid(position, Vector2Scale(direction, VELOCITY_ASTEROID), LARGE, true);

    }

	asteroidContainer->asteroids = asteroids;
	asteroidContainer->max_size = max_size;
	asteroidContainer->current_index = size;
}

int divideAsteroid(AsteroidContainer* asteroidContainer, int collider) {

    Vector2 initalPos = asteroidContainer->asteroids[collider].position;
    Vector2 direction;
    asteroidContainer->current_index += 1;


    if (asteroidContainer->current_index < asteroidContainer->max_size){
        PlaySound(asteroidContainer->asteroids[collider].explosion);

       if (asteroidContainer->asteroids[collider].ray == LARGE) {

          direction = sideFuncs[GetRandomValue(0, 3)].directionFunc() ;
          asteroidContainer->asteroids[asteroidContainer->current_index] = *initAsteroid(initalPos, direction, MEDIUM, false);

          direction = Vector2Scale(direction, -1);
          asteroidContainer->asteroids[collider] = *initAsteroid( initalPos, direction, MEDIUM, false);

          return 20;

       }

       else if (asteroidContainer->asteroids[collider].ray == MEDIUM) {

          direction = sideFuncs[GetRandomValue(0, 3)].directionFunc();
          asteroidContainer->asteroids[collider] = *initAsteroid(initalPos, direction, SMALL, false);

          direction = Vector2Scale(direction, -1);
          asteroidContainer->asteroids[asteroidContainer->current_index] =  *initAsteroid(initalPos, direction, SMALL, false);
          return 10;
       }

    }
    return 0;

}


void updateAsteroids(AsteroidContainer* asteroidContainer) {

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
        /*if (asteroids[i].edges[EDGES_SIZE - 1].x > SCREEN_WIDHT  + ZERO_OFFSET ||
            asteroids[i].edges[EDGES_SIZE - 1].x < -ZERO_OFFSET ||
            asteroids[i].edges[EDGES_SIZE - 1].y > SCREEN_HEIGHT + ZERO_OFFSET ||
            asteroids[i].edges[EDGES_SIZE - 1].y < -ZERO_OFFSET) {

            // Riappare l'asteroide su un lato casuale
            int side = GetRandomValue(0, 3);
            Vector2 newPosition = sideFuncs[side].positionFunc();
            resetEdges(&asteroids[i], asteroids[i].position, newPosition);


            asteroids[i].position = newPosition;
            asteroids[i].direction = Vector2Scale(sideFuncs[side].directionFunc(), VELOCITY_ASTEROID);
        }*/
        if (asteroids[i].edges[EDGES_SIZE - 1].x > SCREEN_WIDHT  + ZERO_OFFSET){

            Vector2 newPosition = {-ZERO_OFFSET, asteroids[i].position.y};
            resetEdges(&asteroids[i], asteroids[i].position, newPosition);

            asteroids[i].position = newPosition;
            asteroids[i].direction = Vector2Scale(sideFuncs[GetRandomValue(0, 3)].directionFunc(), VELOCITY_ASTEROID);
        }
        if (asteroids[i].edges[EDGES_SIZE - 1].x < -ZERO_OFFSET ){
            Vector2 newPosition = {SCREEN_HEIGHT + ZERO_OFFSET, asteroids[i].position.y};
            resetEdges(&asteroids[i], asteroids[i].position, newPosition);

            asteroids[i].position = newPosition;
            asteroids[i].direction = Vector2Scale(sideFuncs[GetRandomValue(0, 3)].directionFunc(), VELOCITY_ASTEROID);
        }
        if (asteroids[i].edges[EDGES_SIZE - 1].y > SCREEN_HEIGHT + ZERO_OFFSET){
            Vector2 newPosition = {asteroids[i].position.x,  -ZERO_OFFSET};
            resetEdges(&asteroids[i], asteroids[i].position, newPosition);

            asteroids[i].position = newPosition;
            asteroids[i].direction = Vector2Scale(sideFuncs[GetRandomValue(0, 3)].directionFunc(), VELOCITY_ASTEROID);
        }
        if (asteroids[i].edges[EDGES_SIZE - 1].y < -ZERO_OFFSET){
            Vector2 newPosition = {asteroids[i].position.x,  SCREEN_HEIGHT + ZERO_OFFSET};
            resetEdges(&asteroids[i], asteroids[i].position, newPosition);
            asteroids[i].position = newPosition;
            asteroids[i].direction = Vector2Scale(sideFuncs[GetRandomValue(0, 3)].directionFunc(), VELOCITY_ASTEROID);
        }


    }
}


void drawAsteroids(AsteroidContainer* asteroidContainer)
{
    Asteroid* asteroid = asteroidContainer->asteroids;

    for (int i = 0; i < asteroidContainer->max_size; i++) {

        if (asteroid[i].isDestroyed == false) {
            // Disegna i bordi del poligono
            for (int j = 0; j < EDGES_SIZE; j++) {

                int nextIndex = (j + 1) % EDGES_SIZE;

                DrawLineV(asteroid[i].edges[j], asteroid[i].edges[nextIndex], WHITE);
            }
        }
    }
}


void freeAsteroids(AsteroidContainer* asteroids) {

    free(asteroids->asteroids);
    free(asteroids);
}
