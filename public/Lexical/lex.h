#ifndef LEX_H
#define LEX_H

#include "hash.h"
#include "lex_word_list.h"
#include "xin_structs.h"

wordlist* LexResult;
wordlist* LexError;

void lexinit();
dynamicstr* lexanalyse(char* str);
#endif // !LEX_H
