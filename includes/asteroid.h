#ifndef ASTEROID_H
#define ASTEROID_H

#include "raylib.h"
#include "raymath.h"
#include "math.h"
#include "stdlib.h"
#include "stdio.h"

#define EDGES_SIZE 8

enum AsteroidSize {
    SMALL = 40, MEDIUM = 30, LARGE = 50
};


typedef struct {
    Sound explosion;

    Vector2 position;
    Vector2 direction;

    int ray;
    bool isDestroyed;

    Vector2* edges;


} Asteroid ;


Asteroid* initAsteroid(Vector2 position, Vector2 direction, int size, bool isDestroyed);
void destroyAsteroid(Asteroid* asteroid);
void resetEdges(Asteroid* asteroid, Vector2 oldPosition, Vector2 newPosition);


#endif 
