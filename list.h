/*
文件：list.h

作者：李培生

内容：
控制显示内容的宏定义；
列表显示图书的函数的声明；
列表显示用户的函数的声明；
列表显示借阅的函数的声明；
设置显示内容的函数的声明；
列表显示的函数的声明。
*/




//控制显示内容的宏定义
#define LIST_NO 0
#define LIST_BOOK 1
#define LIST_USER 2
#define LIST_BORROW 3




//列表显示图书
void DrawListBook(void);

//列表显示用户
void DrawListUser(void);

//列表显示借阅
void DrawListBorrow(void);




//设置显示内容
void SetList(int set_list_content, int* set_list);

//列表显示
void DrawList(void);