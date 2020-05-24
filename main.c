/*
文件：main.c

作者：李培生

内容：
NO-GUI Edition 的主函数

当前实现的Menu功能：1 2 3 4 7
*/




#include <stdio.h>

#include "database.h"
#include "date.h"
#include "file.h"




int main(void)
{
	int db_amount = FileCheckInfo();
	int db_num;

	printf("Current database amount:%d\n", db_amount);
	printf("Open or add:");

	scanf("%d", &db_num);

	if (db_num > db_amount)
	{
		FileUpdateInfo();
		db_num = db_amount = FileCheckInfo();
	}
	
	FileCheckUser();

	struct BookNode* book_head = FileReadBook(db_num);
	struct UserNode* user_head = FileReadUser();
	struct BorrowNode* borrow_head = FileReadBorrow(db_num);

	struct BookNode book_temp;
	struct BookNode user_temp;
	struct BookNode borrow_temp;


	//进入菜单
	printf("\n******Menu******\n");
	printf("1.List all books\n");
	printf("2.List all users\n");
	printf("3.List all borrow\n");
	printf("4.Add a book\n");
	printf("5.Add a user\n");
	printf("6.Add borrow\n");
	printf("7.Change a book's name\n");


	int menu_choice;
	scanf("%d", &menu_choice);

	switch (menu_choice)
	{
	case 1: //显示所有书
	{
		printf("Total:%d books\n", CheckBookAmount(book_head, SEARCH_EXIST));

		for (int i = 1; i <= CheckBookAmount(book_head, SEARCH_ALL); i++)
		{
			if (ReadNodeInt(book_head, BOOK, i, BOOK_STATUS) == EXIST) //只显示未删除的
			{
				printf("%s\n", ReadNodeString(book_head, BOOK, i, BOOK_NAME));
			}
		}
	} break;

	case 2: //显示所有用户
	{
		printf("Total:%d users\n", CheckUserAmount(user_head, SEARCH_EXIST));

		for (int i = 1; i <= CheckUserAmount(user_head, SEARCH_ALL); i++)
		{
			if (ReadNodeInt(user_head, USER, i, USER_STATUS) == EXIST) //只显示未删除的
			{
				printf("%s\n", ReadNodeString(user_head, USER, i, USER_NAME));
			}
		}
	} break;

	case 3: //显示所有借阅
	{
		printf("Total:%d borrow\n", CheckBorrowAmount(borrow_head, SEARCH_EXIST));

		for (int i = 1; i <= CheckBorrowAmount(borrow_head, SEARCH_ALL); i++)
		{
			if (ReadNodeInt(borrow_head, BORROW, i, BORROW_STATUS) == EXIST) //只显示未删除的
			{
				printf("%s\n", ReadNodeString(borrow_head, BORROW, i, USER_NAME));
			}
		}
	} break;

	case 4: //新增书
	{
		printf("book name:");
		scanf("%s", &book_temp.book_name);

		printf("book keywords:");
		scanf("%s%s%s%s%s", &book_temp.book_keyword[0], &book_temp.book_keyword[1], &book_temp.book_keyword[2], &book_temp.book_keyword[3], &book_temp.book_keyword[4]);

		printf("book writers:");
		scanf("%s%s%s", &book_temp.book_writer[0], &book_temp.book_writer[1], &book_temp.book_writer[2]);

		printf("book publish:");
		scanf("%s", &book_temp.book_publish);

		printf("book date year:");
		scanf("%d", &book_temp.book_date.year);
		printf("book date month:");
		scanf("%d", &book_temp.book_date.month);
		printf("book date day:");
		scanf("%d", &book_temp.book_date.day);

		book_temp.book_date = AddDate(book_temp.book_date.year, book_temp.book_date.month, book_temp.book_date.day);

		book_head = AddBookNode(book_head, book_temp);
	} break;

	case 7: //更改书名
	{
		printf("id:");
		scanf("%d", &book_temp.book_id);
		printf("new name:");
		scanf("%s", &book_temp.book_name);

		ChangeNodeString(book_head, BOOK, book_temp.book_id, BOOK_NAME, book_temp.book_name);
	} break;
	}




	//保存
	FileWriteBook(book_head, db_num);
	FileWriteUser(user_head);
	FileWriteBorrow(borrow_head, db_num);



	return 0;
}
