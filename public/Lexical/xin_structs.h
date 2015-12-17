#ifndef XIN_STRUCTS_H
#define XIN_STRUCTS_H

typedef struct dynamicstr {
	int len;
	char* str;
} dynamicstr;

typedef struct key_word {
	unsigned int tokencode;
	char * word;
}key_word;

typedef struct wordhash {
	unsigned int tokencode;
	struct wordhash * next;
	dynamicstr *word;
}wordhash;

typedef struct wordlist {
	wordhash* hashkey;
	struct wordlist *next;
}wordlist;

typedef struct analyseres {
	dynamicstr* analysestr;
	int analytoken;
}analyseres;

typedef struct errorlist {
	wordhash* hashkey;
	int linenum;
	struct errorlist* next;
}errorlist;

#endif //XIN_STRUCTS_H
