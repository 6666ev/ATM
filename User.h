//
// Created by 96399 on 2018/12/16.
//

#ifndef FINALL_USER_H
#define FINALL_USER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
//最多容纳1000人(可以根据需求来修改）
#define N 1000
struct user
{
	char accounts[10];    //用户账号
	char password[10];    //用户密码
	char name[10];        //用户名字
	double prestore;      //现有金额
	int isMissing;        //挂失情况
};
void aboutFile();        //获取文件
void date();             //获取日期
void Main();             //主界面
void logIn();            //登录
void userInterface();    //用户主界面
void signIn();           //登录
void missAccount();      //注销账户
void userOperate(int n);      //用户操作界面
void deposit(int n);     //存款
void withdraw(int n);    //取款
void changePassword(int n);  //修改密码
void lostUser(int n);        //注销用户
void showInfo(int n);     //展示信息
void adminInterface();    //管理员界面
void adminOperate();     //管理员操作界面
void search();           //查看用户信息
void isLost();            //确认挂失
int checkPw(char *password); //检查密码合法性

#endif //FINALL_USER_H
