/*
文件：sort.c

作者：古亚青

内容：
对图书排序的函数；
对用户排序的函数；
对借阅排序的函数。
*/




#include <stdlib.h>
#include <string.h>


#include "database.h"
#include "sort.h"




//对图书排序
int* SortBookNode(struct BookNode* Node, int node_name, int sort_mode)
{
	int i = 0;
	int* L = (int*)calloc(CheckBookAmount(Node, SEARCH_ALL) + 1, sizeof(int)); //开辟数组空间存放查找结果

	if (Node == NULL)
		return NULL;

	struct BookNode* p = Node;
	while (p)
	{
		L[i++] = p->book_id;
		p = p->next;
	}

	int num = i;

	switch (node_name)
	{
	case BOOK_ID: //按书号排序
	{
		if (sort_mode == ASCENDING); //升序

		else if (sort_mode == DESCENDING) //降序
		{
			for (int k = 0; k < num; k++)
			{
				L[k] = num - k;
			}
		}
	}
	break;

	case BOOK_NAME: //按书名排序
	{
		int flag, tmp;

		//对书名进行冒泡排序
		for (int k = num - 1; k >= 1; k--)
		{
			for (int j = 0; j <= k - 1; j++)
			{
				if (sort_mode == ASCENDING) //升序
					flag = strcmp(ReadNodeString(Node, BOOK, L[j], BOOK_NAME), ReadNodeString(Node, BOOK, L[j + 1], BOOK_NAME)) > 0 ? 1 : 0;
				else if (sort_mode == DESCENDING) //降序
					flag = strcmp(ReadNodeString(Node, BOOK, L[j], BOOK_NAME), ReadNodeString(Node, BOOK, L[j + 1], BOOK_NAME)) < 0 ? 1 : 0;

				if (flag)
				{
					tmp = L[j + 1];
					L[j + 1] = L[j];
					L[j] = tmp;
				}
			}
		}
	}
	break;

	case BOOK_WRITER: //按第一作者排序
	{
		int flag, tmp;

		//对第一作者进行冒泡排序
		for (int k = num - 1; k >= 1; k--)
		{
			for (int j = 0; j <= k - 1; j++)
			{
				//读取对应的第一作者
				char(*p1)[MAX_LEN] = ReadNodeStringArray(Node, BOOK, L[j], BOOK_WRITER);
				char(*p2)[MAX_LEN] = ReadNodeStringArray(Node, BOOK, L[j + 1], BOOK_WRITER);

				if (sort_mode == ASCENDING) //升序
					flag = strcmp(p1[0], p2[0]) > 0 ? 1 : 0;
				else if (sort_mode == DESCENDING) //降序
					flag = strcmp(p1[0], p2[0]) < 0 ? 1 : 0;

				if (flag)
				{
					tmp = L[j + 1];
					L[j + 1] = L[j];
					L[j] = tmp;
				}
			}
		}
	}
	break;
	}

	return L; //返回排序结果
}




//对用户排序
int* SortUserNode(struct UserNode* Node, int node_name, int sort_mode)
{
	int i = 0;
	int* L = (int*)calloc(CheckUserAmount(Node, SEARCH_ALL) + 1, sizeof(int)); //开辟数组空间存放查找结果

	if (Node == NULL)
		return NULL;

	struct UserNode* p = Node;
	while (p)
	{
		L[i++] = p->user_id;
		p = p->next;
	}

	int num = i;

	switch (node_name)
	{
	case USER_ID: //按用户号排序
	{
		if (sort_mode == ASCENDING); //升序

		else if (sort_mode == DESCENDING) //降序
		{
			for (int k = 0; k < num; k++)
			{
				L[k] = num - k;
			}
		}
	}
	break;

	case USER_NAME: //按用户名称排序
	{
		int flag, tmp;

		//对用户名称进行冒泡排序
		for (int k = num - 1; k >= 1; k--)
		{
			for (int j = 0; j <= k - 1; j++)
			{
				if (sort_mode == ASCENDING) //升序
					flag = strcmp(ReadNodeString(Node, USER, L[j], USER_NAME), ReadNodeString(Node, USER, L[j + 1], USER_NAME)) > 0 ? 1 : 0;
				else if (sort_mode == DESCENDING) //降序
					flag = strcmp(ReadNodeString(Node, USER, L[j], USER_NAME), ReadNodeString(Node, USER, L[j + 1], USER_NAME)) < 0 ? 1 : 0;

				if (flag)
				{
					tmp = L[j + 1];
					L[j + 1] = L[j];
					L[j] = tmp;
				}
			}
		}
	}
	break;

	case USER_WORK://按用户工作单位排序
	{
		int flag, tmp;

		//对用户工作单位进行冒泡排序
		for (int k = num - 1; k >= 1; k--)
		{
			for (int j = 0; j <= k - 1; j++)
			{
				if (sort_mode == ASCENDING) //升序
					flag = strcmp(ReadNodeString(Node, USER, L[j], USER_WORK), ReadNodeString(Node, USER, L[j + 1], USER_WORK)) > 0 ? 1 : 0;
				else if (sort_mode == DESCENDING) //降序
					flag = strcmp(ReadNodeString(Node, USER, L[j], USER_WORK), ReadNodeString(Node, USER, L[j + 1], USER_WORK)) < 0 ? 1 : 0;

				if (flag)
				{
					tmp = L[j + 1];
					L[j + 1] = L[j];
					L[j] = tmp;
				}
			}
		}
	}
	break;
	}

	return L; //返回排序结果
}




//对借阅排序
int* SortBorrowNode(struct BorrowNode* Node, int node_name, int sort_mode)
{
	int i = 0;
	int* L = (int*)calloc(CheckBorrowAmount(Node, SEARCH_ALL) + 1, sizeof(int)); //开辟数组空间存放查找结果

	if (Node == NULL)
		return NULL;

	struct BorrowNode* p = Node;
	while (p)
	{
		L[i++] = p->borrow_id;
		p = p->next;
	}

	int num = i;

	switch (node_name)
	{
	case BORROW_ID: //按用户号排序
	{
		if (sort_mode == ASCENDING); //升序

		else if (sort_mode == DESCENDING) //降序
		{
			for (int k = 0; k < num; k++)
			{
				L[k] = num - k;
			}
		}
	}
	}

	return L; //返回排序结果
}