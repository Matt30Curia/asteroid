#ifndef BULLET_H
#define BULLET_H

#include "raymath.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>


typedef struct {
    Vector2 position ;
    Vector2 direction;
    bool isActive; // Aggiunto un flag per indicare se il proiettile è attivo o meno
} Bullet ;


typedef struct  {
    int head ;
    int tail ;

    size_t size;

    Bullet* items;
} Queue;


void initQueue(Queue* queue, size_t size);
bool enQueue(Queue* queue, Bullet* element);
Bullet* deQueue(Queue* queue);



#endif
