#include "User.h"
#ifdef __clang__
	#include "User.c" 
#endif
//解决6ev的linker问题

void setColor(unsigned short ForeColor, unsigned short BackGroundColor) {
    HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);//获取当前窗口句柄
    SetConsoleTextAttribute(handle,ForeColor+BackGroundColor*0x10);//设置颜色
}

void SetPos(int x,int y)
{
    COORD pos;
    HANDLE handle;
    pos.X=x;
    pos.Y=y;
    handle=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(handle,pos);
}
int main()
{
    setColor(10,0);
    int i;
    date();
    aboutFile();
    system("cls");
    system("color 31");
    date();
    SetPos(30,10);
    setColor(10,8);
    printf("wel");
    setColor(1,8);
    printf("come");
    setColor(4,8);
    printf(" to");
    setColor(5,8);
    printf(" The");
    setColor(14,8);
    printf(" inter");
    setColor(6,13);
    printf("nation");
    setColor(10,8);
    printf("nal");
    setColor(12,8);
    printf(" bank");
    setColor(1,8);
    printf("\n\n\n\t\t\tPlease select your identity category:\n\n\t\t\t1.user   \n\n\t\t\t2.admin   \n\n\t\t\t3.exit\n\n");
    printf("\t\t\tplease choose:");
    fflush(stdin);
    scanf("%d", &i);
    switch (i)
    {
    case 1:
        userInterface();
        break;
    case 2:
        adminInterface();
        break;
    case 3:
        exit(0);
    }
    return 0;
}