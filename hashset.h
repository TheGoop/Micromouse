#ifndef HASHSET_H
#define HASHSET_H

#include "coord.h"

typedef struct {
  Coord* buckets;
  int capacity;
  int curr_size;
} HashSet;

HashSet* hashset_create(int capacity);
void hashset_free(HashSet* set);
void hashset_add(HashSet* set, Coord coord);
void hashset_remove(HashSet* set, Coord coord);
int hashset_contains(HashSet* set, Coord coord);
int hashset_size(HashSet* set);

#endif /* HASHSET_H */
