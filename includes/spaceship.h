#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "raylib.h"
#include "stdlib.h"
#include "bullet.h"


#define TIMER 0.7f
#define MAX_BULLET 15

typedef struct  {
    Texture2D texture;
    Vector2 position;
    Vector2 velocity;
    Queue bullets;

    int rotation;
    float cooldown;

    int ray;

} SpaceShip ;

SpaceShip* initSpaceShip(Texture2D texture, Vector2 pos, int ray);
void addBullet(SpaceShip* spaceship, Vector2 direction, bool isKeyDown);
void updateBullet(SpaceShip* spaceship) ;
void updateSpaceShip(SpaceShip* spaceship) ;
void drawBullet(SpaceShip* spaceship);
void drawSpaceShip(const SpaceShip* space_ship);
void unloadSpaceship(SpaceShip* spaceship);


#endif 
