#ifndef LEX_H
#define LEX_H

#include "hash.h"
#include "lex_word_list.h"
#include "xin_structs.h"

wordlist* LexResult;
errorlist* LexError;

void lexinit();
void lexanalyse(char* str);
#endif // !LEX_H
