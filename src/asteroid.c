#include "../includes/asteroid.h"

Sound explosion;

Sound* loadSound() {
    // Dichiarazione della variabile statica per tenere traccia dello stato di inizializzazione
    static int initialized = 0;

    // Controlla se il suono è già stato inizializzato
    if (initialized == 0) {
        // Se non è stato inizializzato, esegui l'inizializzazione
        printf("Init suond...\n");
        // Qui inserisci il codice per caricare effettivamente il suono
        explosion = LoadSound("./asset/explosion.ogg");
        // Imposta la variabile initialized a 1 per indicare che il suono è stato inizializzato
        initialized = 1;
    } else {
        printf("sound initialized\n");
    }
    return &explosion;
}

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


Asteroid* initAsteroid(Vector2 position, Vector2 direction, int size, bool isDestroyed) {

    float avg_radius = (float)size;
    float irregularity = 0;
    float spikiness = 0.7;


    irregularity *= 2 * PI / EDGES_SIZE;
    spikiness *= avg_radius;

    Vector2* points = (Vector2*)malloc(EDGES_SIZE * sizeof(Vector2));

    float* angle_steps = randomAngleSteps(EDGES_SIZE, irregularity);


    if (points == NULL) {
        printf("allocation failed from initAsteroid");
        return NULL;
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
    astTmp->explosion = *loadSound();

    return astTmp;
}

void destroyAsteroid(Asteroid* asteroid) {
    asteroid->isDestroyed = true;
}

void resetEdges(Asteroid* asteroid, Vector2 oldPosition, Vector2 newPosition) {
    for (int i = 0; i < EDGES_SIZE; i++) {
        asteroid->edges[i] = Vector2Subtract(asteroid->edges[i], oldPosition);
        asteroid->edges[i] = Vector2Add(asteroid->edges[i], newPosition);
    }

}

