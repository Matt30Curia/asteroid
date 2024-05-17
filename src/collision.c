#include "../includes/collision.h"


bool asteroidCollide(SpaceShip* spaceship, const Asteroid* asteroid){

    float distance;
    Bullet tempBullet;

    for (int i = 0; i < spaceship->bullets.size; i++) {
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

int collide(SpaceShip* spaceship, AsteroidContainer* asteroidContainer) {

    Asteroid* asteroid = asteroidContainer->asteroids;
    int num = asteroidContainer->max_size;

    float distance;
    //Vector2SubtractValue(asteroid[i].edges[7], asteroid[i].ray)
    for (int i = 0; i < num; i++) {
        distance = powf(spaceship->position.x - asteroid[i].edges[7].x, 2) + pow(spaceship->position.y - asteroid[i].edges[7].y, 2) + 20;
        //space ship colllide
        if (CheckCollisionCircles(spaceship->position, 10, asteroid[i].position , asteroid[i].ray) && !asteroid[i].isDestroyed ){
            printf("game over");
            return -1;
        }

        if (asteroidCollide(spaceship, &asteroid[i] )) {
            if (asteroid[i].ray == SMALL) {

                destroyAsteroid(&asteroid[i]);
                return 10;

            }
            else
            {
                return divideAsteroid(asteroidContainer, i);
            }



        }

    }
    return 0;
}
