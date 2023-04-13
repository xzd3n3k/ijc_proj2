#define TABLE_SIZE 30011

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libhtab.h"

#ifndef WORD_MAX_LEN
#define WORD_MAX_LEN 255
#endif


int main() {

    HashTableItem *hash_table = init_table(TABLE_SIZE);
    char word[WORD_MAX_LEN];

    while (scanf("%s", word) == 1) {
        unsigned long index = hash_sdbm(word) % TABLE_SIZE;
        HashTableItem *node = &hash_table[index];

        while (node != NULL && strcmp(node->key, word) != 0)
            node = node->next;

        if (node == NULL) {
            node = (HashTableItem *) malloc(sizeof(HashTableItem));
            strcpy(node->key, word);
            node->value = 0;
            node->next = &hash_table[index];
            hash_table[index] = *node;
        }

        node->value++;
    }

    for (int i = 0; i < TABLE_SIZE; i++) {
        HashTableItem *node = &hash_table[i];

        while (node != NULL) {
            printf("%s\t%d\n", node->key, node->value);
            node = node->next;
        }

    }

    free_table(hash_table);

    return 0;
}
