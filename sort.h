/*
文件：sort.h

作者：古亚青

内容：
关于排序为升序或降序的宏定义；
对图书排序的函数的声明；
对用户排序的函数的声明；
对借阅排序的函数的声明。
*/


#ifndef __SORT_H__
#define __SORT_H__


//关于排序为升序或降序的宏定义
#define ASCENDING 0 //升序
#define DESCENDING 1 //降序




//对图书排序
int* SortBookNode(struct BookNode* Node, int node_name, int sort_mode);

//对用户排序
int* SortUserNode(struct UserNode* Node, int node_name, int sort_mode);

//对借阅排序
int* SortBorrowNode(struct BorrowNode* Node, int node_name, int sort_mode);

#endif