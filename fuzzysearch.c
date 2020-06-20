/*
文件：fuzzysearch.c

作者：

内容：
模糊匹配函数；
在链表中对字符串进行模糊搜索的函数的声明；
在链表中对二位字符数组进行模糊搜索的函数的声明。
*/




#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "database.h" //提供各种库结构的定义


#include "fuzzysearch.h"




//模糊匹配，若传入的关键词key是字符串str的子片段，则认为符合匹配条件，返回1；否则返回0
int FuzzyCompare(char* str, char* key)
{
	if (key == NULL || str == NULL)
		return 0;

	int key_len = strlen(key);
	int str_len = strlen(str);

	if (key_len > str_len)
		return 0;
	
	char(*p)[MAX_LEN] = NULL;//定义数组指针
	p = (char(*)[MAX_LEN])calloc(str_len - key_len + 1, sizeof(char[MAX_LEN]));//分配内存空间
	
	//将str字符串中每一个长度与key相等的子片段取出，存入p指向的内存空间
	int k = 0;
	for (int i = 0; i <= str_len - key_len; i++)
	{
		k = 0;
		for (int j = i; j < i + key_len; j++)
		{
			p[i][k++] = str[j];
		}
	}

	//将关键词key与str中取出的每一个子片段相比较
	int flag = 0;
	for (int i = 0; i <= str_len - key_len; i++)
	{
		if (strcmp(key, p[i]) == 0)
		{
			flag = 1;
			break;
		}
	}

	free(p);//释放内存空间

	return flag;
}




// 在链表中对字符串进行模糊搜索，返回一个整形数组，存放符合搜索条件的结点的id序列
int* FuzzySearchNodeString(void* Node, int node_name, int string_name, char* string_value, int search_mode)
{
	int* L = NULL, i = 0;

	switch (node_name)
	{
		//在图书链表中查找
	case BOOK:
	{
		L = (int*)calloc(CheckBookAmount(Node, SEARCH_ALL) + 1, sizeof(int));//开辟数组空间存放查找结果

		struct  BookNode* p = (struct BookNode*)Node;
		switch (string_name)
		{
			//按书名查找
		case BOOK_NAME:
		{
			if (search_mode == SEARCH_ALL)  //在全部图书中查找
			{
				while (p != NULL)
				{
					if (FuzzyCompare(p->book_name, string_value))
					{
						L[i++] = p->book_id;
					}
					p = p->next;
				}
			}
			else if (search_mode == SEARCH_EXIST)  //在现有图书中查找
			{
				while (p != NULL)
				{
					if (FuzzyCompare(p->book_name, string_value) == 1 && p->book_status == EXIST)
					{
						L[i++] = p->book_id;
					}
					p = p->next;
				}
			}
		}
		break;

		//按出版社查找
		case BOOK_PUBLISH:
		{
			if (search_mode == SEARCH_ALL)  //在全部图书中查找
			{
				while (p != NULL)
				{
					if (FuzzyCompare(p->book_publish, string_value))
					{
						L[i++] = p->book_id;
					}
					p = p->next;
				}
			}
			else if (search_mode == SEARCH_EXIST)  //在现有图书中查找
			{
				while (p != NULL)
				{
					if (FuzzyCompare(p->book_publish, string_value) == 1 && p->book_status == EXIST)
					{
						L[i++] = p->book_id;
					}
					p = p->next;
				}
			}
		}
		break;
		}
	}
	break;

	//在用户链表中查找
	case USER:
	{
		L = (int*)calloc(CheckUserAmount(Node, SEARCH_ALL) + 1, sizeof(int));//开辟数组空间存放查找结果

		struct  UserNode* p = (struct UserNode*)Node;
		switch (string_name)
		{
			//按用户名查找
		case USER_NAME:
		{
			if (search_mode == SEARCH_ALL)  //在全部用户中查找
			{
				while (p != NULL)
				{
					if (FuzzyCompare(p->user_name, string_value))
					{
						L[i++] = p->user_id;
					}
					p = p->next;
				}
			}
			else if (search_mode == SEARCH_EXIST)  //在现有用户中查找
			{
				while (p != NULL)
				{
					if (FuzzyCompare(p->user_name, string_value) == 1 && p->user_status == EXIST)
					{
						L[i++] = p->user_id;
					}
					p = p->next;
				}
			}
		}
		break;

		//按用户职业查找
		case USER_WORK:
		{
			if (search_mode == SEARCH_ALL)  //在全部用户中查找
			{
				while (p != NULL)
				{
					if (FuzzyCompare(p->user_work, string_value))
					{
						L[i++] = p->user_id;
					}
					p = p->next;
				}
			}
			else if (search_mode == SEARCH_EXIST)  //在现有用户中查找
			{
				while (p != NULL)
				{
					if (FuzzyCompare(p->user_work, string_value) == 1 && p->user_status == EXIST)
					{
						L[i++] = p->user_id;
					}
					p = p->next;
				}
			}
		}
		break;
		}
	}
	break;
	}

	return L;  //返回存放查找结果的数组
}




//在链表中对字符串数组进行模糊搜索，返回一个整形数组，存放符合搜索条件的结点的id序列
//传入字符串与结点的二位字符数组的任一行满足模糊匹配条件，即认为该节点符合模糊搜索条件
int* FuzzySearchNodeStringArray(void* Node, int node_name, int string_array_name, char* string_value, int search_mode)
{
	int* L = NULL, i = 0, j = 0;

	switch (node_name)
	{
	case BOOK://在图书链表中查找
	{
		L = (int*)calloc(CheckBookAmount(Node, SEARCH_ALL) + 1, sizeof(int));//开辟数组空间存放查找结果

		struct BookNode* p = (struct BookNode*)Node;

		switch (string_array_name)
		{
		case BOOK_KEYWORD://按关键词查找
		{
			if (search_mode == SEARCH_ALL)//在全部图书中查找
			{
				while (p != NULL)
				{
					for (j = 0; j < 5; j++)
					{
						if (FuzzyCompare(p->book_keyword[j], string_value))
							break;
					}

					if (j < 5)
					{
						L[i++] = p->book_id;
					}
					p = p->next;
				}
			}

			else if (search_mode == SEARCH_EXIST)//在现存图书中查找
			{
				while (p != NULL)
				{
					if (p->book_status == EXIST)
					{
						for (j = 0; j < 5; j++)
						{
							if (FuzzyCompare(p->book_keyword[j], string_value))
								break;
						}

						if (j < 5)
						{
							L[i++] = p->book_id;
						}
					}
					p = p->next;
				}
			}
		}
		break;

		case BOOK_WRITER://按作者查找
		{
			if (search_mode == SEARCH_ALL)//在全部图书中查找
			{
				while (p != NULL)
				{
					for (j = 0; j < 3 ; j++)
					{
						if (FuzzyCompare(p->book_writer[j], string_value))
							break;
					}

					if (j < 3)
					{
						L[i++] = p->book_id;
					}
					p = p->next;
				}
			}

			else if (search_mode == SEARCH_EXIST)//在现存图书中查找
			{
				while (p != NULL)
				{
					if (p->book_status == EXIST)
					{
						for (j = 0; j < 3; j++)
						{
							if (FuzzyCompare(p->book_writer[j], string_value))
								break;
						}

						if (j < 3)
						{
							L[i++] = p->book_id;
						}
					}
					p = p->next;
				}
			}
		}
		break;
		}
	}
	break;
	}

	return L;  //返回存放查找结果的数组
}