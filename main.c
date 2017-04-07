/*
Linux操作系统上
获得目标文件的权限，可修改目标文件的权限和所有者。
*/

#include <sys/types.h> //基本系统数据类型。
#include <sys/stat.h>  //文件状态。
#include <unistd.h>    //unix/linux系统调用。
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void changeMod(char *filename); //修改文件权限。
void changeOwn(char *filename); //修改文件所有者。

int main(int argc, char *argv[])
//argc是参数个数，argv[0]是本程序的可执行文件名，argv[1]是目标文件名。
{
    while (1)
    {
        int statret = -1;
        struct stat buf;
        memset(&buf, 0, sizeof(struct stat)); //初始化buf。

        statret = stat(argv[1], &buf); //获取文件信息，保存到结构体中。
        if (statret < 0)               //未获取到文件信息。
        {
            perror("open");
            exit(-1);
        }

        //查看文件权限。
        switch (S_IRWXU & buf.st_mode) //用位标志判断文件权限。
        {
        case S_IRUSR | S_IWUSR | S_IXUSR:
            printf("Owner of %s has rwx permission.\n", argv[1]);
            break;
        case S_IWUSR:
            printf("Owner of %s has w permission.\n", argv[1]);
            break;
        case S_IXUSR:
            printf("Owner of %s has x permission.\n", argv[1]);
            break;
        case S_IRUSR:
            printf("Owner of %s has r permission.\n", argv[1]);
            break;
        case S_IWUSR | S_IXUSR:
            printf("Owner of %s has wx permission.\n", argv[1]);
            break;
        case S_IRUSR | S_IXUSR:
            printf("Owner of %s has rx permission.\n", argv[1]);
            break;
        case S_IRUSR | S_IWUSR:
            printf("Owner of %s has rw permission.\n", argv[1]);
            break;
        default:
            printf("Owner of %s has no permission.\n", argv[1]);
        }

        switch (S_IRWXG & buf.st_mode) //用位标志判断文件权限。
        {
        case S_IRGRP | S_IWGRP | S_IXGRP:
            printf("Group of %s has rwx permission.\n", argv[1]);
            break;
        case S_IWGRP:
            printf("Group of %s has w permission.\n", argv[1]);
            break;
        case S_IXGRP:
            printf("Group of %s has x permission.\n", argv[1]);
            break;
        case S_IRGRP:
            printf("Group of %s has r permission.\n", argv[1]);
            break;
        case S_IWGRP | S_IXGRP:
            printf("Group of %s has wx permission.\n", argv[1]);
            break;
        case S_IRGRP | S_IXGRP:
            printf("Group of %s has rx permission.\n", argv[1]);
            break;
        case S_IRGRP | S_IWGRP:
            printf("Group of %s has rw permission.\n", argv[1]);
            break;
        default:
            printf("Group of %s has no permission.\n", argv[1]);
        }

        switch (S_IRWXO & buf.st_mode) //用位标志判断文件权限。
        {
        case S_IROTH | S_IWOTH | S_IXOTH:
            printf("Others not in the group have rwx permission.\n");
            break;
        case S_IWOTH:
            printf("Others not in the group have w permission.\n");
            break;
        case S_IXOTH:
            printf("Others not in the group have x permission.\n");
            break;
        case S_IROTH:
            printf("Others not in the group have r permission.\n");
            break;
        case S_IWOTH | S_IXOTH:
            printf("Others not in the group have wx permission.\n");
            break;
        case S_IROTH | S_IXOTH:
            printf("Others not in the group have rx permission.\n");
            break;
        case S_IROTH | S_IWOTH:
            printf("Others not in the group have rw permission.\n");
            break;
        default:
            printf("Others not in the group have no permission.\n");
        }
        //菜单。
        printf("1.Change the permission.\n");
        printf("2.Change the owner.\n");
        printf("3.Exit.\n");
        int choice = 0; //菜单选择。
        scanf("%d", &choice);
        char ch;
        while ((ch = getchar()) != '\n' && ch != EOF);//清除输入缓存。
        if (choice >= 1 && choice <= 3)
        {
            switch (choice)
            {
            case 1:
                changeMod(argv[1]);
                break;
            case 2:
                changeOwn(argv[1]);
                break;
            case 3:
                return 0;
            default:
                break;
            }
        }
        else
            continue;
    }
}

void changeMod(char *filename) //修改文件权限。
{
    printf("Please enter an octal number to modify the permission of this file.\n");
    int permission = 01000;       //八进制。
    if (scanf("%o", &permission)) //八进制%o
    {
        char ch;
        while ((ch = getchar()) != '\n' && ch != EOF);//清除输入缓存。
        if (permission >= 00 && permission <= 0777)
        {
            int chmodret = chmod(filename, permission); //chmod成功返回0，失败返回-1。
            if (chmodret == 0)
            {
                printf("The permission of the file has been changed.\n\n");
                return;
            }
            else if (chmodret < 0)
            {
                perror("change the permission");
                printf("\n");
                return;
            }
        }
        else
        {
            printf("Invalid operrand.\n\n");
            return;
        }
    }
    else
    {
        char ch;
        while ((ch = getchar()) != '\n' && ch != EOF);//清除输入缓存。
        printf("Invalid operrand.\n\n");
        return;
    }
}

void changeOwn(char *filename) //修改文件所有者。
{
    printf("Please enter the id of the owner and its group.\n");
    int owner = 10000; //10000是个不存在的id。
    int group = 10000;
    if (scanf("%d%d", &owner, &group) == 2)
    {
        char ch;
        while ((ch = getchar()) != '\n' && ch != EOF);//清除输入缓存。
        int chownret = chown(filename, owner, group); //chown成功返回0，失败返回-1。
        if (chownret == 0)
        {
            printf("The owner and group of the file has been changed.\n\n");
            return;
        }
        else
        {
            perror("change the owner and group");
            printf("\n");
            return;
        }
    }
    else
    {
        char ch;
        while ((ch = getchar()) != '\n' && ch != EOF);//清除输入缓存。
        printf("Invalid operrand.\n\n");
        return;
    }
}