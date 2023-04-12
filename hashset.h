#ifndef HASHSET_H
#define HASHSET_H

#include "coord.h"

typedef struct {
  Coord* buckets;
  int capacity;
} HashSet;

HashSet* hashset_create(int capacity);
void hashset_free(HashSet* set);
void hashset_add(HashSet* set, Coord coord);
void hashset_remove(HashSet* set, Coord coord);
int hashset_contains(HashSet* set, Coord coord);

#endif /* HASHSET_H */
