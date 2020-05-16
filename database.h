/*
文件：database.h

作者：古亚青、李培生

内容：
图书库、用户库、借阅库结构；
关于各种库的宏定义；
用于新增一个库的函数的声明。
新增节点、删除节点、读取节点、更改节点、搜索节点五种基本函数的声明。
*/




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
#define BORROW_DATE 12
#define RETURN_DATE 13
#define BORROW_STATUS 14

//性别
#define MALE 0
#define FEMALE 1

//节点状态
#define EXIST 0
#define DELETE 1

//搜索功能
#define SEARCH_EXIST 0
#define SEARCH_ALL 1




//图书库结构
struct BookNode
{
    int book_id; //从1开始递增，具有唯一性

    string book_name; //书名
    string book_keyword[5]; //关键词
    string book_writer[3]; //作者
    string book_publish; //出版社
    struct Date book_date; //出版日期

    int book_status; //图书状态（是否删除）

    struct BookNode *next;
};

//用户库结构
struct UserNode
{
    int user_id; //从1开始递增，具有唯一性

    string user_name; //用户名
    int user_sex; //性别
    string user_work; //工作单位

    int user_status; //用户状态（是否删除）

    struct UserNode *next;
};

//借阅库结构
struct BorrowNode
{
    int borrow_id; //从1开始递增，具有唯一性

    int book_id; //图书id
    int user_id; //用户id
    struct Date borrow_date; //借阅日期
    struct Date return_date; //应还日期
    
    int borrow_status; //借阅状态（是否删除）

    struct BorrowNode *next; 
};




//新增一个库
void* AddDatabase(int node_name);




//新增一个节点
int AddBookNode(...);
int AddUserNode(...);
int AddBorrowNode(...);




//删除一个节点
int DeleteNode(void* Node, int node_name, int id);




//链表整型内容的读取
int ReadNodeInt(void* Node, int node_name, int id, int int_name);

/*链表单个字符串内容的读取*/
string ReadNodeString(void* Node, int node_name, int id, int string_name);

/*链表字符串数组的读取*/
string* ReadNodeStringArray(void* Node, int node_name, int id, int string_array_name);

/*链表日期的读取*/
struct Date ReadNodeDate(void* Node, int node_name, int id, int date_name);




//链表整型内容的更改
int ChangeNodeInt(void* Node, int node_name, int id, int int_name, int int_value);

/*链表单个字符串内容的更改*/
int ChangeNodeString(void* Node, int node_name, int id, int string_name, string string_value);

/*链表字符串数组的更改*/
int ChangeNodeStringArray(void* Node, int node_name, int id, int string_array_name, string* string_array_value);

/*链表日期的更改*/
int ChangeNodeDate(void* Node, int node_name, int id, int date_name, struct Date date_value);




//链表整型内容的搜索
//搜索链表并返回一个整型数组。例如，搜索得出id为1,3,7的符合条件，则返回数组{1,3,7,0}
int* SearchNodeInt(void* Node, int node_name, int int_name, int int_value, int search_mode);

/*链表单个字符串内容的搜索*/
int* SearchNodeString(void* Node, int node_name, int string_name, string string_value, int search_mode);

/*链表字符串数组的搜索*/
int* SearchNodeStringArray(void* Node, int node_name, int string_array_name, string* string_array_value, int search_mode);

/*链表日期的搜索*/
int* SearchNodeDate(void* Node, int node_name, int date_name, struct Date date_value, int search_mode);