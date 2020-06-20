/*
文件：list.h

作者：李培生

内容：
控制显示内容的宏定义；
设置显示内容的函数的声明；
列表显示的函数的声明。
*/


#ifndef __LIST_H__
#define __LIST_H__


//控制显示内容的宏定义
#define LIST_NO 0
#define LIST_BOOK 1
#define LIST_USER 2
#define LIST_BORROW_ADMIN 3
#define LIST_BORROW_USER 4




//设置显示内容
void SetList(int set_list_content, int* set_list);




//列表显示
void DrawList(void);


#endif