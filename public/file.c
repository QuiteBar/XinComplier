#include"file.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

/*
读入整个文件，返回存储文件内容的缓冲区指针
filename 读取的文件名
*/
char * readwholefile(char* filename) {
	FILE* fp;
	char* buf = NULL;
	int size = 0;
	fp = fopen(filename, "r");
	if (!fp) {
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
保存字符串
savefilename 保存结果的文件名
buf	字符串缓冲区
*/
int savestr(char* savefilename, char* buf) {
	FILE* fp = fopen(savefilename, "w");
	if (!fp) {
		return FILE_OPEN_ERROR;
	}
	int buflen = strlen(buf);
	fwrite(buf, buflen, 1, fp);
	fclose(fp);
	return FILE_SAVE_SUCCESS;
}