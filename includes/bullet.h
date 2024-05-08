#ifndef BULLET_H
#define BULLET_H

#include "raymath.h"
#include <stdbool.h>

#define BULLET_SIZE 15


typedef struct {
    Vector2 position ;
    Vector2 direction;
    bool isActive; // Aggiunto un flag per indicare se il proiettile è attivo o meno
} Bullet ;


typedef struct  {
    int head ;
    int tail ;
    Bullet items[BULLET_SIZE];
} Queue;


void initQueue(Queue* queue);
bool enQueue(Queue* queue, Bullet* element);
Bullet* deQueue(Queue* queue);



#endif
