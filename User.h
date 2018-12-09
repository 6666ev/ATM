//
// Created by  on 2018/12/3.
//

#ifndef ATM_USER_H
#define ATM_USER_H
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define N 10000

struct user
{
    char acnum[9];    //用户账号
    char pswdnum[7];  //用户密码
    char name[20];    //用户名字
    //char idnum[20];   //用户身份证
    //char phnum[15];   //用户手机号
    //char adrss[105];  //用户地址
    //char cardnum[20]; //用户银行卡号
    double money;      //现有金额
    int ero;          //挂失情况
} u[N];

void aboutFile();         //文件准备
void userInterface();     //用户操作界面
void adminInterface();    //管理员登录界面
void logIn();             //用户登录
void signIn();            //用户注册
void missAccount();       //用户挂失
void userOperate(int);    //用户登录后操作界面
void deposit(int);        //存款
void withdraw(int);       //取款
void changePassword(int); //修改密码
void lostUser(int);       //用户注销
void showInfo(int);       //用户信息查询
void adminOperate();      //管理员操作界面
void isLost();            //显示挂失的用户并确认
void search();            //显示用户信息
void date();              //显示当前的时间日期
int checkAdd(char addmoney[]);
int checkReduce(char reducemoney[], int j);
char ac[11], pass[10];
char account[11], password[10];
#endif //ATM_USER_H
