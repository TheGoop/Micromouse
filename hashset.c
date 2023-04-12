#include <stdlib.h>
#include "hashset.h"

#define DEFAULT_CAPACITY 16

static int hash(Coord coord, int capacity) {
  return ((coord.row * 31) ^ coord.col) % capacity;
}

HashSet* hashset_create(int capacity) {
  if (capacity < 1) {
    capacity = DEFAULT_CAPACITY;
  }
  HashSet* set = malloc(sizeof(HashSet));
  set->buckets = calloc(capacity, sizeof(Coord));
  set->capacity = capacity;
  return set;
}

void hashset_free(HashSet* set) {
  free(set->buckets);
  free(set);
}

void hashset_add(HashSet* set, Coord coord) {
  int index = hash(coord, set->capacity);
  while (set->buckets[index].row != 0 || set->buckets[index].col != 0) {
    if (set->buckets[index].row == coord.row && set->buckets[index].col == coord.col) {
      return;
    }
    index = (index + 1) % set->capacity;
  }
  set->buckets[index] = coord;
}

void hashset_remove(HashSet* set, Coord coord) {
  int index = hash(coord, set->capacity);
  while (set->buckets[index].row != 0 || set->buckets[index].col != 0) {
    if (set->buckets[index].row == coord.row && set->buckets[index].col == coord.col) {
      set->buckets[index].row = 0;
      set->buckets[index].col = 0;
      return;
    }
    index = (index + 1) % set->capacity;
  }
}

int hashset_contains(HashSet* set, Coord coord) {
  int index = hash(coord, set->capacity);
  while (set->buckets[index].row != 0 || set->buckets[index].col != 0) {
    if (set->buckets[index].row == coord.row && set->buckets[index].col == coord.col) {
      return 1;
    }
    index = (index + 1) % set->capacity;
  }
  return 0;
}
