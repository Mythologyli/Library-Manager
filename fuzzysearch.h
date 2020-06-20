/*
文件：fuzzysearch.h

作者：古亚青

内容：
模糊匹配函数的声明；
在链表中对字符串进行模糊搜索的函数的声明；
在链表中对二位字符数组进行模糊搜索的函数的声明。
*/


#ifndef __FUZZYSEARCH_H__
#define __FUZZYSEARCH_H__




//在链表中对字符串进行模糊搜索，返回一个整形数组，存放符合搜索条件的结点的id序列
int* FuzzySearchNodeString(void* Node, int node_name, int string_name, char* string_value, int search_mode);




//在链表中对二维字符数组进行模糊搜索，返回一个整形数组，存放符合搜索条件的结点的id序列
//传入字符串与结点的二位字符数组的任一行满足模糊匹配条件，即认为该节点符合模糊搜索条件
int* FuzzySearchNodeStringArray(void* Node, int node_name, int string_array_name, char* string_value, int search_mode);


#endif