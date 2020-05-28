/*
文件：database.h

作者：古亚青、李培生

内容：
图书库、用户库、借阅库结构；
关于各种库的宏定义；
查找节点个数的函数的声明；
新增节点、删除节点、读取节点、更改节点、搜索节点五种基本函数的声明。
*/


#ifndef __DATABASE_H__
#define __DATABASE_H__


#include "date.h" //提供日期结构的定义




//链表类型名称
#define BOOK 0
#define USER 1
#define BORROW 2

//内容名称
#define BOOK_NAME 0
#define BOOK_KEYWORD 1
#define BOOK_WRITER 2
#define BOOK_PUBLISH 3
#define BOOK_DATE 4
#define BOOK_STATUS 5
#define USER_NAME 6
#define USER_SEX 7
#define USER_WORK 8
#define USER_STATUS 9
#define BOOK_ID 10
#define USER_ID 11
#define BORROW_ID 12
#define BORROW_DATE 13
#define RETURN_DATE 14
#define BORROW_STATUS 15

//性别
#define MALE 0
#define FEMALE 1

//节点状态
#define EXIST 0
#define DELETE 1

//搜索功能
#define SEARCH_EXIST 0
#define SEARCH_ALL 1

//字符串最大长度
#define MAX_LEN 15



//图书库结构
struct BookNode
{
	int book_id; //从1开始递增，具有唯一性

	char book_name[MAX_LEN];//书名
	char book_keyword[5][MAX_LEN];//关键词
	char book_writer[3][MAX_LEN];//作者
	char book_publish[MAX_LEN];//出版社
	struct Date book_date; //出版日期

	int book_status; //图书状态（是否删除）

	struct BookNode* next;
};

//用户库结构
struct UserNode
{
	int user_id; //从1开始递增，具有唯一性

	char user_name[MAX_LEN]; //用户名
	int user_sex; //性别
	char user_work[MAX_LEN]; //工作单位

	int user_status; //用户状态（是否删除）

	struct UserNode* next;
};

//借阅库结构
struct BorrowNode
{
	int borrow_id; //从1开始递增，具有唯一性

	int book_id; //图书id
	int user_id; //用户id
	struct Date borrow_date; //借阅日期
	struct Date return_date; //应还日期

	int borrow_status; //借阅状态（是否删除，删除即表示已归还）

	struct BorrowNode* next;
};




//返回节点的个数
int CheckBookAmount(struct BookNode* node, int check_mode);
int CheckUserAmount(struct UserNode* node, int check_mode);
int CheckBorrowAmount(struct BorrowNode* node, int check_mode);




//新增一个节点
struct BookNode* AddBookNode(struct BookNode* node, struct BookNode data);
struct UserNode* AddUserNode(struct UserNode* node, struct UserNode data);
struct BorrowNode* AddBorrowNode(struct BorrowNode* node, struct BorrowNode data);




//删除一个节点，成功则返回1，若不存在该id则返回0
int DeleteNode(void* Node, int node_name, int id);




//链表整型内容的读取
int ReadNodeInt(void* Node, int node_name, int id, int int_name);

//链表单个字符串内容的读取
char* ReadNodeString(void* Node, int node_name, int id, int string_name);

//链表字符串数组的读取
char** ReadNodeStringArray(void* Node, int node_name, int id, int string_array_name);

//链表日期的读取
struct Date ReadNodeDate(void* Node, int node_name, int id, int date_name);




//链表整型内容的更改
int ChangeNodeInt(void* Node, int node_name, int id, int int_name, int int_value);

//链表单个字符串内容的更改
int ChangeNodeString(void* Node, int node_name, int id, int string_name, char* string_value);

//链表字符串数组的更改
int ChangeNodeStringArray(void* Node, int node_name, int id, int string_array_name, char** string_array_value);

//链表日期的更改
int ChangeNodeDate(void* Node, int node_name, int id, int date_name, struct Date date_value);





//链表整型内容的搜索
//返回一个存放搜索结果的整型数组，以0作为结束标志，例如，id为1,3,7的结点符合条件，则返回{1，3，7，0}
int* SearchNodeInt(void* Node, int node_name, int int_name, int int_value, int search_mode);

//链表单个字符串内容的搜索
int* SearchNodeString(void* Node, int node_name, int string_name, char* string_value, int search_mode);

//链表字符串数组的搜索
int* SearchNodeStringArray(void* Node, int node_name, int string_array_name, char** string_array_value, int search_mode);

//链表日期的搜索
int* SearchNodeDate(void* Node, int node_name, int date_name, struct Date date_value, int search_mode);




#endif