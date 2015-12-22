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
			//ɾ������ע��
			if (buf[i + 1] == '/') {
				i += 2;
				while (buf[i]) {
					if (buf[i++] == '\n') {
						tmp[usefulchar++] = buf[i - 1];
						break;
					}
				}
			}
			//ɾ������ע��
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
			//��������˫�����ڲ����ַ�������ֹ�ַ����е��ַ����������ַ�����
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
			//�������������ڲ����ַ�������ֹ�ַ����е��ַ����������ַ�����
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
			//��������ո�ֻ����һ��
			//\t �ַ��ÿո����
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