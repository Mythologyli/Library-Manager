/*
文件：list.c

作者：李培生

内容：
控制列表显示的内容的整型全局变量；
id列表，整型指针全局变量；
列表显示图书的函数；
列表显示用户的函数；
列表显示借阅的函数；
设置显示内容的函数；
列表显示的函数。
*/




#include "imgui.h"
#include "graphics.h"
#include "extgraph.h"


#include "database.h"
#include "date.h"
#include "list.h"




extern struct BookNode* book_head;
extern struct UserNode* user_head;
extern struct BorrowNode* borrow_head;
extern double winheight;




//全局变量
int list_content = LIST_NO; //控制列表显示的内容
int* list; //id列表，末位为0




//列表显示图书
void DrawListBook(void)
{
    //图形相关
    double x = 0.2;
    double y = winheight - GetFontHeight() * 10;
    double dx = 0.6;
    double dy = GetFontHeight() * 1.5;

    drawLabel
    (
        x, 
        y, 
        "ID    Name            Key1      Key2      Key3      Key4      Key5      Writer1  Writer2   Writer3   Publish                Year       Month    Day"
    );
    
    for (int i = 0, j = 1; list[i] != 0; i++) //按列显示
    {
        if (ReadNodeInt(book_head, BOOK, list[i], BOOK_STATUS) == DELETE) //跳过已删除结点
            continue;
        
        char temp_str[5]; //满足itoa函数的参数需要
        char (*p_keyword)[MAX_LEN] = ReadNodeStringArray(book_head, BOOK, list[i], BOOK_KEYWORD);
        char (*p_writer)[MAX_LEN] = ReadNodeStringArray(book_head, BOOK, list[i], BOOK_WRITER);

        //ID
        drawLabel(x, y - j * dy, itoa(list[i], temp_str, 10));

        //书名
        drawLabel(x + dx * 0.5, y - j * dy, ReadNodeString(book_head, BOOK, list[i], BOOK_NAME));

        //图书关键词
        drawLabel(x + dx * 2, y - j * dy, p_keyword[0]);

        drawLabel(x + dx * 3, y - j * dy, p_keyword[1]);

        drawLabel(x + dx * 4, y - j * dy, p_keyword[2]);

        drawLabel(x + dx * 5, y - j * dy, p_keyword[3]);

        drawLabel(x + dx * 6, y - j * dy, p_keyword[4]);

        //图书作者
        drawLabel(x + dx * 7, y - j * dy, p_writer[0]);

        drawLabel(x + dx * 8, y - j * dy, p_writer[1]);

        drawLabel(x + dx * 9, y - j * dy, p_writer[2]);

        //出版社
        drawLabel(x + dx * 10, y - j * dy, ReadNodeString(book_head, BOOK, list[i], BOOK_PUBLISH));

        //出版日期
        struct Date date = ReadNodeDate(book_head, BOOK, list[i], BOOK_DATE);

        drawLabel(x + dx * 12, y - j * dy, itoa(date.year, temp_str, 10));
    
        drawLabel(x + dx * 13, y - j * dy, itoa(date.month, temp_str, 10));

        drawLabel(x + dx * 14, y - j * dy, itoa(date.day, temp_str, 10));
    
        j++;
    }
}




//列表显示用户
void DrawListUser(void)
{
    //图形相关
    double x = 0.2;
    double y = winheight - GetFontHeight() * 10;
    double dx = 0.6;
    double dy = GetFontHeight() * 1.5;

    drawLabel
    (
        x, 
        y, 
        "ID    Name            Sex                       Workplace"
    );

    for (int i = 0, j = 1; list[i] != 0; i++) //按列显示
    {
        if (ReadNodeInt(user_head, USER, list[i], USER_STATUS) == DELETE) //跳过已删除结点
            continue;
        
        char temp_str[5]; //满足itoa函数的参数需要

        //ID
        drawLabel(x, y - j * dy, itoa(list[i], temp_str, 10));

        //用户名
        drawLabel(x + dx * 0.5, y - j * dy, ReadNodeString(user_head, USER, list[i], USER_NAME));

        //性别
        drawLabel(x + dx * 2, y - j * dy, ReadNodeInt(user_head, USER, list[i], USER_SEX) == MALE ? "Male" : "Female");

        //工作单位
        drawLabel(x + dx * 4, y - j * dy, ReadNodeString(user_head, USER, list[i], USER_WORK));

        j++;
    }
}




//列表显示借阅
void DrawListBorrow(void)
{
    //图形相关
    double x = 0.2;
    double y = winheight - GetFontHeight() * 10;
    double dx = 0.6;
    double dy = GetFontHeight() * 1.5;

    drawLabel
    (
        x, 
        y, 
        "ID           Book      User       Year      Month     Day        Year      Month     Day        Total      Status"
    );

    for (int i = 0, j = 1; list[i] != 0; i++) //按列显示
    {
        char temp_str[5]; //满足itoa函数的参数需要

        //ID
        drawLabel(x, y - j * dy, itoa(list[i], temp_str, 10));

        //被借阅的书名
        drawLabel(x + dx, y - j * dy, ReadNodeString(book_head, BOOK, ReadNodeInt(borrow_head, BORROW, list[i], BOOK_ID), BOOK_NAME));

        //借阅人名称
        drawLabel(x + dx * 2, y - j * dy, ReadNodeString(user_head, USER, ReadNodeInt(borrow_head, BORROW, list[i], USER_ID), USER_NAME));

        //借阅日期
        struct Date borrow_date = ReadNodeDate(borrow_head, BORROW, list[i], BORROW_DATE);

        drawLabel(x + dx * 3, y - j * dy, itoa(borrow_date.year, temp_str, 10));

        drawLabel(x + dx * 4, y - j * dy, itoa(borrow_date.month, temp_str, 10));

        drawLabel(x + dx * 5, y - j * dy, itoa(borrow_date.day, temp_str, 10));
        
        //应还日期
        struct Date return_date = ReadNodeDate(borrow_head, BORROW, list[i], RETURN_DATE);

        drawLabel(x + dx * 6, y - j * dy, itoa(return_date.year, temp_str, 10));

        drawLabel(x + dx * 7, y - j * dy, itoa(return_date.month, temp_str, 10));

        drawLabel(x + dx * 8, y - j * dy, itoa(return_date.day, temp_str, 10));

        //借阅天数
        drawLabel(x + dx * 9, y - j * dy, itoa(DateInterval(borrow_date, return_date), temp_str, 10));

        //借阅状态
        drawLabel(x + dx * 10, y - j * dy, ReadNodeInt(borrow_head, BORROW, list[i], BORROW_STATUS) == EXIST ? "NOT RETURNED" : "RETURNED");
        
        j++;
    }
}




//设置显示内容
void SetList(int set_list_content, int* set_list)
{
    list_content = set_list_content;
    list = set_list;
}




//列表显示
void DrawList(void)
{
    switch (list_content)
    {
    case LIST_BOOK: DrawListBook(); break;
    case LIST_USER: DrawListUser(); break;
    case LIST_BORROW: DrawListBorrow();
    }
}