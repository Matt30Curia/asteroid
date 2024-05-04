#ifndef ASTEROID_H
#define ASTEROID_H

#include "raylib.h"
#define EDGES_SIZE 8

enum AsteroidSize {
    SMALL = 10, MEDIUM = 30, LARGE = 50
};


typedef struct {

    Vector2 position;
    Vector2 direction;

    int ray;
    bool isDestroyed;

    Vector2* edges;

} Asteroid ;



Asteroid* initAsteroid(Vector2 position, Vector2 direction, AsteroidSize size, bool isDestroyed);



//------------------ IMPLEMENTED FUNCTION -------------------//



float Clip(float value, float lower, float upper) {
    return fmin(upper, fmax(value, lower));
}


float* randomAngleSteps(int steps, float irregularity) {
    float* angles = (float*)malloc(steps * sizeof(float));

    // generate n angle steps
    float lower = (2 * PI / steps) - irregularity;
    float upper = (2 * PI / steps) + irregularity;
    float cumsum = 0;

    for (int i = 0; i < steps; i++) {
        float angle = GetRandomValue((int)(lower * 1000), (int)(upper * 1000)) / 1000.0f;
        angles[i] = angle;
        cumsum += angle;
    }

    // normalize the steps so that point 0 and point n+1 are the same
    cumsum /= (2 * PI);
    for (int i = 0; i < steps; i++) {
        angles[i] /= cumsum;
    }

    return angles;
}


Asteroid* initAsteroid(Vector2 position, Vector2 direction, AsteroidSize size, bool isDestroyed) {

    float avg_radius = (float)size;
    float irregularity = 0;
    float spikiness = 0.7;


    irregularity *= 2 * PI / EDGES_SIZE;
    spikiness *= avg_radius;

    Vector2* points = (Vector2*)malloc(EDGES_SIZE * sizeof(Vector2));

    float* angle_steps = randomAngleSteps(EDGES_SIZE, irregularity);


    if (points == NULL) {
        puts("allocation error from initAsteroid");
        return nullptr;
	}
	
    // now generate the points
    float angle = GetRandomValue(0, 360) * DEG2RAD;
    for (int i = 0; i < EDGES_SIZE; i++) {
        float radius = Clip(GetRandomValue((int)(avg_radius - spikiness), (int)(avg_radius + spikiness)), 0, 2 * avg_radius);
        points[i].x = position.x + radius * cosf(angle);
        points[i].y = position.y + radius * sinf(angle);
        angle += angle_steps[i];
    }

    free(angle_steps);

	Asteroid* astTmp = (Asteroid*)malloc(sizeof(Asteroid));

	astTmp->position = position;
	astTmp->direction = direction;
	astTmp->ray = size;
	astTmp->isDestroyed = isDestroyed;
	astTmp->edges = points;
    
    return astTmp;
}

#endif 
