#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

dynamicstr* mkdynamicstr(char* str, int len) {
	dynamicstr* ds = (dynamicstr*)malloc(sizeof(dynamicstr));
	char* strtocopy = (char*)malloc(len + 1);
	memset(strtocopy, 0, len + 1);
	memcpy(strtocopy, str, len);
	ds->len = len;
	ds->str = strtocopy;
	return ds;
}

// BKDR Hash Function
// BKDR Hash is a good hash function in get the string's hash key
unsigned int BKDRHash(dynamicstr *str) {
	unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
	unsigned int hash = 0;
	
	for (int i = 0; i < str->len;i++) {
		hash = hash * seed + str->str[i];
	}

	return (hash & 0x7FFFFFFF) % MAXKEY;	//mod MAXKEY meams make it put into the hash table
}

//initialize hash table
void hashinit(wordhash* hashtable, int hashtablelen) {
	int i = 0;
	for (i = 0; i < hashtablelen; i++) {
		hashtable[i].next = NULL;
		hashtable[i].tokencode = 0;
		hashtable[i].word = NULL;
	}
}

//insert word into hash table
wordhash * word_insert(dynamicstr* word, unsigned int tokencode) {
	unsigned int hash;
	wordhash* tmp, *p;
	
	tmp = word_find(word);
	if (tmp != NULL) {
		return  tmp;
	}

	hash = BKDRHash(word);
	tmp = XHashTable + hash;
	
	if (tmp->tokencode == 0) {
		tmp->next = NULL;
		tmp->tokencode = tokencode;
		tmp->word = word;
	}
	else {
		while (tmp->next != NULL) tmp = tmp->next;
		p = (wordhash*)malloc(sizeof(wordhash));
		p->next = NULL;
		p->tokencode = tokencode;
		p->word = word;
		tmp = p;
	}
	return tmp;
}

//find word from hash table and return the hash table index
wordhash * word_find(dynamicstr * word) {
	unsigned int hash;
	wordhash *tmp;
	hash = BKDRHash(word);
	tmp = XHashTable+hash;

	if (tmp->word == NULL) {
		return NULL;
	}

	while (tmp != NULL) {

		if (!strcmp(word->str, tmp->word->str)) {
			return tmp;
		}
		tmp = tmp->next;
	}
	return NULL;
}