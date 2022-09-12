#ifndef SORT_H
#define SORT_H

#include "inventory.h"

void quicksort(struct part arr[], int low, int high);
int split(struct part arr[], int low, int high);

#endif