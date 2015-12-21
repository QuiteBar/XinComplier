#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include"../file.h"
#include"lex_word_list.h"
#include "lex.h"
#include "pretreat.h"
#include<Windows.h>

void colorwords(wordlist* list) {
	int token;
	HANDLE hd = GetStdHandle(STD_OUTPUT_HANDLE);
	
	while (list != NULL) {
		token = list->hashkey->tokencode;
		token = token >> 28;
		switch (token) {
		case 0:
			SetConsoleTextAttribute(hd, FOREGROUND_GREEN);
			break;
		case 1:
			SetConsoleTextAttribute(hd, FOREGROUND_RED);
			break;
		case 2:
			SetConsoleTextAttribute(hd, FOREGROUND_RED | FOREGROUND_GREEN);
			break;
		case 3:
			SetConsoleTextAttribute(hd, FOREGROUND_RED | FOREGROUND_BLUE);
			break;
		case 4:
			SetConsoleTextAttribute(hd, FOREGROUND_BLUE | FOREGROUND_GREEN);
			break;
		default:
			SetConsoleTextAttribute(hd, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			break;
		}
		printf("%s ", list->hashkey->word->str);
		list = list->next;
	}
	printf("\n");
	SetConsoleTextAttribute(hd, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}


int main(int argc,char* argv[]) {

	//char file[] = "e:\\XinComplier\\test\\helloworld.c";
	//char file[256];
	//memset(file,0,256);
	//scanf("%s", file);
	if (argc != 2) {
		return 0;
	}
	char* buf = readwholefile(argv[1]);
	if (buf == NULL) {
		printf("file read error!");
		return 0;
	}
	pretreat(buf, strlen(buf));
	lexinit();
	lexanalyse(buf);
	wordlist* tmp;

	printf("Lexical Result\n");
	tmp = LexResult->next;
	while (tmp != NULL) {
		if (tmp->hashkey->tokencode == XBO_NEWLINE) {
			tmp = tmp->next;
			continue;
		}
		printf("0x%08x\t%s\n", tmp->hashkey->tokencode, tmp->hashkey->word->str);
		tmp = tmp->next;
	}
	tmp = LexResult->next;
	colorwords(tmp);

	errorlist* tmperr = LexError->next;
	if (tmperr != NULL) {
		printf("error find\n");
	}
	while (tmperr != NULL) {
		printf("line:%d\t%s\n", tmperr->linenum, tmperr->hashkey->word->str);
		tmperr = tmperr->next;
	}
	return 0;
}