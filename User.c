#include "User.h"
#ifdef _MSC_VER
	#define getch _getch
#endif
void flush()
{
#ifdef _MSC_VER
	getchar();
#else
	flush();
#endif 
}
int A = 0; //表示用户数量
void aboutFile()
{
	FILE *fp = fopen("userinfo.txt", "r");
	if (fp == NULL)
	{
		printf("user file doesn't exist, building");
		FILE *fp = fopen("userinfo.txt", "w");
		fclose(fp);
	}
	else
	{
		fclose(fp);
	}
}
void date()
{
	printf("current date");
	printf("\t");
	system("date/t");
	printf("\n");
	printf("current time");
	printf("\t");
	system("time/t");
}
void userInterface()
{
	system("cls");
	int a;
	date();
	FILE *fy = fopen("userinfo.txt", "r");
	if (!fy)
	{
		printf("fail to read file\n");
	}
	printf("\n\n\n\n\t\t\t*******please choose your entrance*******");
	printf("\n\n\t\t\t1.log on\n\n\t\t\t2.sign up\n\n\t\t\t3.report for lost\n\n\t\t\t4.exit\n");
	printf("\n\n\t\t\tplease input your choice:");
	flush();
	scanf("%d", &a);
	switch (a)
	{
		case 1:
			logIn();
			break;
		case 2:
			signIn();
			break;
		case 3:
			missAccount();
		case 4:
			exit(0);
	}
}
void logIn()
{
	system("cls");
	FILE *fp = fopen("userinfo.txt", "r");
	date();
	if (!fp)
	{
		printf("fail to open file");
	}
	int i, n, index;
	int j = 0, k = 3;
	for (i = 0; i <= 100; i++)
	{
		fscanf(fp, "%s\t%s\t%s\n", u[i].acnum, u[i].pswdnum, u[i].name);
	}
	fclose(fp);
	printf("\n\n\t\tplease input your right account:");
	scanf("%s", ac);
	for (i = 0; i <= 100; i++)
	{
		if (strcmp(u[i].acnum, ac) == 0)
		{
			if (u[i].ero == 1)
			{
				printf("\n\n\t\tthis card is reported missing");
				getchar();
				getchar();
				userInterface();
			}
			else
				break;
		}
	}
	for (index = 0; index <= 100; index++)
		if (strcmp(u[index].acnum, ac) == 0)
			j++;
	while (j == 0)
	{
		printf("\n\n\t\tthis account doesn't exist or being signed off, \n\t\tplease sign up and log on (input Enter to return)");
		getchar();
		getchar();
		userInterface();
	}
L:
	printf("\n\t\tplease input your password:");
	scanf("%s", pass);
	n = strcmp(u[i].pswdnum, pass);
	if (n != 0 && k != 0)
	{
		k--;
		printf("\n\n\t\twrong password, there are %d chances left", k);
		getch();
		flush();
		goto L;
	}
	else if (n != 0 && k == 0)
	{
		printf("\n\n\t\tyou have run out of chances\n");
		getch();
		userInterface();
	}
	else if (k != 0)
	{
		printf("\n\n\t\tlog on successful");
		printf("\n\n\t\tinput any key to continue->");
		getch();
		userOperate(i);
	}
}

void signIn()
{
	system("cls");
	FILE *op, *fp;
	int i, index;
	int j = 0;
	char ac[10];
	fp = fopen("userinfo.txt", "r");
	for (i = 0; i <= 100; i++)
	{
		fscanf(fp, "%s\t%s\t%s\n", u[i].acnum, u[i].pswdnum, u[i].name);
	}
	fclose(fp);
	op = fopen("userinfo.txt", "a+");
	date();

	if (!op)
	{
		printf("fail to open file");
	}
	flush();
	printf("\n\n\t\tplease input your account(less than 9 letter):");
	gets(ac);
	for (index = 0; index <= 100; index++)
		if (strcmp(u[index].acnum, ac) == 0)
			j++;
	while (j != 0)
	{
		printf("\n\t\tthis account has been signed up, try again please!(input Enter to return)");
		getchar();
		userInterface();
	}
	strcpy(u[A].acnum, ac);
	printf("\n\t\tplease input your password(less than 6 letter):");
	gets(u[A].pswdnum);
	printf("\n\t\tplease input your name:");
	gets(u[A].name);

	printf("\n\t\tprestored money:");
	scanf("%lf", &u[A].money);
	u[A].ero = 0;
	fprintf(op, "%s\t%s\t%s\n", u[A].acnum, u[A].pswdnum, u[A].name);
	A++;
	fclose(op);
	printf("\n\n\t\treturn to last page, input random key to continue->");
	getch();
	userInterface();
}
void missAccount()
{
	system("cls");
	int i, j, k;
	date();
	FILE *fy = fopen("userinfo.txt", "r");

	if (!fy)
	{
		printf("fail to create file\n");
	}
	for (i = 0; i <= 100; i++)
	{
		fscanf(fy, "%s\t%s\t%s\t%lf\t%d\n", u[i].acnum, u[i].pswdnum, u[i].name, &u[i].money, &u[i].ero);
	}
	fclose(fy);
	do
	{
		printf("\n\n\t\tplease input your right account to be reported missing");
		scanf("%s", ac);
		putchar('\n');
		printf("\t\tinput your password:");
		scanf("%s", pass);
		for (i = 0; i <= 100; i++)
		{
			j = strcmp(u[i].acnum, ac);
			k = strcmp(u[i].pswdnum, pass);
			if (j == 0 && k == 0)
			{
				u[i].ero = 1;
				printf("\n\n\t\treport missing finished");
				break;
			}
		}
	} while (i >= 101);
	FILE *fz = fopen("userinfo.txt", "w");
	for (i = 0; i <= 100; i++)
	{
		if (strcmp(u[i].acnum, "\0") != 0)
			fprintf(fz, "%s\t%s\t%s\t%.2lf\t%d\n", u[i].acnum, u[i].pswdnum, u[i].name, u[i].money, u[i].ero);
	}
	fclose(fz);
	printf("\n\n\t\treturn to last page, input random key to continue->");
	getch();
	userInterface();
}

void userOperate(int n)
{
	system("cls");
	date();
	int a;
	printf("\n\n\n\n\t\t\t*******choose your wanted *******");
	printf("\n\n\t\t\t1.save money\n\n\t\t\t2.withdraw money  \n\n\t\t\t3.change password  \n\n\t\t\t4.user sign off  \n\n\t\t\t5.search info \n\n\t\t\t6.exit \n");

	printf("\n\t\tplease input your choice:");
	flush();
	scanf("%d", &a);
	switch (a)
	{
		case 1:
			deposit(n);
			break;
		case 2:
			withdraw(n);
			break;
		case 3:
			changePassword(n);
			break;
		case 4:
			lostUser(n);
			break;
		case 5:
			showInfo(n);
			break;
		case 6:
			exit(0);
	}
}
void deposit(int n)
{
	date();
	int i, money;
	double temp;
	char m[10];
	do
	{
		system("cls");
		printf("\n\n\t\tplease input amount of the money you want to save:");
		gets(m);
	} while (checkAdd(m) == 0);
	money = atoi(m);
	temp = money + u[n].money;
	u[n].money = temp;
	printf("\n\t\tsave money successful");
	printf("\t\tyour current balance is:\t%.2lf\n", u[n].money);
	FILE *fz = fopen("userinfo.txt", "w");
	for (i = 0; i <= 99; i++)
	{
		if (strcmp(u[i].acnum, "\0") != 0)
			fprintf(fz, "%s\t%s\t%s\t%.2lf\t%d\n", u[i].acnum, u[i].pswdnum, u[i].name, u[i].money, u[i].ero);
	}
	fclose(fz);
	printf("\n\n\t\treturn to last page, input random key to continue->");
	getch();
	userOperate(n);
}

void withdraw(int n)
{
	date();
	int i, money;
	double temp;
	char m[10];
	do
	{
		system("cls");
		printf("\n\n\t\tplease input the amount of money you want to withdraw:");
		gets(m);
	} while (checkReduce(m, n) == 0);
	money = atoi(m);
	printf("\n\t\twithdraw successful, please get your paper money in the right port\n\n");
	temp = u[n].money - money;
	u[n].money = temp;
	printf("\t\tyour current balance is:%.2lf\n", u[n].money);

	FILE *fy = fopen("userinfo.txt", "w");
	for (i = 0; i <= 99; i++)
	{
		if (strcmp(u[i].acnum, "\0") != 0)
			fprintf(fy, "%s\t%s\t%s\t%.2lf\t%d\n", u[i].acnum, u[i].pswdnum, u[i].name, u[i].money, u[i].ero);
	}
	fclose(fy);
	printf("\n\n\t\treturn to last page, input random key to continue->");

	getch();
	userOperate(n);
}

//检验所输入字符是否符合要求：数字字符，位于100--10000的100的倍数
//符合要求返回1，不符合返回0

int checkAdd(char addmoney[])
{
	int i = 0, money; //检查待存入金额位数

	while (addmoney[i] != '\0')
	{
		if (addmoney[i] < '0' || addmoney[i] > '9') //检验输入字符的合法性
		{
			printf("\n\n\t\tinvalid character! input random key to continue\n");
			getch();
			return 0; //输入字符返回0，该检验不合格
		}
		i++;
	}

	if (i >= 6) //检验金额位数是否合法
	{
		// printf("\n\n\t\t一次性所存金额超过最大限度！\n\n\t\t按任意键继续操作\n");
		printf("\n\n\t\tsaving money exceeded the maximum limit\n\n\t\tinput random key to continue\n");

		getch();
		return 0;
	}

	money = atoi(addmoney); //将字符型金额转化为整型
	if (money % 100 == 0)   //检验金额数是否为100的倍数
	{
		if (money <= 10000 && money >= 100) //检验金额数是否符合规定范围
			return 1;
		else
		{
			// printf("\n\n\t\t金额应位于100--10000区间范围,按任意键继续操作");
			printf("\n\n\t\tthe amount of money should be loacated between 100 and 10000,input random key to continue");

			getch();
			return 0;
		}
	}
	else
	{
		// printf("\n\n\t\t存入金额数应为100的倍数！按任意键继续操作\n");
		printf("\n\n\t\tsaving money should be multiple of 100, input random key to continue\n");

		getch();
		return 0;
	}
}
//用于检查所取金额数是否符合要求：数字字符，位于100--3000的100的数
//符合要求返回1，不符合返回0
//用到头文件<stdlib.h>

int checkReduce(char reducemoney[], int j)
{
	int i = 0, money; //用于累计预取金额位数

	while (reducemoney[i] != '\0')
	{
		if (reducemoney[i] < '0' || reducemoney[i] > '9') //检验输入字符的合法性
		{
			// printf("\n\n\t\t输入的字符为非法字符!\n\n\t\t按任意键继续操作\n");
			printf("\n\n\t\tinvalid character!\n\n\t\tinput random key to continue\n");
			getch();
			return 0; //输入字符违法返回上一界面
		}
		i++;
	}

	if (i >= 5) //检验预取金额位数是否合法
	{
		// printf("\n\n\t\t一次性所存金额超过最大限度！\n\n\t\t按任意键继续操作\n");
		printf("\n\n\t\tsaving money exceeded the maximum limit\n\n\t\tinput random key to continue\n");

		getch();
		return 0;
	}

	money = atoi(reducemoney); //将字符型金额转化为整型

	if (money % 100 == 0) //检验预取金额数是否为100的倍数
	{
		if (money <= 3000 && money >= 100) //检验预取金额数是否符合规定范围
		{
			if (u[j].money >= money) //检验预取金额数是否小于用户余额
				return 1;
			else
			{
				// printf("\n\n\t\t您的余额不足！\n\n\t\t目前您的余额为:");
				// printf("%.2lf\n\n\t\t按任意键继续操作", u[j].money);

				printf("\n\n\t\tyour Your balance is insufficient.\n\n\t\tyour current balance is:");
				printf("%.2lf\n\n\t\tinput random key to continue", u[j].money);
				getch();
				return 0;
			}
		}
		else
		{
			// printf("\n\n\t\t金额数应在100--3000范围内,按任意键继续操作");

			getch();
			return 0;
		}
	}
	else
	{
		// printf("\n\n\t\t所取金额数不合法,应为100的倍数！\n\n\t\t按任意键继续操作\n");
		printf("\n\n\t\twithdrawing money should be multiple of 100!\n\n\t\t input random key to continue\n");

		getch();
		return 0;
	}
}

void changePassword(int n)
{
	system("cls");
	date();
	int i, l;
	char temp[10];
D:
	printf("\n\t\tplease input your original password:");

	scanf("%s", &password);
	l = strcmp(password, u[n].pswdnum);
	if (l != 0)
	{
		printf("\n\t\twrong password!");

		goto D;
	}
	else
	{

		printf("\n\t\tinput your new password");

		scanf("%s", temp);
		strcpy(u[n].pswdnum, temp);
	}
	FILE *fz = fopen("userinfo.txt", "w");
	for (i = 0; i <= 99; i++)
	{
		if (strcmp(u[i].acnum, "\0") != 0)
			fprintf(fz, "%s\t%s\t%s\t%.2lf\t%d\n", u[i].acnum, u[i].pswdnum, u[i].name, u[i].money, u[i].ero);
	}
	fclose(fz);
	printf("\n\t\tchange password successful!");
	printf("\n\n\t\treturn to main page,input Enter to continue->");
	getchar();
	getchar();
	userInterface();
}

void lostUser(int n)
{
	system("cls");
	date();
	int i, l;
	printf("\n\n\t\tconfirm your account again");

	scanf("%s", &account);
D:
	printf("\n\t\tplease input your password");

	scanf("%s", &password);
	l = strcmp(password, u[n].pswdnum);
	if (l != 0)
	{
		printf("\n\t\twrong password!");
		goto D;
	}
	else
	{
		strcpy(u[n].acnum, "\0");
		strcpy(u[n].pswdnum, "\0");
		strcpy(u[n].name, "\0");
		u[n].money = 0.00;
		u[n].ero = 0;
	}
	FILE *fz = fopen("userinfo.txt", "w");
	for (i = 0; i <= 99; i++)
	{
		if (u[i].acnum[0] != '\0')
			fprintf(fz, "%s\t%s\t%s\t%.2lf\t%d\n", u[i].acnum, u[i].pswdnum, u[i].name, u[i].money, u[i].ero);
	}
	printf("\n\t\tuser has been signed off\n");

	printf("\n\n\t\treturn to main page,input Enter to continue->");

	getchar();
	getchar();
	userInterface();
}

void showInfo(int n)
{
	system("cls");
	printf("\n\n\t\t%s hello!your info is as follows\n\n", u[n].name);
	printf("\n\t\tbalamce:%.2lf\n", u[n].money);
	printf("\n\n\t\treturn to last page, input random key to continue->");

	getch();
	userOperate(n);
}

void adminInterface()
{
	system("cls");
	date();
	aboutFile();
	char adminac[10], adminpd[10];
	int i, j;
	strcpy(adminac, "123456");
	strcpy(adminpd, "123456");
	printf("\n\n\n\n\n\n\t\t\thello!administrator\n\n");
	printf("\n\t\t\tinput administrator account: ");

	scanf("%s", ac);
	printf("\n\t\t\tplease input administrator password:");

	scanf("%s", pass);
	i = strcmp(ac, adminac);
	j = strcmp(pass, adminpd);
	if (i == 0 && j == 0)
	{
		printf("\n\n\t\t\thello,administrator");
		getch();
		adminOperate();
	}
	flush();
	printf("\n\n\t\t\tsorry, what you input is not administrator's account");
	getch();
	exit(0);
}
void adminOperate()
{
	system("cls");
	date();
	int a;
	FILE *fy = fopen("userinfo.txt", "r");
	if (!fy)
	{
		printf("fail to read file\n");

	}
	printf("\n\n\n\n\n\n\t\t\t*****please choose your entrance*****  ");
	printf("\n\n\t\t\t1.confirm users' info  \n\n\t\t\t2.confirm reported missing users  \n\n\t\t\t3.exit     \n\n");
	printf("\t\t\tinput your choice:");
	flush();;
	scanf("%d", &a);
	switch (a)
	{
		case 1:
			search();
			break;
		case 2:
			isLost();
			break;
		case 3:
			exit(0);
	}
}
void search()
{
	system("cls");
	date();
	int i, j;
	FILE *fy = fopen("userinfo.txt", "r");
	if (!fy)
	{
		printf("fail to read file\n");

	}
	for (i = 0; i <= 100; i++)
	{
		fscanf(fy, "%s\t%s\t%s\t%lf\t%d\n", &u[i].acnum, &u[i].pswdnum, &u[i].name, &u[i].money, &u[i].ero);
	}
	fclose(fy);
	for (j = 0; j <= 100 && u[j].acnum[0] != '\0'; j++)
	{
		printf("\n\n\n\t\t\tuser account:%s\n\n\t\t\tuser password:%s\n\n\t\t\tbalance:%.2lf\n\n\t\t\tuser status:%d\n\n",
			   u[j].acnum, u[j].pswdnum, u[j].name, u[j].money, u[j].ero);

	}
	printf("\n\n\t\tfinished, input random key to return");
	getch();
	adminOperate();
}
void isLost()
{
	system("cls");
	date();
	int i, j;
	FILE *fy = fopen("userinfo.txt", "r");
	if (!fy)
	{
		printf("fail to read file\n");

	}
	printf("\n\n");
	for (i = 0; i <= 100; i++)
	{
		fscanf(fy, "%s\t%s\t%s\t%lf\t%d\n", &u[i].acnum, &u[i].pswdnum, &u[i].name, &u[i].money, &u[i].ero);
		if (u[i].ero == 1)
		{
			printf("\n\n\n\t\t\tuser account:%s\n\n\t\t\tuser password:%s\n\n\t\t\tbalance:%.2lf\n\n\t\t\tuser status:%d\n\n",
				   u[i].acnum, u[i].pswdnum, u[i].name, u[i].money, u[i].ero);

		}
	}
	printf("\n\n\t\t\tfinished, input random key to return");
	getch();
	adminOperate();
}
