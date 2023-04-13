#include "libhtab.h"
#include <stdio.h>
#include <stdlib.h>

HashTableItem* init_table(int size) {
    HashTableItem *hash_table = calloc(size, sizeof(HashTableItem));

    return hash_table;
}