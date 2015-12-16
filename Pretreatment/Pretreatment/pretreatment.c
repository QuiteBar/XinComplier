/*
	date:2015-11-19
	Pretreatment, before Lexical analysis
*/

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define FILE_OPEN_ERROR -1
#define FILE_SAVE_SUCCESS 1

/*
*����Ԥ�������
*	ɾ�������е�\r ,\n ,\t ����Ŀո�ע�Ͳ��ֵȷ���ʷ����� 
*		buf ����
*		buflen ��������С
*/
void preteatment(char* buf, int buflen){
	int usefulchar = 0;
	char* tmp = (char*)malloc(buflen + 1);
	int flag = buflen;
	int backslashcount;

	memset(tmp, 0x00, buflen+1);

	for (int i = 0; i < buflen&&buf[i] != 0;){
		switch (buf[i]){
		case '/':
			//ɾ������ע��
			if (buf[i + 1] == '/'){
				i += 2;
				while (buf[i]){
					if (buf[i++] == '\n'){
						break;
					}
				}
			}
			//ɾ������ע��
			else if (buf[i + 1] == '*'){
				i += 2;
				while (buf[i]){
					if (buf[i] == '*'&&buf[i + 1] == '/'){
						i += 2;
						break;
					}
					++i;
				}
			}
			else{
				tmp[usefulchar++] = buf[i++];
			}
			break;
		case '"':
			//��������˫�����ڲ����ַ�������ֹ�ַ����е��ַ����������ַ�����
			tmp[usefulchar++] = buf[i++];
			backslashcount = 0;
			while (buf[i]){
				if (buf[i] == '\\'){
					backslashcount++;
				}
				else if(buf[i]=='"'){
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
			if (usefulchar != 0){
				if (tmp[usefulchar-1] == ' '){
					++i;
					break;
				}
			}
			tmp[usefulchar++] = ' ';
			++i;
			break;
			//ɾ��\r \t �ַ�
//		case '\r':
//		case '\n':
//			++i;
//			break;
		default:
			tmp[usefulchar++] = buf[i++];
			break;
		}
	}
	memset(buf, 0, buflen);
	strcpy(buf, tmp);
	free(tmp);
}

/*
	���������ļ������ش洢�ļ����ݵĻ�����ָ��
	filename ��ȡ���ļ���
*/
char * readwholefile(char* filename){
	FILE* fp;
	char* buf=NULL;
	int size=0;
	fp = fopen(filename, "r");
	if (!fp){
		return buf;
	}

	fseek(fp, 0, SEEK_END);
	size = ftell(fp);

	fseek(fp, 0, SEEK_SET);
	buf = (char*)malloc(size + 1);
	memset(buf, 0x00, size + 1);
	fread(buf, size, 1, fp);
	fclose(fp);
	return buf;
}

/*
����Ԥ������
savefilename ���������ļ���
buf	Ԥ������������
*/
int savepreresult(char* savefilename, char* buf){
	FILE* fp = fopen(savefilename, "w");
	if (!fp){
		return FILE_OPEN_ERROR;
	}
	int buflen = strlen(buf);
	fwrite(buf, buflen, 1, fp);
	fclose(fp);
	return FILE_SAVE_SUCCESS;
}

int main(){
	char file[] = "e:\\Xin\\test\\helloworld.c";
	//char file[] = "e:\\Xin\\test\\stdio.h";
	//char file[] = "e:\\Xin\\test\\1.txt";
	char savefile[256] = {0};
	char* buf;
	buf = readwholefile(file);
	if (!buf){
		printf("file read error!");
	}
	else{
		printf("%s\n", buf);
		preteatment(buf, strlen(buf));
		printf("%s\n", buf);
		strcpy(savefile, file);
		strcat(savefile, ".pre");
		savepreresult(savefile, buf);
		free(buf);
	}
	return 0;
}
