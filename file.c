/*
文件：file.c

作者：李培生

内容：
从info文件中读取信息的函数；
从borrowday文件中读取当前设置的借阅天数的函数；
从borrowtime文件中读取当前设置的最大借阅次数的函数；
向borrowday文件写入当前设置的借阅天数的函数；
向borrowtime文件写入当前设置的最大借阅次数的函数；
更新info文件中信息并增加文件的函数；
检测用户库文件状态的函数；
向文件中写入链表的函数；
从文件中读出链表的函数。
*/




#include <stdio.h>
#include <stdlib.h>


#include "database.h" //提供各种库结构的定义
#include "date.h" //提供日期结构的定义


#include "file.h"




//返回目前图书库（借阅库）数量。如果当前无Info文件存在，会自动新建Info文件并设定数量为0，返回0
int FileCheckInfo(void)
{
    int db_amount;
    FILE* fp_info = fopen("info", "r");

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




//返回当前借阅天数。如果当前无borrowday文件存在，会自动新建borrowday文件并设定数量为30，返回30
int FileCheckBorrowDay(void)
{
    int borrow_day;
    FILE* fp_borrow_day = fopen("borrowday", "r");

    if (fp_borrow_day == NULL) //borrowday文件不存在
    {
        fp_borrow_day = fopen("borrowday", "w");
        fprintf(fp_borrow_day, "30");

        fclose(fp_borrow_day);

        return 30;
    }

    //borrowday文件存在
    fscanf(fp_borrow_day, "%d", &borrow_day);

    fclose(fp_borrow_day);

    return borrow_day;
}




//返回当前最大借阅次数。如果当前无borrowtime文件存在，会自动新建borrowtime文件并设定数量为5，返回5
int FileCheckBorrowTime(void)
{
    int borrow_time;
    FILE* fp_borrow_time = fopen("borrowtime", "r");

    if (fp_borrow_time == NULL) //borrowtime文件不存在
    {
        fp_borrow_time = fopen("borrowtime", "w");
        fprintf(fp_borrow_time, "5");

        fclose(fp_borrow_time);

        return 5;
    }

    //borrowtime文件存在
    fscanf(fp_borrow_time, "%d", &borrow_time);

    fclose(fp_borrow_time);

    return borrow_time;
}




//写入当前借阅天数
void FileWriteBorrowDay(int borrow_day)
{
    FILE* fp_borrow_day = fopen("borrowday", "w");

    fprintf(fp_borrow_day, "%d", borrow_day);

    fclose(fp_borrow_day);
}




//写入当前最大借阅次数
void FileWriteBorrowTime(int borrow_time)
{
    FILE* fp_borrow_time = fopen("borrowtime", "w");

    fprintf(fp_borrow_time, "%d", borrow_time);

    fclose(fp_borrow_time);
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




//检测用户库文件状态。若存在，返回1；若不存在，自动新建用户库文件，返回0
void FileCheckUser(void)
{
    FILE* fp_user = fopen("user", "rb");

    if (fp_user == NULL) //文件不存在
    {
        fp_user = fopen("user", "wb");

        fclose(fp_user);

        return 0;
    }

    //文件存在
    fclose(fp_user);

    return 1;
}




//向文件中写入图书库链表,成功则返回1。若要写入的链表为空，返回0
int FileWriteBook(struct BookNode* node, int db_num)
{
    if (node == NULL) //写入的链表为空
        return 0;
    
    //写入的链表不为空
    int node_size = sizeof(struct BookNode);

    char book_filename[MAX_FILE_NAME];
    sprintf(book_filename, "book%d", db_num);

    FILE* fp_book = fopen(book_filename, "wb");

    struct BookNode* p = node;

    while (p)
    {
        fwrite(p, node_size, 1, fp_book);
        p = p->next;
    }

    fclose(fp_book);

    return 1;
}




//向文件中写入用户库链表,成功则返回1。若要写入的链表为空，返回0
int FileWriteUser(struct UserNode* node)
{
    if (node == NULL) //写入的链表为空
        return 0;
    
    //写入的链表不为空
    int node_size = sizeof(struct UserNode);

    FILE* fp_user = fopen("user", "wb");

    struct UserNode* p = node;

    while (p)
    {
        fwrite(p, node_size, 1, fp_user);
        p = p->next;
    }

    fclose(fp_user);

    return 1;
}




//向文件中写入借阅库链表,成功则返回1。若要写入的链表为空，返回0
int FileWriteBorrow(struct BorrowNode* node, int db_num)
{
    if (node == NULL) //写入的链表为空
        return 0;
    
    //写入的链表不为空
    int node_size = sizeof(struct BorrowNode);

    char borrow_filename[MAX_FILE_NAME];
    sprintf(borrow_filename, "borrow%d", db_num);

    FILE* fp_borrow = fopen(borrow_filename, "wb");

    struct BorrowNode* p = node;

    while (p)
    {
        fwrite(p, node_size, 1, fp_borrow);
        p = p->next;
    }

    fclose(fp_borrow);

    return 1;
}




//从文件中读出图书库链表。若文件为空，返回NULL
struct BookNode* FileReadBook(int db_num)
{
    int node_size = sizeof(struct BookNode);

    char book_filename[MAX_FILE_NAME];
    sprintf(book_filename, "book%d", db_num);

    FILE* fp_book = fopen(book_filename, "rb");

    fseek(fp_book, 0L, SEEK_END);
    if (ftell(fp_book) == 0) //文件为空
    {
        return NULL;
    }

    //文件不为空
    fseek(fp_book, 0L, SEEK_SET);
    struct BookNode* head = NULL;
    struct BookNode* p = NULL;

    head = (struct BookNode*)malloc(node_size);
    fread(head, node_size, 1, fp_book); //读出头结点

    p = head;
    while (p->next) //依次读出并链接之后的结点
    {
        p->next = (struct BookNode*)malloc(node_size);
        fread(p->next, node_size, 1, fp_book);
        p = p->next;
    }

    fclose(fp_book);

    return head;
}




//从文件中读出用户库链表。若文件为空，返回NULL
struct UserNode* FileReadUser(void)
{
    int node_size = sizeof(struct UserNode);

    FILE* fp_user = fopen("user", "rb");

    fseek(fp_user, 0L, SEEK_END);
    if (ftell(fp_user) == 0) //文件为空
    {
        return NULL;
    }

    //文件不为空
    fseek(fp_user, 0L, SEEK_SET);
    struct UserNode* head = NULL;
    struct UserNode* p = NULL;

    head = (struct UserNode*)malloc(node_size);
    fread(head, node_size, 1, fp_user); //读出头结点

    p = head;
    while (p->next) //依次读出并链接之后的结点
    {
        p->next = (struct UserNode*)malloc(node_size);
        fread(p->next, node_size, 1, fp_user);
        p = p->next;
    }

    fclose(fp_user);

    return head;
}




//从文件中读出借阅库链表。若文件为空，返回NULL
struct BorrowNode* FileReadBorrow(int db_num)
{
    int node_size = sizeof(struct BorrowNode);

    char borrow_filename[MAX_FILE_NAME];
    sprintf(borrow_filename, "borrow%d", db_num);

    FILE* fp_borrow = fopen(borrow_filename, "rb");

    fseek(fp_borrow, 0L, SEEK_END);
    if (ftell(fp_borrow) == 0) //文件为空
    {
        return NULL;
    }

    //文件不为空
    fseek(fp_borrow, 0L, SEEK_SET);
    struct BorrowNode* head = NULL;
    struct BorrowNode* p = NULL;

    head = (struct BorrowNode*)malloc(node_size);
    fread(head, node_size, 1, fp_borrow); //读出头结点

    p = head;
    while (p->next) //依次读出并链接之后的结点
    {
        p->next = (struct BorrowNode*)malloc(node_size);
        fread(p->next, node_size, 1, fp_borrow);
        p = p->next;
    }

    fclose(fp_borrow);

    return head;
}