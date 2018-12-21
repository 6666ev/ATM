//
// Created by 96399 on 2018/12/16.
//

#include "User.h"
#include "fileProcessing.h"
#ifdef __clang__
#include "fileProcessing.c"
#endif
struct user user[N];
int userNum = 0;

void compatiablyFlush()
{
#ifdef _MSC_VER
    getchar();
#else
    fflush(stdin);
#endif
}

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

int checkPw(char *password)
{
    int res = 1;
    int digitNum = 0;
    int alphaNum = 0;
    int containInvalidChar = 0;

    for (int i = 0; i < strlen(password); ++i)
    {
        if (isalpha(password[i]))
        {
            ++digitNum;
        }
        else if (isdigit(password[i]))
        {
            ++alphaNum;
        }
        else
        {
            containInvalidChar = 1;
            break;
        }
    }
    if (strlen(password) > 10 || strlen(password) < 6 || digitNum == 0 || alphaNum == 0 || containInvalidChar == 1)
    {
        res = 0;
    }
    return res;
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
    do
    {
        char i;
        system("cls");
        system("color 31");
        date();
        userNum = Read();
        printf("\n\n\n\t\t\tPlease select your identity category: ");
        printf("\n\n\t\t\t1.user   ");
        printf("\n\n\t\t\t2.admin   ");
        printf("\n\n\t\t\t3.exit   ");
        printf("\n\n\n");
        printf("\t\t\tplease choose:");
        i = getchar();
        getchar(); //读走换行符
        if (i == '1')
            userInterface();
        else if (i == '2')
            adminInterface();
        else if (i == '3')
            break;
        else
            printf("Invalid input!");
    } while (1);
}

//用户界面
void userInterface()
{
    do
    {
        system("cls");
        date();
        userNum = Read();
        char i;
        printf("\n\n\n\n\t\t\t*******please choose your entrance*******");
        printf("\n\n\t\t\t1.log on\n\n\t\t\t2.sign up\n\n\t\t\t3.report for lost\n\n\t\t\t4.exit\n");
        printf("\n\n\t\t\tplease input your choice:");
        i = getchar();
        getchar(); //读走换行符
        switch (i)
        {
        case '1':
            logIn();
            break;
        case '2':
            signIn();
            break;
        case '3':
            missAccount();
            break;
        case '4':
            return; //回到主界面
        }
    } while (1);
}

void logIn()
{
    system("cls");
    date();
    userNum = Read();
    char inputAccount[10];  //用户输入的帐号
    char inputPassword[10]; //用户输入的密码
    int chanceNumber = 3;
    int i;     //将被选出来的用户序号;
    int j = 0; //一个flag;
    printf("\n\n\t\tplease input your right account: ");
    gets(inputAccount);
    for (i = 0; i < userNum; i++)
    {
        if (strcmp(user[i].accounts, inputAccount) == 0) //进行对比
        {
            j++;                        //flag;
            if (user[i].isMissing == 1) //注册的帐号被挂失时的情况;
            {
                printf("\n\n\t\tthis card is reported missing");
                getchar();
                return;
            }
            else
                break;
        }
    }
    if (j == 0) //帐号不存在的情况
    {
        printf("\n\n\t\tthis account doesn't exist or being signed off, \n\t\tplease sign up and log on (input Enter to return)");
        getchar();
        return;
    }
    //登录密码次数的现在
    while (chanceNumber--)
    {
        int flag;
        printf("\n\t\tplease input your password:");
        gets(inputPassword);
        flag = strcmp(user[i].password, inputPassword);
        if (flag)
        {
            printf("\n\n\t\twrong password, there are %d chances left", chanceNumber);
            getchar();
            //compatiablyFlush();
            continue;
        }
        else
            break;
    }

    if(chanceNumber==-1){
        printf("\n\n\t\tyou run out of chances");
        printf("\n\n\t\tinput any key to continue->");
        getchar();
        return;
    }

    printf("\n\n\t\tlog on successful");
    printf("\n\n\t\tinput any key to continue->");
    getchar();
    userOperate(i);
    return;
}

void signIn()
{
    system("cls");
    date();
    userNum = Read();
    int j = 0;
    char inputAccounts[10]; //记录用户输入的帐号
    printf("\n\n\t\tplease input your account(less than 10 letter):");
    gets(inputAccounts);
    for (int i = 0; i < userNum; i++) //进行对比，看帐号是否被注册
        if (strcmp(user[i].accounts, inputAccounts) == 0)
            j++; //flag;
    if (j != 0)
    {
        printf("\n\t\tthis account has been signed up, try again please!(input Enter to return)");
        getchar();
        return;
    }
    strcpy(user[userNum].accounts, inputAccounts);
    printf("\n\t\tyour password should be at least 6 letters and contains both alpha and number.\n");
    printf("\n\t\tplease input your password:");

    int flag;
    char pw[10];
    do
    {
        gets(pw);
        flag = checkPw(pw);
        if (flag == 0)
        {
            printf("\n\t\tinvalid password!\n\t\tinput again:");
        }
    } while (flag == 0);
    strcpy(user[userNum].password, pw);

    printf("\n\t\tplease input your name:");
    gets(user[userNum].name);
    printf("\n\t\tprestored money:");
    scanf("%lf", &user[userNum].prestore);
    user[userNum].isMissing = 0;
    userNum++; //增加了一名用户;
    Write();
    printf("\n\n\t\treturn to last page, input random key to continue->");
    getchar();
    return; //返回到主界面
}

void missAccount()
{
    system("cls");
    date();
    userNum = Read();
    int i, j, k; //j,k两个flag;
    char inputAccounts[10];
    char inputPassword[10];
    //进行注销
    printf("\n\n\t\tplease input your right account to be reported missing");
    gets(inputAccounts);
    printf("\n\t\tinput your password:");
    gets(inputPassword);
    for (i = 0; i < userNum; i++)
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
    printf("\n\n\t\treturn to last page, input random key to continue->");
    Write();
    getchar();
    return;
}

void userOperate(int n)
{
    do
    {
        system("cls");
        date();
        userNum = Read();
        char i;
        printf("\n\n\n\n\t\t\t*******choose your wanted *******");
        printf("\n\n\t\t\t1.save money\n\n\t\t\t2.withdraw money  \n\n\t\t\t3.change password  \n\n\t\t\t4.user sign off  \n\n\t\t\t5.search info \n\n\t\t\t6.exit \n");
        printf("\n\t\tplease input your choice:");
        i = getchar();
        getchar();
        switch (i)
        {
        case '1':
            deposit(n);
            break;
        case '2':
            withdraw(n);
            break;
        case '3':
            changePassword(n);
            return; //修改密码后要求重新登陆
        case '4':
            lostUser(n);
            break;
        case '5':
            showInfo(n);
            break;
        case '6':
            return;
        }
    } while (1);
}

void deposit(int n)
{
    system("cls");
    date();
    userNum = Read();
    int money;
    double TS; //暂存数据;
    char inputMoney[10];
    system("cls");
    printf("\n\n\t\tplease input amount of the money you want to save");
    gets(inputMoney);
    money = atoi(inputMoney);
    TS = money + user[n].prestore;
    user[n].prestore = TS;
    printf("\n\t\tsave money successful");
    printf("\t\tyour current balance is:\t%.2lf\n", user[n].prestore);
    printf("\n\n\t\treturn to last page, input random key to continue->");
    Write();
    getchar();
    return;
}

void withdraw(int n)
{
    system("cls");
    date();
    userNum = Read();
    int money;
    double TS;
    char inputMoney[10];
    system("cls");
    printf("\n\n\t\tplease input the amount of money you want to withdraw");
    gets(inputMoney);
    money = atoi(inputMoney);
    printf("\n\t\twithdraw successful, please get your paper money in the right port\n\n");
    TS = user[n].prestore - money;
    user[n].prestore = TS;
    printf("\t\tyour current balance is:%.2lf\n", user[n].prestore);
    printf("\n\n\t\treturn to last page, input random key to continue->");
    Write();
    getchar();
    return;
}

void changePassword(int n)
{
    system("cls");
    date();
    userNum = Read();
    int j; //flag
    char inputPassword[10];
    //直到输对密码并且输入新的密码为止
    while (1)
    {
        printf("\n\t\tplease input your original password:");
        gets(inputPassword);
        j = strcmp(inputPassword, user[n].password);
        if (j != 0)
        {
            printf("\n\t\twrong password!");
            continue;
        }
        else
        {
            printf("\n\t\tyour password should be at least 6 letters and contains both alpha and number.\n");
            printf("\n\t\tinput your new password:");
            // gets(inputPassword);

            int flag;
            char pw[10];
            do
            {
                gets(pw);
                flag = checkPw(pw);
                if (flag == 0)
                {
                    printf("\n\t\tinvalid password!\n\t\tinput again:");
                }
            } while (flag == 0);
            strcpy(user[n].password, pw);

            // strcpy(user[n].password, inputPassword);
            break;
        }
    }
    printf("\n\t\tchange password successful!");
    printf("\n\n\t\treturn to main page,input Enter to continue->");
    Write();
    getchar();
    return;
}

void lostUser(int n)
{
    system("cls");
    date();
    userNum = Read();
    char inputAccounts[10];
    char inputPassword[10];
    int j;
    printf("\n\n\t\tconfirm your account again");
    gets(inputAccounts);
    while (1)
    {
        printf("\n\t\tplease input your password");
        gets(inputPassword);
        j = strcmp(inputPassword, user[n].password);
        if (j != 0)
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
    printf("\n\t\tuser has been signed off\n");
    printf("\n\n\t\treturn to main page,input Enter to continue->");
    Write();
    getchar();
}

void showInfo(int n)
{
    system("cls");
    date();
    userNum = Read();
    printf("\n\n\t\t%s hello!your info is as follows\n\n", user[n].name);
    printf("\n\t\tbalance:%.2lf\n", user[n].prestore);
    printf("\n\n\t\treturn to last page, input random key to continue->");
    getchar();
    return;
}

void adminInterface()
{
    system("cls");
    date();
    userNum = Read();
    char adminAccounts[10], adminPassword[10];
    char inputAccounts[10], inputPassword[10];
    int i, j; //两个flag;
    strcpy(adminAccounts, "123456");
    strcpy(adminPassword, "123456");
    while (1)
    {
        printf("\n\n\n\n\n\n\t\t\thello!administrator\n\n");
        printf("\n\t\t\tinput administrator account: ");
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
        }
        else
        {
            printf("\n\n\t\t\tsorry, what you input is not administrator's account");
            continue;
        }
    }
}

void adminOperate()
{
    do
    {
        system("cls");
        date();
        char i;
        userNum = Read();
        printf("\n\n\n\n\n\n\t\t\t*****please choose your entrance*****  ");
        printf("\n\n\t\t\t1.confirm users' info  \n\n\t\t\t2.confirm reported missing users  \n\n\t\t\t3.exit     \n\n");
        printf("\t\t\tinput your choice:");
        //compatiablyFlush();
        i = getchar();
        getchar();
        switch (i)
        {
        case '1':
            search();
            break;
        case '2':
            isLost();
            break;
        case '3':
            return;
        }
    } while (1);
}

void search()
{
    system("cls");
    date();
    userNum = Read();
    for (int i = 0; i < userNum && strcmp(user[i].accounts, "\0") != 0; i++)
        printf("\n\n\n\t\t\tuser account:%s\n\n\t\t\tuser password:%s\n\n\t\t\tuser name:%s\n\n\t\t\tbalance:%.2lf\n\n\t\t\tuser status:%d\n\n",
               user[i].accounts, user[i].password, user[i].name, user[i].prestore, user[i].isMissing);
    printf("\n\n\t\tfinished, input random key to return");
    getchar();
    return;
}

void isLost()
{
    system("cls");
    date();
    userNum = Read();
    printf("\n\n");
    for (int i = 0; i < userNum; i++)
    {
        if (user[i].isMissing == 1)
            printf("\n\n\n\t\t\tuser account:%s\n\n\t\t\tuser password:%s\n\n\t\t\tuser name:%s\n\n\t\tbalance:%.2lf\n\n\t\t\tuser status:%d\n\n",
                   user[i].accounts, user[i].password, user[i].name, user[i].prestore, user[i].isMissing);
    }
    printf("\n\n\t\t\tfinished, input random key to return");
    getchar();
    return;
}
