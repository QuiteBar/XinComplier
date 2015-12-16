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
*代码预处理程序
*	删除代码中的\r ,\n ,\t 多余的空格，注释部分等方便词法分析 
*		buf 缓冲
*		buflen 缓冲区大小
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
			//删除单行注释
			if (buf[i + 1] == '/'){
				i += 2;
				while (buf[i]){
					if (buf[i++] == '\n'){
						break;
					}
				}
			}
			//删除多行注释
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
			//单独处理双引号内部的字符串，防止字符串中的字符当成其他字符误处理
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
			if (usefulchar != 0){
				if (tmp[usefulchar-1] == ' '){
					++i;
					break;
				}
			}
			tmp[usefulchar++] = ' ';
			++i;
			break;
			//删除\r \t 字符
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
	读入整个文件，返回存储文件内容的缓冲区指针
	filename 读取的文件名
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
保存预处理结果
savefilename 保存结果的文件名
buf	预处理结果缓冲区
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
