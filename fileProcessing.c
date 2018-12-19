#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#include<string.h>
#include"fileProcessing.h"
#include "User.h"
extern struct user user[];
extern int userNum;
const struct key keys[FILE_NUMBER] = {
	{ 267,17,145,"b1.bin" },{ 335,5,53,"b2.bin" },
{ 341,7,43,"b3.bin" },{ 301,11,23,"b4.bin" }
};
//参考：http://www.ruanyifeng.com/blog/2013/07/rsa_algorithm_part_two.html
//unsigned int p[FILE_NUMBER] = { 3,5,11,7 };
//unsigned int q[FILE_NUMBER] = { 89,67,31,43 };
//unsigned int y[FILE_NUMBER] = { 176,264,300,252 };
//const unsigned int n[FILE_NUMBER] = { 267,335,341,301 };
//const unsigned int e[FILE_NUMBER] = { 17,5,7,11 };
//const unsigned int d[FILE_NUMBER] = { 145,53,43,23 };
//char CodeFile[FILE_NUMBER][20] = { "b1.bin","b2.bin" ,"b3.bin" ,"b4.bin" };

/*以下函数都只是为了求公钥和私钥，我已经求好了放到数组里面所以已经不需要了
//函数功能:递归求解最大公约数
//传入参数：两数a,b
//返回值：最大公约数
//创建时间：2018/11/18 14:45
//创建人：钟彤卓
//最后一次修改时间：2018/11/18 14:45
//其他注意事项：
int gcd(int a, int b)
{
	if (b == 0) { return a; }
	else { return gcd(b, a%b); }
}
int exgcd(int a, int b, int* x, int* y)
{
	if (b == 0)
	{
		*x = 1;
		*y = 0;
		return a;
	}
	int r = exgcd(b, a%b, x, y);
	int t = *y;
	*y = *x - (a / b)*(*y);
	*x = t;
	return r;
}
//函数功能:辗转相除法求模反函数
//传入参数：ax+by=1中的a,b。其中a,b一定要大于0
//返回值：x,x＜0时会被加到大于零为止。因为在求模反函数中我们不关心y,
//创建时间：2018/11/18 14:33
//创建人：钟彤卓
//最后一次修改时间：2018/11/18 14:33
//其他注意事项：方程求解：http://blog.sina.com.cn/s/blog_6527c0ca0102wd5q.html
int EuclideanAlgorithm(int a, int b)
{
	int x, y;
	//
	//int cd = gcd(a, b);
	//if (c%cd == 0){}
	//由于c=1,这里不再进行判断,也就是二元一次方程组一定有解
	exgcd(a, b, &x, &y);
	while (x < 0)
		x = x + b;
	return x;
}
*/

/*
//函数功能:通过数论知识得到的一种不用超高位也能进行指数幂+mod运算的函数
//传入参数：底数a,指数b,modc
//返回值：返回值=a^b % c
//创建时间：2018/11/18 20:53
//创建人：钟彤卓
//最后一次修改时间：2018/11/18 20:53
//其他注意事项：参考资料：https://blog.csdn.net/ghevinn/article/details/12561987
*/
int pow_mod(int a, int b, int c)
{
	int r = 1;
	b = b + 1;
	while (b != 1)
	{
		r = r * a;
		r = r % c;
		b--;
	}
	return r;
}

/*
//函数功能：关闭前n+1个文件
//传入参数：文件指针数组和关闭的文件数目
//返回值：无
//创建时间 2018/12/6 23：00
//创建人：钟彤卓
//最后一次修改时间：
//其他注意事项：
*/
void CloseFiles(FILE* pCodeFile[], int n)
{
	for (int i = 0; i <= n; i++)
		fclose(pCodeFile[i]);
}

/*
//函数功能：加密一字节为两字节
//传入参数：char的类型一字节数据,公钥n，e或私钥n，d
//返回值：加密后的short两字节数据
//创建时间：2018/11/18 21:36
//创建人：钟彤卓
//最后一次修改时间：2018/11/20 16:45
//其他注意事项：被“封装”于LockByByte内
*/
unsigned short EncryptChar(unsigned char i, int e, int n)
{
	int r = 1;
	e = e + 1;
	while (e != 1)
	{
		r = r * i;
		r = r % n;
		e--;
	}
	return r;
	//return pow_mod(i, e, n);
}
/*
//函数功能：解密两字节为一字节
//传入参数：short类型两字节数据,公钥n，e或私钥n，d
//返回值：解密后的char一字节数据
//创建时间：2018/11/18 21:36
//创建人：钟彤卓
//最后一次修改时间：2018/11/20 16:45
//其他注意事项：被封装与UnLockByByte内
*/
unsigned char DecryptChar(unsigned short i, int d, int n)
{
	int r = 1;
	d = d + 1;
	while (d != 1)
	{
		r = r * i;
		r = r % n;
		d--;
	}
	return r;
	//return pow_mod(i, d, n);
}

/*
//函数功能：对Encrypt和Decrypt的调用接口修正，现在只需要传入元素和加密模式即可
//传入参数：读取的位置,一个void指针
//返回值：读取到的字节，以unsigned char表示
//创建时间：2018/11/19 13：05
//创建人：钟彤卓
//最后一次修改时间：2018/12/6 23：08
//其他注意事项：
*/
unsigned short Lock_1to2(unsigned char i, int mode)
{
	return EncryptChar(i, keys[mode].e, keys[mode].n);
	//return EncryptChar(i, e[mode], n[mode]);
}
unsigned char Unlock_2to1(unsigned short i, int mode)
{
	return DecryptChar(i, keys[mode].d, keys[mode].n);
	//return DecryptChar(i, d[mode], e[mode]);
}

/*
//函数功能：对指定内存按字节加密为两字节
//传入参数: 加密目的位置指针、加密源头位置指针、加密的长度、加密模式
//返回值：无
//创建时间：2018/11/18 13：22
//创建人：钟彤卓
//最后一次修改时间：2018/11/20 17:01
//其他注意事项：
*/
void Lock(void* const dst, void* const src, int length, int mode)
{
	unsigned char* cur_s;
	unsigned short* cur_d;
	cur_s = (unsigned char*)src;
	cur_d = (unsigned short*)dst;
	for (int i = 0; i < length; i++)
	{
		*cur_d = Lock_1to2(*cur_s, mode);
		cur_s++;
		cur_d++;
	}
}
/*
//函数功能：对指定内存解密
//传入参数: 解密的内存位置，解密长度，解密模式
//返回值：无
//创建时间：2018/11/18 23：44
//创建人：钟彤卓
//最后一次修改时间：2018/11/20 17：04
//其他注意事项：在Read中被调用
*/
void Unlock(void* const dst, void* const src, int length, int mode)
{
	unsigned short* cur_s;
	unsigned char* cur_d;
	cur_s = (unsigned short*)src;
	cur_d = (unsigned char*)dst;
	for (int i = 0; i < length/2; i++)
	{
		*cur_d = Unlock_2to1(*cur_s, mode);
		cur_s++;
		cur_d++;
	}
}

/*
//函数功能：对文件解密并且将信息存在用户数组各个元素
//传入参数: 解密的文件名和解密的
//返回值：返回用户的数量
//创建时间：2018/11/18 13：22
//创建人：钟彤卓
//最后一次修改时间：2018/11/20 17:17
//其他注意事项：Check和Lock是不分开的，在ATM程序中，每次操作都必须先Check
//如果我在处理的过程中文件被修改了怎么办……好像没有办法?
*/
int Read()
{
	//system("cls");
	int mode = Check();
	if (mode == -1)
	{
		printf("Invalid files!");
		getchar();
		exit(-1);
	}
	//system("cls");
	int count = 0;
	FILE* fp = fopen(keys[mode].CodeFile, "rb");
	int unlock_size = sizeof(struct user) * 2;//从文件中读取两倍长度的内容到内存中
	int copy_size = sizeof(struct user);//实际一个结构体变量的长度
	void* copy_buffer = malloc(copy_size);
	void* unlock_buffer = malloc(unlock_size);
	while (fread(unlock_buffer, unlock_size, 1, fp))
		//之前已经保证了文件大小是sizeof struct的整数倍，而且我们不考虑
		//在处理过程中文件被修改的情况。因此只要fread失败了就认为文件读
		//完了
	{
		Unlock(copy_buffer, unlock_buffer, unlock_size, mode);
		user[count] = *((struct user*)copy_buffer);
//		system("cls");
		//我****到底为什么malloc会失败？ 11/20 17:30
		//我****为什么成功了？？？ 11/20 21：22
		//遇到bug别紧张，烧给佛祖一炷香。心平气和敲代码，早日坐上头等舱(误)。11.22/15：50
		//copy_buffer = (struct user *)malloc(copy_size);
		//大家好，我又遇到bug了，而且好像是一样的问题呢  12/19 19：53
		count++;
	}
//	system("cls");
	free((struct user*)copy_buffer);
	copy_buffer = NULL;
	fclose(fp);
	return count;
};
int Write()
{
	FILE* pCodeFile[FILE_NUMBER];
	int flag = 1;
	int i = 0;
	for (i = 0; i < FILE_NUMBER; i++)
	{
		pCodeFile[i] = fopen(keys[i].CodeFile, "wb");
		if (pCodeFile[i] == NULL)
		{
			flag = 0;
			printf("error:open file failed");
			system("pause");
			exit(0);
			break;
		}
	}
	if (flag == 1)
	{
		int copy_size = sizeof(struct user);
		int lock_size = sizeof(struct user) * 2;
		struct user* copy_buffer = malloc(copy_size);//将每个账户拷贝到buffer内，避免用户资料被修改
		void *lock_buffer = malloc(lock_size);//被加密后的内容储存位置
		for (i = 0; i < userNum; i++)//对于每个账户
		{
			*copy_buffer = user[i];
			for (int j = 0; j < FILE_NUMBER; j++)//对于不同加密模式
			{
				Lock(lock_buffer, copy_buffer, copy_size, j);
				fwrite(lock_buffer, lock_size, 1, pCodeFile[j]);
			}
		}
	}
	CloseFiles(pCodeFile, FILE_NUMBER - 1);
	return flag;
}


/*
//函数功能：获取二进制文件长度
//传入参数：文件指针
//返回值：unsigned long类型的文件长度，不检查文件指针对象是否存在。
//创建时间：2018/11/19 10:29
//创建人：钟彤卓
//最后一次修改时间：2018/11/19 23:00
//其他注意事项：
*/
long GetFileLength(FILE* fp)
{
	long beg, end;
	fseek(fp, 0, SEEK_SET);
	beg = ftell(fp);
	fseek(fp, 0, SEEK_END);
	end = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	return end - beg;
}

/*
//函数功能：对检查文件长度是否相同
//传入参数：比较的文件指针,不检查文件是否存在
//返回值：0：长度不同 1：长度相同
//创建时间：2018/11/19 10:29
//创建人：钟彤卓
//最后一次修改时间：2018/11/19 11:05
//其他注意事项：
*/
int Length_Equal(FILE* f_1, FILE* f_2)
{
	return GetFileLength(f_1) == GetFileLength(f_2) ? 1 : 0;
}
/*
//函数功能:对两个文件按照特定模式以两个字节为单位进行解密，然后匹配是否相同
//传入参数：解密的文件指针和对应模式
//返回值：1代表文件匹配，0代表文件不匹配
//创建时间：2018/11/22 11：52
//创建人：钟彤卓
//最后一次修改时间：2018/11/2 11:52
//其他注意事项：
*/
int CheckTwoFile(FILE* f1, FILE* f2, int mode1, int mode2)
{
	static unsigned short c1, c2;
	static int flag;
	flag = 1;
	do
	{
		fread(&c1, sizeof(c1), 1, f1);
		fread(&c2, sizeof(c2), 1, f2);
		if (Unlock_2to1(c1, mode1) != Unlock_2to1(c2, mode2))
		{
			flag = 0;
			break;
		}
	} while (feof(f1) == 0 && feof(f2) == 0);
	//循环结束，代表两者至少有一个为1，也就是未结束
	//接下来检查是不是两者都结束，也就是都为1，如果
	//不是则代表文件不等长。两者合取1的反也就是两者
	//析取0
	if (feof(f1) == 0 || feof(f2) == 0)
		flag = 0;
	fseek(f1, 0, SEEK_SET);
	fseek(f2, 0, SEEK_SET);
	return flag;
}
/*
//函数功能:检查文件是否被篡改
//传入参数：无
//返回值：-1代表文件被修改，其他数字代表某个合法的文件序号（mode）
//创建时间：2018/11/22 11：52
//创建人：钟彤卓
//最后一次修改时间：2018/11/2 11:52
//其他注意事项：我觉得代码的通用性不好，只适用于四个的情况，但是缺乏相关算法知识暂时没有改进的思路。
*/
int Check()
{
	static int i, j;
	static FILE* pCodeFile[FILE_NUMBER];

	static unsigned int Length[FILE_NUMBER];
	static int count;//用来记录有多少个组不合法
	count = 0;
	//记录哪条路线不合法,i到（i+1）%FILE_NUMER的路线被记为i
	static unsigned int LegalPath[FILE_NUMBER];
	for (i = 0; i < FILE_NUMBER; i++)
		LegalPath[i] = 1;

	//todo 如果在根本没有文件的情况下，这里也会报错，更好的办法是直接创建文件。
	//先检查文件能否打开
	for (i = 0; i < FILE_NUMBER; i++)
	{
		if ((pCodeFile[i] = fopen(keys[i].CodeFile, "rb")) == NULL)
		{
			CloseFiles(pCodeFile, i);
			return -1;
		}
	}
	//检查文件长度是否合法
	for (i = 0; i < FILE_NUMBER; i++)
		if ((Length[i] = GetFileLength(pCodeFile[i])) % (2 * sizeof(struct user)) != 0)
		{
			CloseFiles(pCodeFile, 3);
			return -1;
		}
	//文件长度不一致，退出
	for (i = 0; i < FILE_NUMBER-1; i++)
	{
		if (Length[i] != Length[i + 1])
		{
			CloseFiles(pCodeFile, 3);
			return -1;
		}
	}

	//对环形路线进行检查
	for (i = 0; i<FILE_NUMBER; i++)
		if (CheckTwoFile(pCodeFile[i], pCodeFile[(i + 1) % FILE_NUMBER], i, (i + 1) % FILE_NUMBER) == 0)
		{
			count++;
			LegalPath[i] = 0;
		}

	static flag;
	if (count == 0)
		flag = 0;//如果没错，返回哪个都可以，这里返回第0个
	else if (count == 2)
	{
		if (LegalPath[0] == 0 && LegalPath[1] == 0)
			flag = 2;
		else if (LegalPath[1] == 0 && LegalPath[2] == 0)
			flag = 3;
		else if (LegalPath[2] == 0 && LegalPath[3] == 0)
			flag = 0;
		else if (LegalPath[3] == 0 && LegalPath[0] == 0)
			flag = 1;
		else
			flag = -1;
	}
	else// else if (count == 1||count==3||count==4)
		//奇数个不匹配是不可能的，出现这种情况代表文件在检测期间被修改了。
		//四个都不一样代表文件已经被毁了
		flag = -1;
	CloseFiles(pCodeFile, 3);
	return flag;
}
void LockTest(int mode)
{
	unsigned char c = 0;
	unsigned short d = 0;
	unsigned char e = 0;
	int count = 0;
	printf("\n");
	for (c = 0; c < 255; c++)
	{
		d = Lock_1to2(c, mode);
		e = Unlock_2to1(d, mode);

		printf("原文:%d", c);
		printf("加密：%d", d);
		printf("解密：%d", e);
		if (c != e) printf("\n…………");
		printf("\n");
		//count++;
	}
	printf("\n");
	//printf("不合法%d", count);
}