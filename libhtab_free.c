#include "libhtab.h"
#include <stdlib.h>

void free_table(HashTableItem *table) {
    free(table);
}