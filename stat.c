/*
文件：stat.c

作者：李培生、黄怀萱

内容：
查询图书总借阅次数的函数的定义；
查询用户总借阅次数的函数的定义；
查询用户当前借阅数量的函数的定义；
查询被借阅数量最多的图书的函数的定义；
查询被借阅数量最少的图书的函数的定义；
查询借阅数量最多的用户的函数的定义；
查询出现数量最多的图书关键词的函数的定义。
*/




#include <stdlib.h>
#include <string.h>


#include "database.h"


#include "stat.h"




//查询图书总借阅次数
int BookBorrowTime(struct BookNode* book_node, int book_id, struct BorrowNode* borrow_node)
{
    int borrow_amount = CheckBorrowAmount(borrow_node, SEARCH_ALL);
    int time = 0;

    for (int i = 1; i <= borrow_amount; i++)
    {
        if (ReadNodeInt(borrow_node, BORROW, i, BOOK_ID) == book_id)
        {
            time++;
        }
    }

    return time;
}




//查询用户总借阅次数
int UserBorrowTime(struct UserNode* user_node, int user_id, struct BorrowNode* borrow_node)
{
    int borrow_amount = CheckBorrowAmount(borrow_node, SEARCH_ALL);
    int time = 0;

    for (int i = 1; i <= borrow_amount; i++)
    {
        if (ReadNodeInt(borrow_node, BORROW, i, USER_ID) == user_id)
        {
            time++;
        }
    }

    return time;
}




//查询用户当前借阅数量
int UserBorrowTimeExist(struct UserNode* user_node, int user_id, struct BorrowNode* borrow_node)
{
    int borrow_amount = CheckBorrowAmount(borrow_node, SEARCH_ALL);
    int time = 0;

    for (int i = 1; i <= borrow_amount; i++)
    {
        if (ReadNodeInt(borrow_node, BORROW, i, BORROW_STATUS) == EXIST && ReadNodeInt(borrow_node, BORROW, i, USER_ID) == user_id)
        {
            time++;
        }
    }

    return time;
}




//查询被借阅数量最多的图书
int FindMostFavoriteBook(struct BookNode* book_node, struct BorrowNode* borrow_node)
{
    int book_amount = CheckBookAmount(book_node, SEARCH_ALL);
    int borrow_amount = CheckBorrowAmount(borrow_node, SEARCH_ALL);

    int* book_time = calloc(book_amount, sizeof(int));

    for (int i = 1; i <= borrow_amount; i++)
    {
        book_time[ReadNodeInt(borrow_node, BORROW, i, BOOK_ID) - 1]++;
    }

    int most_book_id = 1;

    for (int i = 1; i < book_amount; i++)
    {
        if (book_time[most_book_id - 1] < book_time[i])
        {
            most_book_id = i + 1;
        }
    }

    return most_book_id;
}




//查询被借阅数量最少的图书
int FindLeastFavoriteBook(struct BookNode* book_node, struct BorrowNode* borrow_node)
{
    int book_amount = CheckBookAmount(book_node, SEARCH_ALL);
    int borrow_amount = CheckBorrowAmount(borrow_node, SEARCH_ALL);

    int* book_time = calloc(book_amount, sizeof(int));

    for (int i = 1; i <= borrow_amount; i++)
    {
        book_time[ReadNodeInt(borrow_node, BORROW, i, BOOK_ID) - 1]++;
    }

    int least_book_id = 1;

    for (int i = 1; i < book_amount; i++)
    {
        if (book_time[least_book_id - 1] > book_time[i])
        {
            least_book_id = i + 1;
        }
    }

    return least_book_id;
}




//查询借阅数量最多的用户
int FindMostBorrowUser(struct UserNode* user_node, struct BorrowNode* borrow_node)
{
    int user_amount = CheckUserAmount(user_node, SEARCH_ALL);
    int borrow_amount = CheckBorrowAmount(borrow_node, SEARCH_ALL);

    int* user_time = calloc(user_amount, sizeof(int));

    for (int i = 1; i <= borrow_amount; i++)
    {
        user_time[ReadNodeInt(borrow_node, BORROW, i, USER_ID) - 1]++;
    }

    int most_user_id = 1;

    for (int i = 1; i < user_amount; i++)
    {
        if (user_time[most_user_id - 1] < user_time[i])
        {
            most_user_id = i + 1;
        }
    }

    return most_user_id;
}




//查询出现数量最多的图书关键词
char* FindMostBookKey(struct BookNode* book_node)
{
    int book_amount = CheckBookAmount(book_node, SEARCH_ALL);
    
    char(*book_key)[MAX_LEN] = calloc(book_amount * 5, sizeof(char) * MAX_LEN);
    int* key_time = calloc(book_amount * 5, sizeof(int));

    int key_amount = 0;
    for (int i = 1; i <= book_amount; i++)
    {
        char(*p_key)[MAX_LEN] = ReadNodeStringArray(book_node, BOOK, i, BOOK_KEYWORD);

        for (int j = 0; j < 5; j++)
        {
            //判断第i个字符串数组第j + 1个字符串
            int is_same = 0;
            
            //判断与之前的是否重复
            for (int m = 0; m < key_amount; m++)
            {
                if (strcmp(p_key[j], book_key[m]) == 0)
                {
                    is_same = 1;
                    key_time[m]++;
                    break;
                }
            }

            //重复，继续
            if (is_same == 1)
            {
                continue;
            }

            //不重复，新增key，次数为1
            strcpy(book_key[key_amount], p_key[j]);
            key_time[key_amount] = 1;
            key_amount++;
        }
    }

    int most_key_id = 0;

    for (int i = 1; i < key_amount; i++)
    {
        if (key_time[most_key_id] < key_time[i])
        {
            most_key_id = i;
        }
    }

    return book_key[most_key_id];
}