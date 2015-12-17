#include<stdio.h>
#include<Windows.h>

int main() {
	HANDLE hd = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hd, FOREGROUND_BLUE);
	printf("1342");
	system("pause");
	return 0;
}