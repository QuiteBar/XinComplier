#include "lex.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


static wordlist* res_tmp;
static wordlist* err_tmp;

void lexinit() {
	int size;
	int i;
	dynamicstr* tmp;
	LexResult = (wordlist*)malloc(sizeof(wordlist));
	res_tmp = LexResult;
	res_tmp->next = NULL;

	LexError = (wordlist*)malloc(sizeof(wordlist));
	err_tmp = LexError;
	err_tmp->next = NULL;
	
	hashinit(XHashTable, MAXKEY);

	size = sizeof(XBO_list) / sizeof(key_word);
	for (i = 0; i < size; i++) {
		tmp = mkdynamicstr(XBO_list[i].word, strlen(XBO_list[i].word));
		word_insert(tmp, XBO_list[i].tokencode);
	}

	size = sizeof(XOP_list) / sizeof(key_word);
	for (i = 0; i < size; i++) {
		tmp = mkdynamicstr(XOP_list[i].word, strlen(XOP_list[i].word));
		word_insert(tmp, XOP_list[i].tokencode);
	}

	size = sizeof(XKEY_list) / sizeof(key_word);
	for (i = 0; i < size; i++) {
		tmp = mkdynamicstr(XKEY_list[i].word, strlen(XKEY_list[i].word));
		word_insert(tmp, XKEY_list[i].tokencode);
	}
}

void wordlist_insert(wordhash* hashkey,wordlist** into) {
	wordlist* tmp = (wordlist*)malloc(sizeof(wordlist));
	tmp->hashkey = hashkey;
	tmp->next = NULL;
	(*into)->next = tmp;
	(*into) = tmp;
}

analyseres* mkresnode(char* cp, int len, unsigned int token) {
	analyseres* tmpres = (analyseres*)malloc(sizeof(analyseres));
	dynamicstr* tmpds = mkdynamicstr(cp, len);
	tmpres->analysestr = tmpds;
	tmpres->analytoken = token;
	return tmpres;
}

int is_digital(char c) {
	if (c >= '0' && c <= '9')
		return 1;
	return 0;
}

int is_letter(char c) {
	if (c >= 'a'&&c <= 'z' || c >= 'A'&&c <= 'Z')
		return 1;
	return 0;
}

analyseres* dig_begin(char *cp) {
	analyseres* res = NULL;
	
	return res;
}

analyseres* letter_begin(char* cp) {
	analyseres* res = NULL;
	char* tmp = cp + 1;
	while (is_digital(*tmp) || is_letter(*tmp) || *tmp == '_')
		tmp++;
	dynamicstr* tmpds = mkdynamicstr(cp, tmp - cp );
	wordhash* tmpwh = word_find(tmpds);
	if (tmpwh != NULL) {
		res = mkresnode(cp, tmpds->len, tmpwh->tokencode);
	}
	else {
		res = mkresnode(cp, tmpds->len, XIDEN);
	}
	free(tmpds);
	return res;
}

analyseres* excal_begin(char* cp) {
	analyseres* res = NULL;
	if (*(cp + 1) == '=') {
		res = mkresnode(cp, 2, XOP_NEQ);
	}
	else {
		res = mkresnode(cp, 1, XOP_NOT);
	}
	return res;
}

analyseres* doublequo_begin(char* cp) {
	analyseres* res = NULL;
	char* tmp = cp + 1;
	int backslashcount = 0;
	while (*tmp != '\0') {
		if (*tmp == '\\') {
			backslashcount++;
		}
		else if (*tmp == '\"') {
			if (backslashcount % 2 == 0) {
				res = mkresnode(cp, tmp - cp + 1, XCON_STRING);
				break;
			}
			else {
				backslashcount = 0;
			}
		}
		else {
			backslashcount = 0;
		}
		tmp++;
	}
	return res;
}

analyseres* singlequo_begin(char* cp) {
	analyseres* res = NULL;
	char* tmp = cp + 1;
	int backslashcount = 0;
	while (*tmp!='\0') {
		if (*tmp == '\\') {
			backslashcount++;
		}
		else if (*tmp == '\'') {
			if (backslashcount % 2 == 0) {
				res = mkresnode(cp, tmp - cp + 1, XCON_CHAR);
				break;
			}
			else {
				backslashcount = 0;
			}
		}
		else {
			backslashcount = 0;
		}
		tmp++;
	}
	return res;
}

analyseres* add_begin(char* cp) {
	analyseres* res = NULL;
	if (*(cp + 1) == '+') {
		res = mkresnode(cp, 2, XOP_INC);
	}
	else if (is_digital(*(cp + 1))) {

	}
	else {
		res = mkresnode(cp, 1, XOP_PLUS);
	}
	return res;
}

analyseres* sub_begin(char* cp) {
	analyseres* res = NULL;
	if (*(cp + 1) == '-') {
		res = mkresnode(cp, 2, XOP_DEC);
	}
	else if (*(cp + 1) == '>') {
		res = mkresnode(cp, 2, XOP_POINTTO);
	}
	else if (is_digital(*(cp + 1))) {

	}
	else {
		res = mkresnode(cp, 1, XOP_MINUS);
	}
	return res;
}

analyseres* dot_begin(char* cp) {
	analyseres* res = NULL;
	if (*(cp + 1) != '.') {
		res = mkresnode(cp, 1, XOP_DOT);
	}
	else if (*(cp + 1) == '.'&&*(cp + 2) == '.') {
		res = mkresnode(cp, 3, XKEY_DOT3);
	}
	else {
		res = mkresnode(cp, 2, XLEX_ERROR);
	}
	return res;
}

analyseres* lt_begin(char* cp) {
	analyseres* res = NULL;
	if (*(cp + 1) == '<') {
		res = mkresnode(cp, 2, XOP_MOVEBITL);
	}
	else if(*(cp+1)=='=') {
		res = mkresnode(cp, 2, XOP_LEQ);
	}
	else {
		res = mkresnode(cp, 1, XOP_LT);
	}
	return res;
}

analyseres* gt_begin(char* cp) {
	analyseres* res = NULL;
	if (*(cp + 1) == '>') {
		res = mkresnode(cp, 2, XOP_MOVEBITR);
	}
	else if (*(cp + 1) == '=') {
		res = mkresnode(cp, 2, XOP_GEQ);
	}
	else {
		res = mkresnode(cp, 1, XOP_GT);
	}
	return res;
}

analyseres* assign_begin(char* cp) {
	analyseres* res = NULL;
	if (*(cp + 1) == '=') {
		res = mkresnode(cp, 2, XOP_EQ);
	}
	else {
		res = mkresnode(cp, 1, XOP_ASSIGN);
	}
	return res;
}

analyseres* error_begin(char* cp) {
	analyseres* res = NULL;
	return res;
}

dynamicstr* lexanalyse(char* str) {
	char * p = str;
	char c;
	analyseres * tmpres;
	dynamicstr * tmpds;
	wordhash * tmpwh;
	while ( *p != '\0') {
		c = *p;
		tmpres = NULL;
		switch (c) {
		case '0':case '1':case '2':case '3':case '4':case '5':
		case '6':case '7':case '8':case '9':
			tmpres = dig_begin(p);
			break;
		case 'a':case 'b':case 'c':case 'd':case 'e':case 'f':
		case 'g':case 'h':case 'i':case 'j':case 'k':case 'l':
		case 'm':case 'n':case 'o':case 'p':case 'q':case 'r':
		case 's':case 't':case 'u':case 'v':case 'w':case 'x':
		case 'y':case 'z':
		case 'A':case 'B':case 'C':case 'D':case 'E':case 'F':
		case 'G':case 'H':case 'I':case 'J':case 'K':case 'L':
		case 'M':case 'N':case 'O':case 'P':case 'Q':case 'R':
		case 'S':case 'T':case 'U':case 'V':case 'W':case 'X':
		case 'Y':case 'Z':
		case '_':
			tmpres = letter_begin(p);
			break;
		case '!':
			tmpres = excal_begin(p);
			break;
		case '"':
			tmpres = doublequo_begin(p);
			break;
		case '\'':
			tmpres = singlequo_begin(p);
			break;
		case '#':
			tmpres = mkresnode(p, 1, XBO_POUND);
			break;
		case '%':
			tmpres = mkresnode(p, 1, XOP_MOD);
			break;
		case '&':
			tmpres = mkresnode(p, 1, XOP_AND);
			break;
		case '^':
			tmpres = mkresnode(p, 1, XOP_XOR);
			break;
		case '|':
			tmpres = mkresnode(p, 1, XOP_OR);
			break;
		case '~':
			tmpres = mkresnode(p, 1, XOP_NOTBIT);
			break;
		case '(':
			tmpres = mkresnode(p, 1, XBO_OPENPA);
			break;
		case ')':
			tmpres = mkresnode(p, 1, XBO_CLOSEPA);
			break;
		case '*':
			tmpres = mkresnode(p, 1, XOP_STAR);
			break;
		case '+':
			tmpres = add_begin(p);
			break;
		case ',':
			tmpres = mkresnode(p, 1, XBO_COMMA);
			break;
		case '-':
			tmpres = sub_begin(p);
			break;
		case '.':
			tmpres = dot_begin(p);
			break;
		case '/':
			tmpres = mkresnode(p, 1, XOP_DIVIDE);
			break;
		case ':':
			tmpres = mkresnode(p, 1, XBO_COLON);
			break;
		case ';':
			tmpres = mkresnode(p, 1, XBO_SEMICOLON);
			break;
		case '<':
			tmpres = lt_begin(p);
			break;
		case '=':
			tmpres = assign_begin(p);
			break;
		case '>':
			tmpres = gt_begin(p);
			break;
		case '?':
			tmpres = mkresnode(p, 1, XOP_YES);
			break;
		case '[':
			tmpres = mkresnode(p, 1, XBO_OPENBR);
			break;
		case ']':
			tmpres = mkresnode(p, 1, XBO_CLOSEBR);
			break;
		case '{':
			tmpres = mkresnode(p, 1, XBO_BEGIN);
			break;
		case '}':
			tmpres = mkresnode(p, 1, XBO_END);
			break;
		case ' ':case'\t':case ' \r':case '\n':
			p += 1;
			continue;
		default:
			tmpres = error_begin(p);
			break;
		}
		if (tmpres != NULL) {
			//printf("%s\t:0x%08x\n", tmpres->analysestr->str, tmpres->analytoken);
			tmpwh = word_insert(tmpres->analysestr, tmpres->analytoken);
			if (tmpres->analytoken != XLEX_ERROR) {
				wordlist_insert(tmpwh, &res_tmp);
			}
			else {
				wordlist_insert(tmpwh, &err_tmp);
			}
			p += tmpres->analysestr->len;
		}
		else {
			p += 1;
		}
	}
}
