#ifndef BULLET_H
#define BULLET_H

#define BULLET_SIZE 15


typedef struct Bullet {
    Vector2 position ;
    Vector2 direction;
    bool isActive = false; // Aggiunto un flag per indicare se il proiettile è attivo o meno
};


typedef struct Queue {
    int head = -1;  
    int tail = -1;
    Bullet items[BULLET_SIZE];
};


void initQueue(Queue* queue) {
    
    Bullet bullet = {};
    for (int i = 0; i < BULLET_SIZE; i++) {
        queue->items[i] = bullet;
    }
    
}   

// Check if the queue is full
bool isFull(Queue* queue) {
    if ((queue->head == queue->tail + 1) || (queue->head == 0 && queue->tail == BULLET_SIZE - 1)) return true;
    return false;
}

// Check if the queue is empty
bool isEmpty(Queue* queue) {
    if (queue->head == -1) return true;
    return false;
}

// Adding an element
bool enQueue(Queue* queue, Bullet* element) {
    if (isFull(queue))
        return false;
    else {
        if (queue->head == -1) queue->head = 0;
        queue->tail = (queue->tail + 1) % BULLET_SIZE;
        queue->items[queue->tail] = *element;
        
    }
}

// Removing an element
Bullet* deQueue(Queue* queue) {
    
   
    if (isEmpty(queue)) {
        
        return {};
    }
    else {
        Bullet* element;
        element = &queue->items[queue->head];
        
        if (queue->head == queue->tail) {
            queue->head = -1;
            queue->tail = -1;
        }
       
        else {
            queue->head = (queue->head + 1) % BULLET_SIZE;
        }
       
        return (element);
    }
}

#endif
