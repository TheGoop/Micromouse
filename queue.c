#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

Queue* create_queue() {
  Queue* q = (Queue*)malloc(sizeof(Queue));
  q->front = q->rear = NULL;
  return q;
}

void enqueue(Queue* q, Coord data) {
  QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
  node->data = data;
  node->next = NULL;
  if (is_empty(q)) {
    q->front = q->rear = node;
  } else {
    q->rear->next = node;
    q->rear = node;
  }
  q->length += 1;
}

Coord dequeue(Queue* q) {
  if (is_empty(q)) {
    printf("Error: Queue is empty\n");
    exit(1);
  }
  QueueNode* front_node = q->front;
  Coord data = front_node->data;
  q->front = front_node->next;
  free(front_node);
  if (q->front == NULL) {
    q->rear = NULL;
  }
  q->length -= 1;
  return data;
}

int is_empty(Queue* q) {
  return q->front == NULL;
}

void destroy_queue(Queue* q) {
  while (!is_empty(q)) {
    dequeue(q);
  }
  free(q);
}

int queue_size(Queue* q) {
  return q->length;
}
