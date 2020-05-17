/*
文件：file.c

作者：李培生

内容：
从info文件中读取信息的函数；
更新info文件中信息并增加文件的函数；
检测用户库文件状态的函数；
向文件中写入链表的函数；
从文件中读出链表的函数。
*/




#include <stdio.h>
#include "file.h"




//返回目前图书库（借阅库）数量。如果当前无Info文件存在，会自动新建Info文件并设定数量为0，返回0。
int FileCheckInfo(void)
{
    int db_amount;
    FILE* fp_info = fopen("Info", "r");

    if (fp_info == NULL) //info文件不存在
    {
        fp_info = fopen("info", "w");
        fprintf(fp_info, "0");

        fclose(fp_info);

        return 0;
    }

    //info文件存在
    fscanf(fp_info, "%d", &db_amount);

    fclose(fp_info);

    return db_amount;
}




//将图书库（借阅库）数量增加1。并自动新建对应的图书库（借阅库）文件。返回当前库数量
int FileUpdateInfo(void)
{
    int db_amount = FileCheckInfo();
    int db_num = ++db_amount;

    char book_filename[MAX_FILE_NAME];
    char borrow_filename[MAX_FILE_NAME];

    sprintf(book_filename, "book%d", db_num);
    sprintf(borrow_filename, "borrow%d", db_num);

    FILE* fp_info = fopen("info", "w"); //打开info文件
    FILE* fp_book = fopen(book_filename, "wb"); //新建图书库文件
    FILE* fp_borrow = fopen(borrow_filename, "wb");; //新建借阅库文件

    fprintf(fp_info, "%d", db_amount); //将新的库数量写入info文件

    fclose(fp_info);
    fclose(fp_book);
    fclose(fp_borrow);

    return db_amount;
}