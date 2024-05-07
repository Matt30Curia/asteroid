#include "../includes/asteroid_container.h"

typedef struct SideSpawnFuncs {
    Vector2(*positionFunc)(void);
    Vector2(*directionFunc)(void);
};


Vector2 positionFuncTop(void)   { return { (float)GetRandomValue(0, SCREEN_HEIGHT + ZERO_OFFSET), -50 }; }
Vector2 positionFuncLeft(void)  { return { -50, (float)GetRandomValue(0, SCREEN_WIDHT + ZERO_OFFSET), }; }
Vector2 positionFuncRight(void) { return { (float)SCREEN_WIDHT + ZERO_OFFSET, (float)GetRandomValue(0, (float)SCREEN_HEIGHT + ZERO_OFFSET) }; }
Vector2 positionFuncBottom(void){ return { (float)GetRandomValue(0, SCREEN_WIDHT + ZERO_OFFSET), (float)SCREEN_HEIGHT + ZERO_OFFSET }; }

Vector2 directionTop(void) { return { (float)GetRandomValue(-50, 50), (float)GetRandomValue(10, 50) }; }
Vector2 directionBottom(void) { return { (float)GetRandomValue(-50, 50), (float)GetRandomValue(-50, -10) }; }
Vector2 directionLeft(void) { return { (float)GetRandomValue(10, 50) , (float)GetRandomValue(-50, 50) }; }
Vector2 directionRight(void) { return { (float)GetRandomValue(-50, -10) , (float)GetRandomValue(-50, 50) }; }

SideSpawnFuncs sideFuncs[] = {
        { positionFuncTop, directionTop },
        { positionFuncLeft, directionLeft },
        { positionFuncRight, directionRight },
        { positionFuncBottom, directionBottom },
};



AsteroidContainer* createAsteroids(size_t size){

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

    AsteroidContainer* containerTmp = (AsteroidContainer*)malloc(sizeof(AsteroidContainer));

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

                DrawLineV(asteroid[i].edges[j], asteroid[i].edges[nextIndex], WHITE);
            }
        }
    }
}


