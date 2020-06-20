/*
文件：database.c

作者：古亚青、李培生

内容：
查找结点个数的函数；
新增结点、删除结点、读取结点、更改结点、搜索结点五种基本函数。
*/




#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "database.h"




//返回书的个数
int CheckBookAmount(struct BookNode* node, int check_mode)
{
	struct BookNode* p = node;
	int i = 0;

	while (p != NULL)
	{
		if (p->book_status == EXIST || check_mode == SEARCH_ALL)
			i++;

		p = p->next;
	}

	return i;
}




//返回用户的个数
int CheckUserAmount(struct UserNode* node, int check_mode)
{
	struct UserNode* p = node;
	int i = 0;

	while (p != NULL)
	{
		if (p->user_status == EXIST || check_mode == SEARCH_ALL)
			i++;

		p = p->next;
	}

	return i;
}




//返回借阅的个数
int CheckBorrowAmount(struct BorrowNode* node, int check_mode)
{
	struct BorrowNode* p = node;
	int i = 0;

	while (p != NULL)
	{
		if (p->borrow_status == EXIST || check_mode == SEARCH_ALL)
			i++;

		p = p->next;
	}

	return i;
}




//新增图书结点
struct BookNode* AddBookNode(struct BookNode* node, struct BookNode data)
{
	struct BookNode* head = node;
	struct BookNode* p = head;
	struct BookNode* q = head;

	int q_id = 0;
	q = (struct BookNode*)malloc(sizeof(struct BookNode));

	if (head != NULL)
	{
		q_id++;
		while (p->next != NULL)
		{
			q_id++;
			p = p->next;
		}
		p->next = q;
	}


	//写入
	q->book_id = q_id + 1;

	strcpy(q->book_name, data.book_name);

	for (int i = 0; i < 5; i++)
		strcpy(q->book_keyword[i], data.book_keyword[i]);

	for (int i = 0; i < 3; i++)
		strcpy(q->book_writer[i], data.book_writer[i]);

	strcpy(q->book_publish, data.book_publish);

	q->book_date = data.book_date;

	q->book_status = EXIST;

	q->next = NULL;

	if (head == NULL)
		head = q;

	return head;
}




//新增用户结点
struct UserNode* AddUserNode(struct UserNode* node, struct UserNode data)
{
	struct UserNode* head = node;
	struct UserNode* p = head;
	struct UserNode* q = head;

	int q_id = 0;
	q = (struct UserNode*)malloc(sizeof(struct UserNode));

	if (head != NULL)
	{
		q_id++;
		while (p->next != NULL)
		{
			q_id++;
			p = p->next;
		}
		p->next = q;
	}

	//写入
	q->user_id = q_id + 1;

	strcpy(q->user_name, data.user_name);

	q->user_sex = data.user_sex;

	strcpy(q->user_work, data.user_work);

	q->user_status = NOT_PASS;

	q->next = NULL;

	if (head == NULL)
		head = q;

	return head;
}




//新增借阅结点
struct BorrowNode* AddBorrowNode(struct BorrowNode* node, struct BorrowNode data)
{
	struct BorrowNode* head = node;
	struct BorrowNode* p = head;
	struct BorrowNode* q = head;

	int q_id = 0;
	q = (struct BorrowNode*)malloc(sizeof(struct BorrowNode));

	if (head != NULL)
	{
		q_id++;
		while (p->next != NULL)
		{
			q_id++;
			p = p->next;
		}
		p->next = q;
	}

	//写入
	q->borrow_id = q_id + 1;

	q->book_id = data.book_id;
	q->user_id = data.user_id;

	q->borrow_date = data.borrow_date;
	q->return_date = data.return_date;

	q->borrow_status = EXIST;

	q->next = NULL;

	if (head == NULL)
		head = q;

	return head;
}




//读取一个图书结点
struct BookNode ReadBookNode(struct BookNode* node, int book_id)
{
	struct  BookNode* p = node;
	int i;
	for (i = 1; i < book_id; i++)
	{
		p = p->next;
	}

	return *p;
}




//读取一个用户结点
struct UserNode ReadUserNode(struct UserNode* node, int user_id)
{
	struct  UserNode* p = node;
	int i;
	for (i = 1; i < user_id; i++)
	{
		p = p->next;
	}

	return *p;
}




//删除一个结点，成功则返回1，若不存在该id则返回0
int DeleteNode(void* Node, int node_name, int id)
{
	switch (node_name)
	{
	case BOOK://删除图书链表中的结点
	{
		struct  BookNode* p = (struct BookNode*)Node;
		int i = 1;

		if (id > CheckBookAmount(p, SEARCH_ALL))//若不存在该id
			return 0;

		for (i = 1; i < id; i++)
		{
			p = p->next;
		}

		p->book_status = DELETE;
	}
	break;

	case USER://删除用户链表中的结点
	{
		struct  UserNode* p = (struct UserNode*)Node;
		int i;

		if (id > CheckUserAmount(p, SEARCH_ALL))//若不存在该id
			return 0;

		for (i = 1; i < id; i++)
		{
			p = p->next;
		}

		p->user_status = DELETE;
	}
	break;

	case BORROW://删除借阅链表中的结点
	{
		struct  BorrowNode* p = (struct BorrowNode*)Node;
		int i;

		if (id > CheckBorrowAmount(p, SEARCH_ALL))//若不存在该id
			return 0;

		for (i = 1; i < id; i++)
		{
			p = p->next;
		}

		p->borrow_status = DELETE;
	}
	break;
	}

	return 1;
}




//链表整型内容的读取 
int ReadNodeInt(void* Node, int node_name, int id, int int_name)
{
	switch (node_name)
	{
	case BOOK://在图书库中读取
	{
		struct  BookNode* p = (struct BookNode*)Node;
		int i;
		for (i = 1; i < id; i++)
		{
			p = p->next;
		}

		switch (int_name)
		{
		case BOOK_STATUS:
			return p->book_status;
		}
	}

	case USER://在用户库中读取
	{
		struct  UserNode* p = (struct UserNode*)Node;
		int i;
		for (i = 1; i < id; i++)
		{
			p = p->next;
		}

		switch (int_name)
		{
		case USER_SEX:
			return p->user_sex;
		case USER_STATUS:
			return p->user_status;
		}
	}

	case BORROW://在借阅库中读取
	{
		struct  BorrowNode* p = (struct BorrowNode*)Node;
		int i;
		for (i = 1; i < id; i++)
		{
			p = p->next;
		}

		switch (int_name)
		{
		case BOOK_ID:
			return p->book_id;
		case USER_ID:
			return p->user_id;
		case BORROW_STATUS:
			return p->borrow_status;
		}
	}
	}
}




//链表单个字符串内容的读取
char* ReadNodeString(void* Node, int node_name, int id, int string_name)
{
	switch (node_name)
	{
	case BOOK://在图书库中读取
	{
		struct  BookNode* p = (struct BookNode*)Node;
		int i;
		for (i = 1; i < id; i++)
		{
			p = p->next;
		}

		switch (string_name)
		{
		case BOOK_NAME:
			return p->book_name;
		case BOOK_PUBLISH:
			return p->book_publish;
		}
	}

	case USER://在用户库中读取
	{
		struct  UserNode* p = (struct UserNode*)Node;
		int i;
		for (i = 1; i < id; i++)
		{
			p = p->next;
		}

		switch (string_name)
		{
		case USER_NAME:
			return p->user_name;
		case USER_WORK:
			return p->user_work;
		}
	}
	}
}




//链表字符串数组的读取
char** ReadNodeStringArray(void* Node, int node_name, int id, int string_array_name)
{
	switch (node_name)
	{
	case BOOK://在图书库中读取
	{
		struct  BookNode* p = (struct BookNode*)Node;
		int i;
		for (i = 1; i < id; i++)
		{
			p = p->next;
		}

		switch (string_array_name)
		{
		case BOOK_KEYWORD:
			return p->book_keyword;
		case BOOK_WRITER:
			return p->book_writer;
		}
	}
	}
}




//链表日期的读取
struct Date ReadNodeDate(void* Node, int node_name, int id, int date_name)
{
	switch (node_name)
	{
	case BOOK://在图书库中读取
	{
		struct  BookNode* p = (struct BookNode*)Node;
		int i;
		for (i = 1; i < id; i++)
		{
			p = p->next;
		}

		switch (date_name)
		{
		case BOOK_DATE:
			return p->book_date;
		}
	}

	case BORROW://在借阅库中读取
	{
		struct  BorrowNode* p = (struct BorrowNode*)Node;
		int i;
		for (i = 1; i < id; i++)
		{
			p = p->next;
		}

		switch (date_name)
		{
		case BORROW_DATE:
			return p->borrow_date;
		case RETURN_DATE:
			return p->return_date;
		}
	}
	}
}




//链表整型内容的更改
int ChangeNodeInt(void* Node, int node_name, int id, int int_name, int int_value)
{
	switch (node_name)
	{
	case BOOK://在图书链表中更改
	{
		struct  BookNode* p = (struct BookNode*)Node;
		int i;
		for (i = 1; i < id; i++)
		{
			p = p->next;
		}

		switch (int_name)
		{
		case BOOK_STATUS:
			p->book_status = int_value;
		}
	}
	break;

	case USER://在用户链表中更改
	{
		struct  UserNode* p = (struct UserNode*)Node;
		int i;
		for (i = 1; i < id; i++)
		{
			p = p->next;
		}

		switch (int_name)
		{
		case USER_SEX:
			p->user_sex = int_value;
			break;
		case USER_STATUS:
			p->user_status = int_value;
		}
	}
	break;

	case BORROW://在借阅链表中更改
	{
		struct  BorrowNode* p = (struct BorrowNode*)Node;
		int i;
		for (i = 1; i < id; i++)
		{
			p = p->next;
		}

		switch (int_name)
		{
		case BOOK_ID:
			p->book_id = int_value;
			break;
		case USER_ID:
			p->user_id = int_value;
			break;
		case BORROW_STATUS:
			p->borrow_status = int_value;
			break;
		}
	}
	}

	return id;  //返回被更改结点的id
}




//链表单个字符串内容的更改
int ChangeNodeString(void* Node, int node_name, int id, int string_name, char* string_value)
{
	switch (node_name)
	{
	case BOOK://在图书链表中更改
	{
		struct  BookNode* p = (struct BookNode*)Node;
		int i;
		for (i = 1; i < id; i++)
		{
			p = p->next;
		}

		switch (string_name)
		{
		case BOOK_NAME:
			strcpy(p->book_name, string_value);
		case BOOK_PUBLISH:
			strcpy(p->book_publish, string_value);
		}
	}

	case USER://在用户链表中更改
	{
		struct  UserNode* p = (struct UserNode*)Node;
		int i;
		for (i = 1; i < id; i++)
		{
			p = p->next;
		}

		switch (string_name)
		{
		case USER_NAME:
			strcpy(p->user_name, string_value);
		case USER_WORK:
			strcpy(p->user_work, string_value);
		}
	}
	}

	return id;
}




//链表字符串数组的更改
int ChangeNodeStringArray(void* Node, int node_name, int id, int string_array_name, char** string_array_value)
{
	char(*str)[MAX_LEN] = string_array_value;//定义一个数组指针，指向传入二维数组的第一行

	switch (node_name)
	{
	case BOOK://在图书链表中更改
	{
		struct  BookNode* p = (struct BookNode*)Node;
		int i, j;
		for (i = 1; i < id; i++)
		{
			p = p->next;
		}

		switch (string_array_name)
		{
		case BOOK_KEYWORD:
			for (j = 0; j <= 4; j++)
			{
				strcpy(p->book_keyword[j], str[j]);
			}
		case BOOK_WRITER:
			for (j = 0; j <= 2; j++)
			{
				strcpy(p->book_writer[j], str[j]);
			}
		}
	}
	}

	return id;
}




//链表日期的更改
int ChangeNodeDate(void* Node, int node_name, int id, int date_name, struct Date date_value)
{
	switch (node_name)
	{
	case BOOK://在图书链表中更改
	{
		struct  BookNode* p = (struct BookNode*)Node;
		int i;
		for (i = 1; i < id; i++)
		{
			p = p->next;
		}

		switch (date_name)
		{
		case BOOK_DATE:
			p->book_date = date_value;
		}
	}

	case BORROW://在借阅链表中更改
	{
		struct  BorrowNode* p = (struct BorrowNode*)Node;
		int i;
		for (i = 1; i < id; i++)
		{
			p = p->next;
		}

		switch (date_name)
		{
		case BORROW_DATE:
			p->borrow_date = date_value;
		case RETURN_DATE:
			p->return_date = date_value;
		}
	}
	}

	return id;
}




//链表整型内容的搜索
int* SearchNodeInt(void* Node, int node_name, int int_name, int int_value, int search_mode)
{
	int* L  = NULL, i = 0;

	switch (node_name)
	{
		//在图书链表中查找 
	case BOOK:
	{
		L = (int*)calloc(CheckBookAmount(Node, SEARCH_ALL) + 1, sizeof(int));//开辟数组空间存放查找结果

		struct  BookNode* p = (struct BookNode*)Node;
		switch (int_name)
		{
			//按图书状态查找 
		case BOOK_STATUS:
		{
			if (search_mode == SEARCH_ALL)//在现有图书中查找 
			{
				while (p != NULL)
				{
					if (p->book_status == int_value)
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
		switch (int_name)
		{
			//按用户性别查找 
		case USER_SEX:
		{
			if (search_mode == SEARCH_ALL)//在全部用户中查找 
			{
				while (p != NULL)
				{
					if (p->user_sex == int_value)
					{
						L[i++] = p->user_id;
					}
					p = p->next;
				}
			}
			else if (search_mode == SEARCH_EXIST)//在现有用户中查找 
			{
				while (p != NULL)
				{
					if (p->user_sex == int_value && p->user_status == EXIST)
					{
						L[i++] = p->user_id;
					}
					p = p->next;
				}
			}
		}
		break;

		//按用户状态查找 
		case USER_STATUS:
		{
			if (search_mode == SEARCH_ALL)//在全部用户中查找 
			{
				while (p != NULL)
				{
					if (p->user_status == int_value)
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

	//在借阅链表中查找 
	case BORROW:
	{
		L = (int*)calloc(CheckBorrowAmount(Node, SEARCH_ALL) + 1, sizeof(int));//开辟数组空间存放查找结果
		
		struct  BorrowNode* p = (struct BorrowNode*)Node;
		switch (int_name)
		{
			//按图书id查找 
		case BOOK_ID:
		{
			if (search_mode == SEARCH_ALL)//在全部借阅记录中查找 
			{
				while (p != NULL)
				{
					if (p->book_id == int_value)
					{
						L[i++] = p->borrow_id;
					}
					p = p->next;
				}
			}
			else if (search_mode == SEARCH_EXIST)//在未归还借阅记录中查找 
			{
				while (p != NULL)
				{
					if (p->book_id == int_value && p->borrow_status == EXIST)
					{
						L[i++] = p->borrow_id;
					}
					p = p->next;
				}
			}
		}
		break;

		//按借阅id查找  
		case USER_ID:
		{
			if (search_mode == SEARCH_ALL)//在全部借阅记录中查找 
			{
				while (p != NULL)
				{
					if (p->user_id == int_value)
					{
						L[i++] = p->borrow_id;
					}
					p = p->next;
				}
			}
			else if (search_mode == SEARCH_EXIST)//在未归还借阅记录中查找 
			{
				while (p != NULL)
				{
					if (p->user_id == int_value && p->borrow_status == EXIST)
					{
						L[i++] = p->borrow_id;
					}
					p = p->next;
				}
			}
		}
		break;

		//按借阅状态查找 
		case BORROW_STATUS:
		{
			if (search_mode == SEARCH_ALL)//在全部借阅记录中查找 
			{
				while (p != NULL)
				{
					if (p->borrow_status == int_value)
					{
						L[i++] = p->borrow_id;
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

	return L;//返回存放查找结果的数组
}




//链表单个字符串内容的搜索
int* SearchNodeString(void* Node, int node_name, int string_name, char* string_value, int search_mode)
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
					if (strcmp(p->book_name, string_value) == 0)
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
					if (strcmp(p->book_name, string_value) == 0 && p->book_status == EXIST)
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
					if (strcmp(p->book_publish, string_value) == 0)
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
					if (strcmp(p->book_publish, string_value) == 0 && p->book_status == EXIST)
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
					if (strcmp(p->user_name, string_value) == 0)
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
					if (strcmp(p->user_name, string_value) == 0 && p->user_status == EXIST)
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
					if (strcmp(p->user_work, string_value) == 0)
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
					if (strcmp(p->user_work, string_value) == 0 && p->user_status == EXIST)
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




//链表字符串数组的搜索
int* SearchNodeStringArray(void* Node, int node_name, int string_array_name, char** string_array_value, int search_mode)
{
	int* L = NULL, i = 0, j = 0;

	char(*str)[MAX_LEN] = string_array_value;//定义数组指针，指向传入的二维字符数组的第一行

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
					for (j = 0; j <= 5; j++)
					{
						if (strcmp(p->book_keyword[j], str[j]) != 0)
							break;
					}

					if (j == 5)
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
						for (j = 0; j <= 5; j++)
						{
							if (strcmp(p->book_keyword[j], str[j]) != 0)
								break;
						}

						if (j == 5)
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
					for (j = 0; j <= 2; j++)
					{
						if (strcmp(p->book_writer[j], str[j]) != 0)
							break;
					}

					if (j == 3)
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
						for (j = 0; j <= 2; j++)
						{
							if (strcmp(p->book_writer[j], str[j]) != 0)
								break;
						}

						if (j == 3)
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




//链表日期的搜索
int* SearchNodeDate(void* Node, int node_name, int date_name, struct Date date_value, int search_mode)
{
	int* L = NULL, i = 0;
	L = (int*)calloc(100, sizeof(int));//开辟数组空间存放查找结果

	switch (node_name)
	{
	case BOOK://在图书链表中查找
	{
		L = (int*)calloc(CheckBookAmount(Node, SEARCH_ALL) + 1, sizeof(int));//开辟数组空间存放查找结果
		
		struct BookNode* p = (struct BookNode*)Node;

		switch (date_name)
		{
		case BOOK_DATE://按图书日期查找
		{
			if (search_mode == SEARCH_ALL)//在全部图书中查找
			{
				while (p != NULL)
				{
					if (DateInterval(p->book_date, date_value) == 0)
					{
						L[i++] = p->book_id;
					}
					p = p->next;
				}
			}

			else if (search_mode == SEARCH_ALL)//在现存图书中查找
			{
				while (p != NULL)
				{
					if (DateInterval(p->book_date, date_value) == 0 && p->book_status == EXIST)
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

	case BORROW://在借阅链表中查找
	{
		L = (int*)calloc(CheckBorrowAmount(Node, SEARCH_ALL) + 1, sizeof(int));//开辟数组空间存放查找结果
		
		struct BorrowNode* p = (struct BorrowNode*)Node;

		switch (date_name)
		{
		case BORROW_DATE://按借阅日期查找
		{
			if (search_mode == SEARCH_ALL)//在全部借阅记录中查找
			{
				while (p != NULL)
				{
					if (DateInterval(p->borrow_date, date_value) == 0)
					{
						L[i++] = p->borrow_id;
					}
					p = p->next;
				}
			}

			else if (search_mode == SEARCH_EXIST)//在未归还借阅记录中查找
			{
				while (p != NULL)
				{
					if (DateInterval(p->borrow_date, date_value) == 0 && p->borrow_status == EXIST)
					{
						L[i++] = p->borrow_id;
					}
					p = p->next;
				}
			}
		}
		break;

		case RETURN_DATE://按归还日期查找
		{
			if (search_mode == SEARCH_ALL)//在全部借阅记录中查找
			{
				while (p != NULL)
				{
					if (DateInterval(p->return_date, date_value) == 0 && p->borrow_status == DELETE)
					{
						L[i++] = p->borrow_id;
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