#define _CRT_SECURE_NO_WARNINGS

#include"pretreat.h"
#include<stdlib.h>
#include<string.h>

void pretreat(char* buf, int buflen) {
	int usefulchar = 0;
	char* tmp = (char*)malloc(buflen + 1);
	int flag = buflen;
	int backslashcount;

	memset(tmp, 0x00, buflen + 1);

	for (int i = 0; i < buflen&&buf[i] != 0;) {
		switch (buf[i]) {
		case '/':
			//删除单行注释
			if (buf[i + 1] == '/') {
				i += 2;
				while (buf[i]) {
					if (buf[i++] == '\n') {
						tmp[usefulchar++] = buf[i - 1];
						break;
					}
				}
			}
			//删除多行注释
			else if (buf[i + 1] == '*') {
				i += 2;
				while (buf[i]) {
					if (buf[i] == '\n') {
						tmp[usefulchar++] = '\n';
					}
					if (buf[i] == '*'&&buf[i + 1] == '/') {
						i += 2;
						break;
					}
					++i;
				}
			}
			else {
				tmp[usefulchar++] = buf[i++];
			}
			break;
		case '"':
			//单独处理双引号内部的字符串，防止字符串中的字符当成其他字符误处理
			tmp[usefulchar++] = buf[i++];
			backslashcount = 0;
			while (buf[i]) {
				if (buf[i] == '\\') {
					backslashcount++;
				}
				else if (buf[i] == '"') {
					if (backslashcount % 2 == 0) {
						tmp[usefulchar++] = buf[i];
						i++;
						break;
					}
					else {
						backslashcount = 0;
					}
				}
				else {
					backslashcount = 0;
				}
				tmp[usefulchar++] = buf[i];
				i++;
			}
			break;
			//单独处理单引号内部的字符串，防止字符串中的字符当成其他字符误处理
		case '\'':
			tmp[usefulchar++] = buf[i++];
			backslashcount = 0;
			while (buf[i]) {
				if (buf[i] == '\\') {
					backslashcount++;
				}
				else if (buf[i] == '\'') {
					if (backslashcount % 2 == 0) {
						tmp[usefulchar++] = buf[i];
						i++;
						break;
					}
					else {
						backslashcount = 0;
					}
				}
				else {
					backslashcount = 0;
				}
				tmp[usefulchar++] = buf[i];
				i++;
			}
			break;
			//连续多个空格只保留一个
			//\t 字符用空格代替
		case ' ':
		case '\t':
			if (usefulchar != 0) {
				if (tmp[usefulchar - 1] == ' ') {
					++i;
					break;
				}
			}
			tmp[usefulchar++] = ' ';
			++i;
			break;
		default:
			tmp[usefulchar++] = buf[i++];
			break;
		}
	}
	memset(buf, 0, buflen);
	strcpy(buf, tmp);
	free(tmp);
}