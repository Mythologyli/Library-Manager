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