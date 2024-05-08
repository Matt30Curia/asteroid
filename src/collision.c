#include "../includes/collision.h"


bool asteroidCollide(SpaceShip* spaceship, const Asteroid* asteroid){

    float distance;
    Bullet tempBullet;

    for (int i = 0; i < BULLET_SIZE; i++) {
        tempBullet = spaceship->bullets.items[i];

        if (tempBullet.isActive) {

            distance = powf(tempBullet.position.x - asteroid->position.x, 2) + pow(tempBullet.position.y - asteroid->position.y, 2);

            if (distance < powf(asteroid->ray, 2) && !asteroid->isDestroyed) {

                spaceship->bullets.items[i].isActive = false;
                deQueue(&spaceship->bullets);
                return true;
            }
        }
    }
    return false;
}

bool collide(SpaceShip* spaceship, AsteroidContainer* asteroidContainer) {

    Asteroid* asteroid = asteroidContainer->asteroids;
    int num = asteroidContainer->max_size;

    float distance;

    for (int i = 0; i < num; i++) {
        distance = powf(spaceship->position.x - asteroid[i].position.x, 2) + pow(spaceship->position.y - asteroid[i].position.y, 2) + 50;
        //space ship colllide
        if (distance < powf(asteroid[i].ray, 2)){

            return true;
        }

        if (asteroidCollide(spaceship, &asteroid[i] )) {
            if (asteroid[i].ray == SMALL) {

                destroyAsteroid(&asteroid[i]);
            }
            if (asteroid[i].ray == LARGE || asteroid[i].ray == MEDIUM)
            {
                divideAsteroid(asteroidContainer, i);
            }



        }

    }
    return false;
}
