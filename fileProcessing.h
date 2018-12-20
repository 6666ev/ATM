#ifndef FILE_PROCESSING
#define FILE_PROCESSING
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#include<string.h>
#define FILE_NUMBER 4
struct key
{
	unsigned int n;
	unsigned int e;
	unsigned int d;
	char CodeFile[20];
};

int pow_mod(int a, int b, int c);

void CloseFiles(FILE* pCodeFile[], int n);

unsigned short EncryptChar(unsigned char i, int e, int n);
unsigned char DecryptChar(unsigned short i, int d, int n);
unsigned short Lock_1to2(unsigned char i, int mode);
unsigned char Unlock_2to1(unsigned short i, int mode);
void Lock(void* const dst, void* const src, int length, int mode);
void Unlock(void* const dst, void* const src, int length, int mode);
int Read();
int Write();
long GetFileLength(FILE* fp);
int Length_Equal(FILE* f_1, FILE* f_2);
int CheckTwoFile(FILE* f1, FILE* f2, int mode1, int mode2);
int Check();
void LockTest(int mode);
#endif // FILE_PROCESSING


