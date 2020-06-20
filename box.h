/*
文件：box.h

作者：李培生

内容：
控制显示内容的宏定义；
设置显示内容的函数的声明；
显示交互窗口的函数的声明。
*/


#ifndef __BOX_H__
#define __BOX_H__


//控制显示内容的宏
#define BOX_NO 0

#define REGISTER 1
#define USER_LOG 2
#define ADMIN_LOG 3

#define OPEN_DB 4
#define ADD_DB 5

#define ADD_BOOK 6
#define EDIT_BOOK 7
#define DELETE_BOOK 8

#define PASS 9
#define EDIT_USER_ADMIN 10
#define EDIT_USER_USER 11
#define DELETE_USER 12

#define BORROW_BOOK_ADMIN 13
#define BORROW_BOOK_USER 14
#define RETURN_BOOK_ADMIN 15
#define RETURN_BOOK_USER 16

#define SEARCH_BOOK_ID 17
#define SEARCH_BOOK_NAME 18
#define SEARCH_BOOK_WRITER 19
#define SEARCH_BOOK_KEYWORD 20

#define SEARCH_USER_ID 21
#define SEARCH_USER_NAME 22
#define SEARCH_USER_WORK 23

#define STAT_AMOUNT 24
#define STAT_FREQ 25

#define SET_BORROW_DAY 26
#define SET_BORROW_TIME 27

#define VERSION 28
#define HELP 29




//设置显示内容
void SetBox(int set_box_content);




//显示交互窗口
void DrawBox(void);


#endif