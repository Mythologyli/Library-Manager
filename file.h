/*
文件：file.h

作者：

内容：
最大文件名长度的宏定义；
用于从info文件中读取信息的函数的声明；
用于更新info文件中信息并增加文件的函数的声明；
用于检测用户库文件状态的函数的声明；
用于向文件中写入链表的函数的声明；
用于从文件中读出链表的函数的声明。
*/


#ifndef __FILE_H__
#define __FILE_H__







//最大文件名长度的宏定义
#define MAX_FILE_NAME 10




//返回目前图书库（借阅库）数量。如果当前无Info文件存在，会自动新建Info文件并设定数量为0，返回0。
int FileCheckInfo(void);

int FileCheckBorrowDay(void);
int FileCheckBorrowTime(void);
void FileWriteBorrowDay(int borrow_day);
void FileWriteBorrowTime(int borrow_time);



//将图书库（借阅库）数量增加1。并自动新建对应的图书库（借阅库）文件。返回当前库数量
int FileUpdateInfo(void);




//检测用户库文件状态。若存在，返回1；若不存在，自动新建用户库文件，返回0
void FileCheckUser(void);




//向文件中写入链表,成功则返回1。若要写入的链表为空，返回0
int FileWriteBook(struct BookNode* node, int db_num);
int FileWriteUser(struct UserNode* node);
int FileWriteBorrow(struct BorrowNode* node, int db_num);




//从文件中读出链表。若文件为空，返回NULL
struct BookNode* FileReadBook(int db_num);
struct UserNode* FileReadUser(void);
struct BorrowNode* FileReadBorrow(int db_num);




#endif