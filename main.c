#include "User.c"
#include "User.h"
int main()
{
    int i;
    date();
    aboutFile();
    system("cls");      //����
    system("color 3A"); //����̨��ɫ
    date();             //��ȡ����
    printf("\n\n\t\t$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
    printf("\t\t$                                                          $\n");
    printf("\t\t$             welcome to The international bank            $\n");
    printf("\t\t$                                                          $\n");
    printf("\t\t$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
    printf("\n\n\n\t\t\tPlease select your identity category:\n\n\t\t\t1.user   \n\n\t\t\t2.admin   \n\n\t\t\t3.exit\n\n");
    printf("\t\t\tplease choose:");
    fflush(stdin); //��ջ�����
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