//
// Created by 96399 on 2018/12/16.
//

#include "user.h"
int A=0;
//文件准备函数
void aboutFile()
{
    FILE *fp = fopen("test.txt", "r");
    if (!fp)
    {
        FILE *fp = fopen("test.txt", "w");
        fclose(fp);
        return;
    }
    fclose(fp);
}

//捕获时间函数
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

//主界面函数
void Main()
{
    int i;
    system("cls");
    aboutFile();
    system("color 31");
    date();
    printf("\n\n\n\t\t\tPlease select your identity category: ");
    printf("\n\n\t\t\t1.user   ");
    printf("\n\n\t\t\t2.admin   ");
    printf("\n\n\t\t\t3.exit   ");
    printf("\n\n\n");
    printf("\t\t\tplease choose:");
    fflush(stdin);
    scanf("%d", &i);
    if(i==1)
        userInterface();
    if(i==2)
        adminInterface();
    if(i==3)
        return;
}

//用户界面
void userInterface()
{
    system("cls");
    date();
    int i;
    FILE *fp = fopen("test.txt", "r");
    if (!fp)
        printf("fail to read file\n");
    printf("\n\n\n\n\t\t\t*******please choose your entrance*******");
    printf("\n\n\t\t\t1.log on\n\n\t\t\t2.sign up\n\n\t\t\t3.report for lost\n\n\t\t\t4.exit\n");
    printf("\n\n\t\t\tplease input your choice:");
    fflush(stdin);
    scanf("%d", &i);
    if(i==1)
        logIn();
    if(i==2)
        signIn();
    if(i==3)
        missAccount();
    if(i==4)
        Main();           //回到主界面
}

void logIn()
{
    system("cls");
    date();
    char inputAccount[10];   //用户输入的帐号
    char inputPassword[10];  //用户输入的密码
    FILE *fp = fopen("test.txt", "r");
    if (!fp)
        printf("fail to open file");
    int chanceNumber=3;
    int i;                   //将被选出来的用户序号;
    int j=0;                 //一个flag;
    for (i = 0; i <=N; i++)
        fscanf(fp, "%s\t%s\t%s\t%lf\t%d\n", user[i].accounts, user[i].password, user[i].name,&user[i].prestore,&user[i].isMissing);
    fclose(fp);
    printf("\n\n\t\tplease input your right account: ");
    getchar();
    gets(inputAccount);
    for (i = 0; i <=N; i++)
    {
        if (strcmp(user[i].accounts, inputAccount) == 0)                  //进行对比
        {
            j++;                              //flag;
            if (user[i].isMissing == 1)                                      //注册的帐号被挂失时的情况;
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
    if (j == 0)                                            //帐号不存在的情况
    {
        printf("\n\n\t\tthis account doesn't exist or being signed off, \n\t\tplease sign up and log on (input Enter to return)");
        getchar();
        getchar();
        userInterface();
    }
    //登录密码次数的现在
    while(chanceNumber--)
    {
        int flag;
        printf("\n\t\tplease input your password:");
        gets(inputPassword);
        flag=strcmp(user[i].password, inputPassword);
        if(flag)
        {
            printf("\n\n\t\twrong password, there are %d chances left", chanceNumber);
            fflush(stdin);
            continue;
        }
        else
        {
            break;
        }
    }
    printf("\n\n\t\tlog on successful");
    printf("\n\n\t\tinput any key to continue->");
    getchar();
    userOperate(i);
}

void signIn()
{
    system("cls");
    date();
    fflush(stdin);
    int j = 0;
    char inputAccounts[10];   //记录用户输入的帐号
    FILE* fp = fopen("test.txt", "r");
    for (int i = 0; i <= N; i++)
        fscanf(fp, "%s\t%s\t%s\t%lf\t%d\n", user[i].accounts, user[i].password, user[i].name,&user[i].prestore,&user[i].isMissing);
    fclose(fp);
    FILE* op = fopen("test.txt", "a+");
    if (!op)
        printf("fail to open file");
    printf("\n\n\t\tplease input your account(less than 10 letter):");
    gets(inputAccounts);
    for (int i = 0; i <= N; i++)                   //进行对比，看帐号是否被注册
        if (strcmp(user[i].accounts, inputAccounts) == 0)
            j++;         //flag;
    if (j != 0)
    {
        printf("\n\t\tthis account has been signed up, try again please!(input Enter to return)");
        getchar();
        userInterface();
    }
    strcpy(user[A].accounts, inputAccounts);
    printf("\n\t\tplease input your password(less than 6 letter):");
    gets(user[A].password);
    printf("\n\t\tplease input your name:");
    gets(user[A].name);
    printf("\n\t\tprestored money:");
    scanf("%lf", &user[A].prestore);
    user[A].isMissing=0;
    fprintf(op, "%s\t%s\t%s\t%.2lf\t%d\n", user[A].accounts, user[A].password, user[A].name,user[A].prestore,user[A].isMissing);
    A++;                       //增加了一名用户;
    fclose(op);
    printf("\n\n\t\treturn to last page, input random key to continue->");
    getchar();
    userInterface();                //返回到主界面
}

void missAccount()
{
    system("cls");
    date();
    int i, j, k;             //j,k两个flag;
    char inputAccounts[10];
    char inputPassword[10];
    FILE *fp = fopen("test.txt", "r");
    if (!fp)
        printf("fail to create file\n");
    for (i=0;i<=N;i++)
        fscanf(fp, "%s\t%s\t%s\t%lf\t%d\n", user[i].accounts, user[i].password, user[i].name,&user[i].prestore,&user[i].isMissing);
    fclose(fp);
    //进行注销
    printf("\n\n\t\tplease input your right account to be reported missing");
    getchar();
    gets(inputAccounts);
    printf("\n\t\tinput your password:");
    gets(inputPassword);
    for (i =0;i<=N; i++)
    {
        j = strcmp(user[i].accounts, inputAccounts);
        k = strcmp(user[i].password, inputPassword);
        if (j == 0 && k == 0)
        {
            user[i].isMissing = 1;
            printf("\n\n\t\treport missing finished");
            break;
        }
    }
    FILE *fz = fopen("test.txt", "w");
    for (i=0;i<=N; i++)
        if (strcmp(user[i].accounts, "\0") != 0)
            fprintf(fz, "%s\t%s\t%s\t%.2lf\t%d\n", user[i].accounts, user[i].password, user[i].name,user[i].prestore,user[i].isMissing);
    fclose(fz);
    printf("\n\n\t\treturn to last page, input random key to continue->");
    getchar();
    userInterface();
}

void userOperate(int n)
{
    system("cls");
    date();
    int i;
    printf("\n\n\n\n\t\t\t*******choose your wanted *******");
    printf("\n\n\t\t\t1.save money\n\n\t\t\t2.withdraw money  \n\n\t\t\t3.change password  \n\n\t\t\t4.user sign off  \n\n\t\t\t5.search info \n\n\t\t\t6.exit \n");
    printf("\n\t\tplease input your choice:");
    fflush(stdin);
    scanf("%d", &i);
    if(i==1)
        deposit(n);
    if(i==2)
        withdraw(n);
    if(i==3)
        changePassword(n);
    if(i==4)
        lostUser(n);
    if(i==5)
        showInfo(n);
    if(i==6)
        userInterface();
}

void deposit(int n)
{
    date();
    int money;
    double TS;               //暂存数据;
    char inputMoney[10];
    system("cls");
    printf("\n\n\t\tplease input amount of the money you want to save");
    getchar();
    gets(inputMoney);
    money=atoi(inputMoney);
    TS= money + user[n].prestore;
    user[n].prestore=TS;
    printf("\n\t\tsave money successful");
    printf("\t\tyour current balance is:\t%.2lf\n", user[n].prestore);
    FILE *fz = fopen("test.txt", "w");
    for (int i=0; i<N; i++)
    {
        if (strcmp(user[i].accounts, "\0") != 0)
            fprintf(fz, "%s\t%s\t%s\t%.2lf\t%d\n", user[i].accounts, user[i].password, user[i].name,user[i].prestore,user[i].isMissing);
    }
    fclose(fz);
    printf("\n\n\t\treturn to last page, input random key to continue->");
    getchar();
    userOperate(n);
}

void withdraw(int n)
{
    date();
    int  money;
    double TS;
    char inputMoney[10];
    system("cls");
    printf("\n\n\t\tplease input the amount of money you want to withdraw");
    getchar();
    gets(inputMoney);
    money = atoi(inputMoney);
    printf("\n\t\twithdraw successful, please get your paper money in the right port\n\n");
    TS = user[n].prestore-money;
    user[n].prestore =TS;
    printf("\t\tyour current balance is:%.2lf\n", user[n].prestore);

    FILE *fp = fopen("test.txt", "w");
    for (int i=0; i<N; i++)
    {
        if (strcmp(user[i].accounts, "\0") != 0)
            fprintf(fp, "%s\t%s\t%s\t%.2lf\t%d\n", user[i].accounts, user[i].password, user[i].name,user[i].prestore,user[i].isMissing);
    }
    fclose(fp);
    printf("\n\n\t\treturn to last page, input random key to continue->");
    getchar();
    userOperate(n);
}

void changePassword(int n)
{
    system("cls");
    date();
    int j;                    //flag
    char inputPassword[10];
    //直到输对密码并且输入新的密码为止
    while(1)
    {
        printf("\n\t\tplease input your original password:");
        getchar();
        gets(inputPassword);
        j= strcmp(inputPassword, user[n].password);
        if ( j!= 0)
        {
            printf("\n\t\twrong password!");
            continue;
        }
        else
        {
            printf("\n\t\tinput your new password");
            gets(inputPassword);
            strcpy(user[n].password, inputPassword);
            break;
        }
    }
    FILE *fp = fopen("test.txt", "w");
    for (int i = 0; i <N; i++)
    {
        if (strcmp(user[i].accounts, "\0") != 0)
            fprintf(fp, "%s\t%s\t%s\t%.2lf\t%d\n", user[i].accounts, user[i].password, user[i].name,user[i].prestore,user[i].isMissing);
    }
    fclose(fp);
    printf("\n\t\tchange password successful!");
    printf("\n\n\t\treturn to main page,input Enter to continue->");
    getchar();
    userInterface();
}

void lostUser(int n)
{
    system("cls");
    date();
    char inputAccounts[10];
    char inputPassword[10];
    int j;
    printf("\n\n\t\tconfirm your account again");
    getchar();
    gets(inputAccounts);
    while(1)
    {
        printf("\n\t\tplease input your password");
        gets(inputPassword);
        j = strcmp(inputPassword, user[n].password);
        if (j!= 0)
        {
            printf("\n\t\twrong password!");
            continue;
        }
        else
        {
            strcpy(user[n].accounts, "\0");
            strcpy(user[n].password, "\0");
            strcpy(user[n].name, "\0");
            user[n].prestore = 0.00;
            user[n].isMissing = 0;
            break;
        }
    }
    FILE *fp= fopen("test.txt", "w");
    for (int i = 0;i <N; i++)
    {
        if (strcmp(user[i].accounts, "\0") != 0)
            fprintf(fp, "%s\t%s\t%s\t%.2lf\t%d\n", user[i].accounts, user[i].password, user[i].name,user[i].prestore,user[i].isMissing);
    }
    fclose(fp);
    printf("\n\t\tuser has been signed off\n");
    printf("\n\n\t\treturn to main page,input Enter to continue->");
    getchar();
    userInterface();
}

void showInfo(int n)
{
    system("cls");
    date();
    printf("\n\n\t\t%s hello!your info is as follows\n\n", user[n].name);
    printf("\n\t\tbalance:%.2lf\n", user[n].prestore);
    printf("\n\n\t\treturn to last page, input random key to continue->");
    getchar();
    getchar();
    userOperate(n);
}

void adminInterface()
{
    system("cls");
    date();
    aboutFile();
    char adminAccounts[10], adminPassword[10];
    char inputAccounts[10], inputPassword[10];
    int i, j;                                         //两个flag;
    strcpy(adminAccounts, "123456");
    strcpy(adminPassword, "123456");
    while (1)
    {
        printf("\n\n\n\n\n\n\t\t\thello!administrator\n\n");
        printf("\n\t\t\tinput administrator account: ");
        getchar();
        gets(inputAccounts);
        printf("\n\t\t\tplease input administrator password:");
        gets(inputPassword);
        i = strcmp(inputAccounts, adminAccounts);
        j = strcmp(inputPassword, adminPassword);
        if (i == 0 && j == 0)
        {
            printf("\n\n\t\t\thello,administrator");
            getchar();
            adminOperate();
            break;
        } else{
            printf("\n\n\t\t\tsorry, what you input is not administrator's account");
            continue;
        }
    }
}

void adminOperate()
{
    system("cls");
    date();
    int i;
    FILE *fp = fopen("test.txt", "r");
    if (!fp)
        printf("fail to read file\n");
    fclose(fp);
    printf("\n\n\n\n\n\n\t\t\t*****please choose your entrance*****  ");
    printf("\n\n\t\t\t1.confirm users' info  \n\n\t\t\t2.confirm reported missing users  \n\n\t\t\t3.exit     \n\n");
    printf("\t\t\tinput your choice:");
    fflush(stdin);
    scanf("%d", &i);
    if(i==1)
        search();
    if(i==2)
        isLost();
    if(i==3)
        Main();
}

void search()
{
    system("cls");
    date();
    FILE *fp = fopen("test.txt", "r");
    if (!fp)
        printf("fail to read file\n");
    for (int i=0;i<N; i++)
        fscanf(fp,"%s\t%s\t%s\t%lf\t%d\n", user[i].accounts, user[i].password, user[i].name,&user[i].prestore,&user[i].isMissing);
    fclose(fp);
    for (int i=0;i<N && strcmp(user[i].accounts,"\0")!=0; i++)
        printf("\n\n\n\t\t\tuser account:%s\n\n\t\t\tuser password:%s\n\n\t\t\tuser name:%s\n\n\t\t\tbalance:%.2lf\n\n\t\t\tuser status:%d\n\n",
               user[i].accounts, user[i].password, user[i].name,user[i].prestore,user[i].isMissing);
    printf("\n\n\t\tfinished, input random key to return");
    getchar();
    getchar();
    adminOperate();
}

void isLost()
{
    system("cls");
    date();
    FILE *fp = fopen("test.txt", "r");
    if (!fp)
        printf("fail to read file\n");
    printf("\n\n");
    for (int i = 0; i<N; i++)
    {
        fscanf(fp, "%s\t%s\t%s\t%lf\t%d\n", user[i].accounts, user[i].password, user[i].name,&user[i].prestore,&user[i].isMissing);
        if (user[i].isMissing==1)
            printf("\n\n\n\t\t\tuser account:%s\n\n\t\t\tuser password:%s\n\n\t\t\tuser name:%s\n\n\t\tbalance:%.2lf\n\n\t\t\tuser status:%d\n\n",
                   user[i].accounts, user[i].password, user[i].name,user[i].prestore,user[i].isMissing);
    }
    printf("\n\n\t\t\tfinished, input random key to return");
    getchar();
    getchar();
    adminOperate();
}


