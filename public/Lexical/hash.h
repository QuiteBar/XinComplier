#ifndef HASH_H
#define HASH_H
#include "xin_structs.h"

#define MAXKEY 4096

wordhash  XHashTable[MAXKEY];

dynamicstr* mkdynamicstr(char* str, int len);

unsigned int BKDRHash(dynamicstr *str);	// BKDR Hash Function
void hashinit(wordhash* hashtable, int hashtablelen);
wordhash * word_insert(dynamicstr* word, int tokencode);
wordhash * word_find(dynamicstr* word);

#endif // !HASH_H
