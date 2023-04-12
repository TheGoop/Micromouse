#ifndef QUEUE_H
#define QUEUE_H

#include "coord.h"

typedef struct queue_node {
  Coord data;
  struct queue_node* next;
} QueueNode;

typedef struct {
  QueueNode* front;
  QueueNode* rear;
} Queue;

Queue* create_queue();
void enqueue(Queue* q, Coord data);
Coord dequeue(Queue* q);
int is_empty(Queue* q);
void destroy_queue(Queue* q);

#endif
