#define _CRT_SECURE_NO_WARNINGS

#ifndef FILE_H

#define FILE_OPEN_ERROR -1
#define FILE_SAVE_SUCCESS 1

char * readwholefile(char* filename);
int  savestr(char* filename, char* buf);
#endif // !FILE_H
