#ifndef WORD_MAX_LEN
#define WORD_MAX_LEN 255
#endif

#ifndef __LIBHTAB_H__
#define __LIBHTAB_H__

struct HashTableItem {
    char key[WORD_MAX_LEN];
    int value;
    HashTableItem *next;
} typedef HashTableItem;

static unsigned long hash_sdbm(unsigned char *str);

#endif