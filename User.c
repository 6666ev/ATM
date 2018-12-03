//
// Created by on 2018/12/3.
//

#include "User.h"

void aboutFile()
{
    FILE *fp = fopen("userinfo.txt", "r");
    if (fp == NULL)
    {
        // printf("用户文件不存在，将创建");
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
    // printf("**当前日期**  ");
    printf("current date");
    printf("\t");
    system("date/t");
    printf("\n");
    // printf("**当前时间**");
    printf("current time");
    printf("\t");
    system("time/t");
}
void userInterface()
{
    system("cls");
    int a, b;
    date();
    FILE *fy = fopen("userinfo.txt", "r");
    if (!fy)
    {
        // printf("无法读取文件\n");
        printf("fail to read file\n");
    }
    // printf("\n\n\n\n\t\t\t*******请选择您的入口*******");
    // printf("\n\n\t\t\t1.登录\n\n\t\t\t2.注册\n\n\t\t\t3.挂失\n\n\t\t\t4.取消挂失\n\n\t\t\t5.退出\n");
    // printf("\n\n\t\t\t请输入您的选择：");
    printf("\n\n\n\n\t\t\t*******please choose your entrance*******");
    printf("\n\n\t\t\t1.log on\n\n\t\t\t2.sign up\n\n\t\t\t3.report missing\n\n\t\t\t4.cancel missing\n\n\t\t\t5.exit\n");
    printf("\n\n\t\t\tplease input your choice");
    fflush(stdin);
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
        break;
    case 4:
        find();
        break;
    case 5:
        exit(0);
        break;
    }
}
void logIn()
{
    system("cls");
    FILE *fp = fopen("userinfo.txt", "r");
    date();
    if (!fp)
    {
        // printf("无法打开文件");
        printf("fail to open file");
    }
    int i, n, ch, index;
    int j = 0, k = 3;
    for (i = 0; i <= 100; i++)
    {
        fscanf(fp, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%lf\t%d\n", u[i].acnum, u[i].pswdnum, u[i].name, u[i].idnum, &u[i].phnum, &u[i].adrss, &u[i].cardnum, &u[i].mony, &u[i].ero);
    }
    fclose(fp);
    // printf("\n\n\t\t请正确地输入您的账号：");
    printf("\n\n\t\tplease input your right account:");
    scanf("%s", ac);
    for (i = 0; i <= 100; i++)
    {
        if (strcmp(u[i].acnum, ac) == 0)
        {
            if (u[i].ero == 1)
            {
                // printf("\n\n\t\t\t该卡已被挂失");
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
        // printf("\n\t\t该账号不存在或已注销，请注册后再登录！(按回车键返回)");
        printf("\n\n\t\tthis account doesn't exist or being signed off, \n\t\tplease sign up and log on (input Enter to return)");
        getchar();
        getchar();
        userInterface();
    }
L:
    // printf("\n\t\t请输入密码：");
    printf("\n\t\tplease input your password");
    scanf("%s", pass);
    n = strcmp(u[i].pswdnum, pass);
    if (n != 0 && k != 0)
    {
        k--;
        // printf("\n\n\t\t密码输入错误，还剩余%d次机会", k);
        printf("\n\n\t\twrong password, there are %d chances left", k);
        getch();
        fflush(stdin);
        goto L;
    }
    else if (n != 0 && k == 0)
    {
        // printf("\n\n\t\t你已经没有机会了\n");
        printf("\n\n\t\tyou have run out of chances\n");
        getch();
        userInterface();
    }
    else if (n == 0 && k != 0)
    {
        // printf("\n\n\t\t登录成功\n");
        printf("\n\n\t\tlog on successful");
        // printf("\n\n\t\t按任意键继续->");
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
    int j = 0, n = 0;
    char ac[10];
    fp = fopen("userinfo.txt", "r");
    for (i = 0; i <= 100; i++)
    {
        fscanf(fp, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%lf\t%d\n", u[i].acnum, u[i].pswdnum, u[i].name, u[i].idnum, &u[i].phnum, &u[i].adrss, &u[i].cardnum, &u[i].mony, &u[i].ero);
    }
    fclose(fp);
    op = fopen("userinfo.txt", "a+");
    date();
    fflush(stdin);
    if (!op)
    {
        // printf("无法打开文件");
        printf("fail to open file");
    }

    // printf("\n\n\t\t请输入您的账号(不超过9位)：");
    printf("\n\n\t\tplease input your account(less than 9 letter):");
    gets(ac);
    for (index = 0; index <= 100; index++)
        if (strcmp(u[index].acnum, ac) == 0)
            j++;
    while (j != 0)
    {
        // printf("\n\t\t该账号已被注册，请重新注册！(按回车键返回)");
        printf("\n\t\tthis account has been signed up, try again please!(input Enter to return)");
        getchar();
        userInterface();
    }
    strcpy(u[A].acnum, ac);
    // printf("\n\t\t请输入您的密码(不超过6位)：");
    printf("\n\t\tplease input your password(less than 6 letter):");
    gets(u[A].pswdnum);
    // printf("\n\t\t请输入您的名字：");
    printf("\n\t\tplease input your name:");
    gets(u[A].name);
    // printf("\n\t\t请输入您的身份证号(18位)：");
    printf("\n\t\tplease input your ID number(less than 18 letter):");
    gets(u[A].idnum);
    // printf("\n\t\t请输入您的电话号码：");
    printf("\n\t\tplease input your phone number:");
    gets(u[A].phnum);
    // printf("\n\t\t请输入您的地址：");
    printf("\n\t\tinput your address:");
    gets(u[A].adrss);
    // printf("\n\t\t请输入您的卡号：");
    printf("\n\t\tinput your card number:");
    printf("\n\t\t");
    gets(u[A].cardnum);
    // printf("\n\t\t预存的金额：");
    printf("\n\t\tprestored money:");
    scanf("%lf", &u[A].mony);
    u[A].ero = 0;
    fprintf(op, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%.2lf\t%d\n", u[A].acnum, u[A].pswdnum, u[A].name, u[A].idnum, u[A].phnum, u[A].adrss, u[A].cardnum, u[A].mony, u[A].ero);
    A++;
    fclose(op);
    // printf("\n\n\t\t返回之前页面，按任意键继续->");
    printf("\n\n\t\treturn to last page, input random key to continue->");
    getch();
    userInterface();
}
void missAccount()
{
    system("cls");
    int i, j, k;
    int ch;
    date();
    FILE *fy = fopen("userinfo.txt", "r");

    if (!fy)
    {
        // printf("无法创建文件\n");
        printf("fail to create file\n");
    }
    for (i = 0; i <= 100; i++)
    {
        fscanf(fy, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%lf\t%d\n", u[i].acnum, u[i].pswdnum, u[i].name, u[i].idnum, u[i].phnum, u[i].adrss, u[i].cardnum, &u[i].mony, &u[i].ero);
    }
    fclose(fy);
    do
    {
        // printf("\n\n\t\t请输入正确的要挂失的账号：");
        printf("\n\n\t\tplease input your right account to be reported missing");
        scanf("%s", ac);
        putchar('\n');
        // printf("\t\t请输入密码：");
        printf("\t\tinput your password:");
        scanf("%s", pass);
        for (i = 0; i <= 100; i++)
        {
            j = strcmp(u[i].acnum, ac);
            k = strcmp(u[i].pswdnum, pass);
            if (j == 0 && k == 0)
            {
                u[i].ero = 1;
                // printf("\n\n\t\t挂失完成");
                printf("\n\n\t\treport missing finished");
                break;
            }
        }
    } while (i >= 101);
    FILE *fz = fopen("userinfo.txt", "w");
    for (i = 0; i <= 100; i++)
    {
        if (strcmp(u[i].acnum, "\0") != 0)
            fprintf(fz, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%.2lf\t%d\n", u[i].acnum, u[i].pswdnum, u[i].name, u[i].idnum, u[i].phnum, u[i].adrss, u[i].cardnum, u[i].mony, u[i].ero);
    }
    fclose(fz);
    // printf("\n\n\t\t返回之前页面，按任意键继续->");
    printf("\n\n\t\treturn to last page, input random key to continue->");    
    getch();
    userInterface();
}

void find()
{
    system("cls");
    int i, j, k, n;
    int ch;
    date();
    FILE *fy = fopen("userinfo.txt", "r");
    for (i = 0; i <= 100; i++)
    {
        fscanf(fy, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%lf\t%d\n", &u[i].acnum, &u[i].pswdnum, &u[i].name, &u[i].idnum, &u[i].phnum, &u[i].adrss, &u[i].cardnum, &u[i].mony, &u[i].ero);
    }
    fclose(fy);
    do
    {
        // printf("\n\n\t\t请输入正确的要解除挂失的账号：");
        printf("\n\n\t\tplease input your right account to be canceled missing");
        scanf("%s", &ac);
        putchar('\n');
        // printf("\t\t请输入密码：");
        printf("\t\tinput your password");
        scanf("%s", &pass);
        for (i = 0; i <= 100; i++)
        {
            j = strcmp(u[i].acnum, ac);
            k = strcmp(u[i].pswdnum, pass);
            if (j == 0 && k == 0)
            {
                u[i].ero = 0;
                // printf("\n\n\t\t挂失取消");
                printf("\n\n\t\tcanceled report missing");
                getch();
                break;
            }
        }
    } while (i >= 101);
    FILE *fz = fopen("userinfo.txt", "w");
    for (i = 0; i <= 99; i++)
    {
        if (strcmp(u[i].acnum, "\0") != 0)
            fprintf(fz, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%.2lf\t%d\n", u[i].acnum, u[i].pswdnum, u[i].name, u[i].idnum, u[i].phnum, u[i].adrss, u[i].cardnum, u[i].mony, u[i].ero);
    }
    fclose(fz);
    // printf("\n\n\t\t返回之前页面，按任意键继续->");
    printf("\n\n\t\treturn to last page, input random key to continue->");        
    getch();
    userInterface();
}
void userOperate(int n)
{
    system("cls");
    date();
    int a;
    // printf("\n\n\n\n\t\t\t*******请选择您想使用的功能*******");
    printf("\n\n\n\n\t\t\t*******choose your wanted *******");

    // printf("\n\n\t\t\t1.存款\n\n\t\t\t2.取款  \n\n\t\t\t3.修改密码  \n\n\t\t\t4.用户注销  \n\n\t\t\t5.查询信息 \n\n\t\t\t6.退出 \n");
    printf("\n\n\t\t\t1.save money\n\n\t\t\t2.withdraw money  \n\n\t\t\t3.change password  \n\n\t\t\t4.user sign off  \n\n\t\t\t5.serach info \n\n\t\t\t6.exit \n");
    // printf("\n\t\t\t请输入您的选择： ");
    printf("\n\t\tplease input your choice:");
    fflush(stdin);
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
        break;
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
        // printf("\n\n\t\t请输入您要存入的金额：");
        printf("\n\n\t\tplease input amount of the money you want to save");
        gets(m);
    } while (checkAdd(m) == 0);
    money = atoi(m);
    temp = money + u[n].mony;
    u[n].mony = temp;
    // printf("\n\t\t存款成功!\n\n");
    printf("\n\t\tsave money successful");
    // printf("\t\t您目前的余额为：\t%.2lf\n", u[n].mony);
    printf("\t\tyour current balance is:\t%.2lf\n", u[n].mony);    
    FILE *fz = fopen("userinfo.txt", "w");
    for (i = 0; i <= 99; i++)
    {
        if (strcmp(u[i].acnum, "\0") != 0)
            fprintf(fz, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%.2lf\t%d\n", u[i].acnum, u[i].pswdnum, u[i].name, u[i].idnum, u[i].phnum, u[i].adrss, u[i].cardnum, u[i].mony, u[i].ero);
    }
    fclose(fz);
    // printf("\n\n\t\t返回之前页面，按任意键继续->");
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
        // printf("\n\n\t\t请输入您要取出金额：");
        printf("\n\n\t\tplease input the amount of money you want to withdraw");

        gets(m);
    } while (checkReduce(m, n) == 0);
    money = atoi(m);
    // printf("\n\t\t取出成功，请及时在对应窗口取出您的钞票\n\n");
    printf("\n\t\twithdraw successful, please get your paper money in the right port\n\n");
    temp = u[n].mony - money;
    u[n].mony = temp;
    // printf("\t\t您目前的余额为:%.2lf\n", u[n].mony);
    printf("\t\tyour current balance is:%.2lf\n", u[n].mony);
    
    FILE *fy = fopen("userinfo.txt", "w");
    for (i = 0; i <= 99; i++)
    {
        if (strcmp(u[i].acnum, "\0") != 0)
            fprintf(fy, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%.2lf\t%d\n", u[i].acnum, u[i].pswdnum, u[i].name, u[i].idnum, u[i].phnum, u[i].adrss, u[i].cardnum, u[i].mony, u[i].ero);
    }
    fclose(fy);
    // printf("\n\n\t\t返回之前页面，按任意键继续->");
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
            // printf("\n\n\t\t输入的字符为非法字符!按任意键继续操作\n");
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
            if (u[j].mony >= money) //检验预取金额数是否小于用户余额
                return 1;
            else
            {
                // printf("\n\n\t\t您的余额不足！\n\n\t\t目前您的余额为:");
                // printf("%.2lf\n\n\t\t按任意键继续操作", u[j].mony);

                printf("\n\n\t\tyour Your balance is insufficient.\n\n\t\tyour current balance is:");
                printf("%.2lf\n\n\t\tinput random key to continue", u[j].mony);
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
    int i, l, ch;
    double m;
    char temp[10];
D:
    // printf("\n\t\t请输入您的原密码：");
    printf("\n\t\tplease input your original password:");
    
    scanf("%s", &password);
    l = strcmp(password, u[n].pswdnum);
    if (l != 0)
    {
        // printf("\n\t\t密码输入错误！");
        printf("\n\t\twrong password!");

        goto D;
    }
    else
    {
        // printf("\n\t\t请输入新密码：");
        printf("\n\t\tinput your new password");
        
        scanf("%s", temp);
        strcpy(u[n].pswdnum, temp);
    }
    FILE *fz = fopen("userinfo.txt", "w");
    for (i = 0; i <= 99; i++)
    {
        if (strcmp(u[i].acnum, "\0") != 0)
            fprintf(fz, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%.2lf\t%d\n", u[i].acnum, u[i].pswdnum, u[i].name, u[i].idnum, u[i].phnum, u[i].adrss, u[i].cardnum, u[i].mony, u[i].ero);
    }
    fclose(fz);
    // printf("\n\t\t密码修改成功!");
    printf("\n\t\tchange password successful!");
    
    // printf("\n\n\t\t返回主页面，按回车键继续->");
    printf("\n\n\t\treturn to main page,input Enter to continue->");
    
    getchar();
    getchar();
    userInterface();
}

void lostUser(int n)
{
    system("cls");
    date();
    int i, l, ch;
    double m, temp;
    // printf("\n\n\t\t请再次确认您的账号：");
    printf("\n\n\t\tconfirm your account again");
    
    scanf("%s", &account);
D:
    // printf("\n\t\t请输入您的密码：");
    printf("\n\t\tplease input your password");
    
    scanf("%s", &password);
    l = strcmp(password, u[n].pswdnum);
    if (l != 0)
    {
        // printf("\n\t\t密码输入错误！");
        printf("\n\t\twrong password!");        
        goto D;
    }
    else
    {
        strcpy(u[n].acnum, "\0");
        strcpy(u[n].pswdnum, "\0");
        strcpy(u[n].name, "\0");
        strcpy(u[n].idnum, "\0");
        strcpy(u[n].phnum, "\0");
        strcpy(u[n].adrss, "\0");
        strcpy(u[n].cardnum, "\0");
        u[n].mony = 0.00;
        u[n].ero = 0;
    }
    FILE *fz = fopen("userinfo.txt", "w");
    for (i = 0; i <= 99; i++)
    {
        if (u[i].acnum[0] != '\0')
            fprintf(fz, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%.2lf\t%d\n", u[i].acnum, u[i].pswdnum, u[i].name, u[i].idnum, u[i].phnum, u[i].adrss, u[i].cardnum, u[i].mony, u[i].ero);
    }
    // printf("\n\t\t用户已注销！\n");
    printf("\n\t\tuser has been signed off\n");

    // printf("\n\n\t\t返回主页面，按回车键继续->");
    printf("\n\n\t\treturn to main page,input Enter to continue->");
    
    getchar();
    getchar();
    userInterface();
}

void showInfo(int n)
{
    system("cls");
    // printf("\n\n\t\t%s您好，您的信息如下\n\n", u[n].name);
    // printf("\n\n\t\t账号(卡号)：%s\n", u[n].acnum);
    // printf("\n\t\t身份证号：%s\n", u[n].idnum);
    // printf("\n\t\t电话号码：%s\n", u[n].phnum);
    // printf("\n\t\t地址：%s\n", u[n].adrss);
    // printf("\n\t\t余额：%.2lf\n", u[n].mony);
    // printf("\n\n\t\t返回之前页面，按任意键继续->");

   printf("\n\n\t\t%s hello!your info is as follows\n\n", u[n].name);
    printf("\n\n\t\taccount(card number):%s\n", u[n].acnum);
    printf("\n\t\tID number:%s\n", u[n].idnum);
    printf("\n\t\tphone number:%s\n", u[n].phnum);
    printf("\n\t\taddress:%s\n", u[n].adrss);
    printf("\n\t\tbalamce:%.2lf\n", u[n].mony);
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
    int i, j, k;
    strcpy(adminac, "245316");
    strcpy(adminpd, "1q2w3e4r");
    // printf("\n\n\n\n\n\n\t\t\t您好!管理员\n\n");
    // printf("\n\t\t\t请输入管理员账号： ");
    printf("\n\n\n\n\n\n\t\t\thello!administrator\n\n");
    // printf("\n\t\t\t请输入管理员账号： ");
    printf("\n\t\t\tinput administrator account: ");
    
    scanf("%s", ac);
    // printf("\n\t\t\t请输入管理员密码：");
    printf("\n\t\t\tplease input administrator password:");    

    scanf("%s", pass);
    i = strcmp(ac, adminac);
    j = strcmp(pass, adminpd);
    if (i == 0 && j == 0)
    {
        // printf("\n\n\t\t\t欢迎，管理员");
        printf("\n\n\t\t\thello,administrator");

        getch();
        adminOperate();
    }
    fflush(stdin);
    // printf("\n\n\t\t\t抱歉，您输入的不是管理员账号");
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
        // printf("无法读取文件\n");
        printf("fail to read file\n");        
        
    }
    // printf("\n\n\n\n\n\n\t\t\t*****请选择您的入口*****  ");
    // printf("\n\n\t\t\t1.确认用户信息  \n\n\t\t\t2.确认挂失用户  \n\n\t\t\t3.退出     \n\n");
    // printf("\t\t\t请输入您的选择：");
    printf("\n\n\n\n\n\n\t\t\t*****please choose your entrance*****  ");
    printf("\n\n\t\t\t1.confirm users' info  \n\n\t\t\t2.confirm reported missing users  \n\n\t\t\t3.exit     \n\n");
    printf("\t\t\tinput your choice:");
    fflush(stdin);
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
        break;
    }
}
void search()
{
    system("cls");
    date();
    int i, j, k;
    char c;
    FILE *fy = fopen("userinfo.txt", "r");
    if (!fy)
    {
        // printf("无法读取文件\n");
        printf("fail to read file\n");        
        
    }
    for (i = 0; i <= 100; i++)
    {
        fscanf(fy, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%lf\t%d\n", &u[i].acnum, &u[i].pswdnum, &u[i].name, &u[i].idnum, &u[i].phnum, &u[i].adrss, &u[i].cardnum, &u[i].mony, &u[i].ero);
    }
    fclose(fy);
    for (j = 0; j <= 100 && u[j].acnum[0] != '\0'; j++)
    {
        // printf("\n\n\n\t\t\t用户账号：%s\n\n\t\t\t用户密码：%s\n\n\t\t\t用户名：%s\n\n\t\t\t身份证号：%s\n\n\t\t\t电话号码：%s\n\n\t\t\t地址：%s\n\n\t\t\t卡号：%s\n\n\t\t\t余额%.2lf\n\n\t\t\t用户状态%d\n\n",
        //        u[j].acnum, u[j].pswdnum, u[j].name, u[j].idnum, u[j].phnum, u[j].adrss, u[j].cardnum, u[j].mony, u[j].ero);
        printf("\n\n\n\t\t\tuser account:%s\n\n\t\t\tuser password:%s\n\n\t\t\tuser name:%s\n\n\t\t\tID number:%s\n\n\t\t\tphone number:%s\n\n\t\t\taddress:%s\n\n\t\t\tcard number:%s\n\n\t\t\tbalance:%.2lf\n\n\t\t\tuser status:%d\n\n",
                 u[j].acnum, u[j].pswdnum, u[j].name, u[j].idnum, u[j].phnum, u[j].adrss, u[j].cardnum, u[j].mony, u[j].ero);
              
    }
    // printf("\n\n\t\t完成，按任意键返回");
    printf("\n\n\t\tfinished, input random key to return");    

    getch();
    adminOperate();
}
void isLost()
{
    system("cls");
    date();
    int i, j, k;
    FILE *fy = fopen("userinfo.txt", "r");
    if (!fy)
    {
        // printf("无法读取文件\n");
        printf("fail to read file\n");
        
    }
    printf("\n\n");
    for (i = 0; i <= 100; i++)
    {
        fscanf(fy, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%lf\t%d\n", &u[i].acnum, &u[i].pswdnum, &u[i].name, &u[i].idnum, &u[i].phnum, &u[i].adrss, &u[i].cardnum, &u[i].mony, &u[i].ero);
        if (u[i].ero == 1)
        {
            // printf("\t\t\t用户账号：%s\n\n\t\t\t用户密码：%s\n\n\t\t\t用户名：%s\n\n\t\t\t身份证号：%s\n\n\t\t\t电话号码：%s\n\n\t\t\t地址：%s\n\n\t\t\t卡号：%s\n\n\t\t\t余额%.2lf\n\n\t\t\t用户状态%d\n\n", u[i].acnum, u[i].pswdnum, u[i].name, u[i].idnum, u[i].phnum, u[i].adrss, u[i].cardnum, u[i].mony, u[i].ero);
            printf("\n\n\n\t\t\tuser account:%s\n\n\t\t\tuser password:%s\n\n\t\t\tuser name:%s\n\n\t\t\tID number:%s\n\n\t\t\tphone number:%s\n\n\t\t\taddress:%s\n\n\t\t\tcard number:%s\n\n\t\t\tbalance:%.2lf\n\n\t\t\tuser status:%d\n\n",
                 u[j].acnum, u[j].pswdnum, u[j].name, u[j].idnum, u[j].phnum, u[j].adrss, u[j].cardnum, u[j].mony, u[j].ero);
        
        }
    }
    // printf("\n\n\t\t\t完成，按任意键返回");
    printf("\n\n\t\t\tfinished, input random key to return");
    
    getch();
    adminOperate();
}