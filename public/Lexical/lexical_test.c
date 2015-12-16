
#include <stdio.h>
#include <string.h>
#include"../file.h"
#include"lex_word_list.h"
#include "lex.h"

int main() {


	//printf("%s\n", buf);
	//int k = sizeof(XOP_list);
	////printf("%d", k);
	//for (int i = 0; i < k / 8; i++) {
	//	printf("0x%08x %s\n", XOP_list[i].tokencode, XOP_list[i].word);
	//}
	//k = sizeof(XBO_list);
	////printf("%d", k);
	//for (int i = 0; i < k / 8; i++) {
	//	printf("0x%08x %s\n", XBO_list[i].tokencode, XBO_list[i].word);
	//}
	char file[] = "e:\\Xin\\test\\helloworld.c.pre";
	char* buf = readwholefile(file);
	lexinit();
	for (int i = 0; i < MAXKEY; i++) {
		if (XHashTable[i].tokencode) {
			wordhash *tmp = XHashTable + i;
			while (tmp) {
				//printf("0x%08x 0x%08x %s\n", i, tmp->tokencode, tmp->word->str);
				tmp = tmp->next;
			}
		}
	}
	lexanalyse(buf);
	wordlist* tmp;

	printf("word find\n");
	tmp = LexResult->next;
	while (tmp != NULL) {
		printf("%s\t0x%08x\n ", tmp->hashkey->word->str,tmp->hashkey->tokencode);
		tmp = tmp->next;
	}

	printf("error find\n");
	tmp = LexError->next;
	while (tmp != NULL) {
		printf("%s\t0x%08x\n", tmp->hashkey->word->str, tmp->hashkey->tokencode);
		tmp = tmp->next;
	}
	return 0;
}