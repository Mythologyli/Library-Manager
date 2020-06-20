/*
文件：box.c

作者：李培生

内容：
控制显示内容的全局变量；
注册、登录、管理员登录、打开文件、新增图书、新增图书等功能的函数的定义；
设置显示内容的函数的定义；
显示交互窗口的函数的定义。
*/




#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "graphics.h"
#include "extgraph.h"
#include "imgui.h"


#include "database.h"
#include "date.h"
#include "menu.h"
#include "file.h"
#include "list.h"
#include "sort.h"
#include "fuzzysearch.h"
#include "stat.h"
#include "message.h"


#include "box.h"




//外部全局变量
extern struct BookNode* book_head; //当前打开的图书链表
extern struct UserNode* user_head; //当前打开的用户链表
extern struct BorrowNode* borrow_head; //当前打开的借阅链表

extern int log_status; //当前登录状态

extern int current_user_id; //当前用户id（User模式）

extern int db_num; //当前打开的图书/借阅库的序号

extern int borrow_day; //当前设置的借阅天数
extern int max_borrow_time; //当前设置的最大借阅数量

extern double winheight; //窗口高度
extern double winwidth; //窗口宽度




//全局变量
int box_content = BOX_NO; //显示内容




//注册
void DrawRegisterBox(void)
{
	double x = 4.0;
	double y = winheight - GetFontHeight() * 10;
	double w = 1.5;
	double h = GetFontHeight() * 1.5;
	double dx = 1.8;
	double dy = GetFontHeight() * 2.0;


	drawLabel(x, y, "User name:");
	static char user_name[MAX_LEN] = "name";
	textbox(GenUIID(0), x, y - dy, w, h, user_name, sizeof(user_name));

	drawLabel(x, y - dy * 2, "Sex: (Male-0 Female-1)");
	static char user_sex[2] = "0\n";
	textbox(GenUIID(0), x, y - dy * 3, w, h, user_sex, sizeof(user_sex));

	drawLabel(x, y - dy * 4, "Workplace:");
	static char user_work[MAX_LEN] = "work";
	textbox(GenUIID(0), x, y - dy * 5, w, h, user_work, sizeof(user_work));

	if (button(GenUIID(0), x + w / 4, y - dy * 7, w / 2, h, "OK"))
	{
		if (atoi(user_sex) == MALE || atoi(user_sex) == FEMALE)
		{
			struct UserNode temp;
			strcpy(temp.user_name, user_name);
			temp.user_sex = atoi(user_sex);
			strcpy(temp.user_work, user_work);

			user_head = AddUserNode(user_head, temp);

			FileWriteUser(user_head);

			SetBox(BOX_NO);
			SetMessage(MESSAGE_NO, NULL);
		}
		else
		{
			SetMessage(MESSAGE_YES, "Invalid input !");
		}
	}

	if (button(GenUIID(0), x + w / 4, y - dy * 8, w / 2, h, "Cancel"))
	{
		SetBox(BOX_NO);
		SetMessage(MESSAGE_NO, NULL);
	}
}




//登录 
void DrawUserLogBox(void)
{
	double x = 4.0;
	double y = winheight - GetFontHeight() * 10;
	double w = 1.5;
	double h = GetFontHeight() * 1.5;
	double dx = 1.8;
	double dy = GetFontHeight() * 2.0;


	drawLabel(x, y, "Please input your name:");
	static char user_name[MAX_LEN];
	textbox(GenUIID(0), x, y - dy, w, h, user_name, sizeof(user_name));

	drawLabel(x, y - dy * 2, "Workplace:");
	static char user_work[MAX_LEN];
	textbox(GenUIID(0), x, y - dy * 3, w, h, user_work, sizeof(user_work));

	if (button(GenUIID(0), x + w / 4, y - dy * 5, w / 2, h, "OK"))
	{
		int* user_id = SearchNodeString(user_head, USER, USER_NAME, user_name, SEARCH_EXIST);
				
		if (user_id[0] != 0 && strcmp(user_work, ReadNodeString(user_head, USER, user_id[0], USER_WORK)) == 0)
		{
			log_status = USER;

			current_user_id = user_id[0];

			SetBox(BOX_NO);
			SetMessage(MESSAGE_NO, NULL);
		}
		else
		{
			SetMessage(MESSAGE_YES, "Wrong workplace or you have not been passed by admin !");
		}
	}

	if (button(GenUIID(0), x + w / 4, y - dy * 6, w / 2, h, "Cancel"))
	{
		SetBox(BOX_NO);
		SetMessage(MESSAGE_NO, NULL);
	}
}




//管理员登录
void DrawAdminLogBox(void)
{
	double x = 4.0;
	double y = winheight - GetFontHeight() * 10;
	double w = 1.5;
	double h = GetFontHeight() * 1.5;
	double dx = 1.8;
	double dy = GetFontHeight() * 2.0;


	drawLabel(x, y, "Admin password:");
	static char admin_pw[10];
	textbox(GenUIID(0), x, y - dy, w, h, admin_pw, sizeof(admin_pw));

	if (button(GenUIID(0), x + w / 4, y - dy * 3, w / 2, h, "OK"))
	{
		if (strcmp(admin_pw, "ilovezju") == 0)
		{
			log_status = ADMIN;

			SetBox(BOX_NO);
			SetMessage(MESSAGE_NO, NULL);
		}
		else
		{
			SetMessage(MESSAGE_YES, "Wrong password !");
		}
	}

	if (button(GenUIID(0), x + w / 4, y - dy * 4, w / 2, h, "Cancel"))
	{
		SetBox(BOX_NO);
		SetMessage(MESSAGE_NO, NULL);
	}
}




//打开文件
void DrawFileOpenBox(void)
{
	double x = 4.0;
	double y = winheight - GetFontHeight() * 10;
	double w = 1.5;
	double h = GetFontHeight() * 1.5;
	double dx = 1.8;
	double dy = GetFontHeight() * 2.0;

	int db_amount = FileCheckInfo();
	char temp_str[50];
	sprintf(temp_str, "Database num (1 to %d):", db_amount);


	drawLabel(x, y, temp_str);
	static char db_num_str[4] = "1";
	textbox(GenUIID(0), x, y - dy, w, h, db_num_str, sizeof(db_num_str));

	if (button(GenUIID(0), x + w / 4, y - dy * 2, w / 2, h, "OK"))
	{
		db_num = atoi(db_num_str);
		
		if (db_num > 0 && db_num <= db_amount)
		{
			book_head = FileReadBook(db_num);
			borrow_head = FileReadBorrow(db_num);

			SetBox(BOX_NO);
			SetMessage(MESSAGE_NO, NULL);
		}
		else
		{
			SetMessage(MESSAGE_YES, "Invalid input !");
		}
	}

	if (button(GenUIID(0), x + w / 4, y - dy * 3, w / 2, h, "Cancel"))
	{
		SetBox(BOX_NO);
		SetMessage(MESSAGE_NO, NULL);
	}
}




//新增图书
void DrawAddBookBox(void)
{
	double x = 4.0;
	double y = winheight - GetFontHeight() * 10;
	double w = 1.5;
	double h = GetFontHeight() * 1.5;
	double dx = 1.8;
	double dy = GetFontHeight() * 2.0;

	drawLabel(x, y, "Book Name:");
	static char book_name[MAX_LEN] = "name";
	textbox(GenUIID(0), x, y - dy, w, h, book_name, sizeof(book_name));

	drawLabel(x, y - dy * 2, "Book Keyword:");
	static char book_keyword_1[MAX_LEN] = "key";
	textbox(GenUIID(0), x - dx * 2, y - dy * 3, w, h, book_keyword_1, sizeof(book_keyword_1));
	static char book_keyword_2[MAX_LEN] = "key";
	textbox(GenUIID(0), x - dx, y - dy * 3, w, h, book_keyword_2, sizeof(book_keyword_2));
	static char book_keyword_3[MAX_LEN] = "key";
	textbox(GenUIID(0), x, y - dy * 3, w, h, book_keyword_3, sizeof(book_keyword_3));
	static char book_keyword_4[MAX_LEN] = "key";
	textbox(GenUIID(0), x + dx, y - dy * 3, w, h, book_keyword_4, sizeof(book_keyword_4));
	static char book_keyword_5[MAX_LEN] = "key";
	textbox(GenUIID(0), x + dx * 2, y - dy * 3, w, h, book_keyword_5, sizeof(book_keyword_5));

	drawLabel(x, y - dy * 4, "Book Writer:");
	static char book_writer_1[MAX_LEN] = "writer";
	textbox(GenUIID(0), x - dx, y - dy * 5, w, h, book_writer_1, sizeof(book_writer_1));
	static char book_writer_2[MAX_LEN] = "writer";
	textbox(GenUIID(0), x, y - dy * 5, w, h, book_writer_2, sizeof(book_writer_2));
	static char book_writer_3[MAX_LEN] = "writer";
	textbox(GenUIID(0), x + dx, y - dy * 5, w, h, book_writer_3, sizeof(book_writer_3));

	drawLabel(x, y - dy * 6, "Book Publish:");
	static char book_publish[MAX_LEN] = "publish";
	textbox(GenUIID(0), x, y - dy * 7, w, h, book_publish, sizeof(book_publish));

	drawLabel(x, y - dy * 8, "Book Publish Date:");
	static char book_date_year[5] = "2020";
	textbox(GenUIID(0), x - dx, y - dy * 9, w, h, book_date_year, sizeof(book_date_year));
	static char book_date_month[3] = "1";
	textbox(GenUIID(0), x, y - dy * 9, w, h, book_date_month, sizeof(book_date_month));
	static char book_date_day[3] = "1";
	textbox(GenUIID(0), x + dx, y - dy * 9, w, h, book_date_day, sizeof(book_date_day));

	if (button(GenUIID(0), x + w / 4, y - dy * 11, w / 2, h, "OK"))
	{
		struct BookNode temp;
		temp.book_date = AddDate(atoi(book_date_year), atoi(book_date_month), atoi(book_date_day));
		if (temp.book_date.year != 0)
		{
			strcpy(temp.book_name, book_name);
			strcpy(temp.book_keyword[0], book_keyword_1);
			strcpy(temp.book_keyword[1], book_keyword_2);
			strcpy(temp.book_keyword[2], book_keyword_3);
			strcpy(temp.book_keyword[3], book_keyword_4);
			strcpy(temp.book_keyword[4], book_keyword_5);
			strcpy(temp.book_writer[0], book_writer_1);
			strcpy(temp.book_writer[1], book_writer_2);
			strcpy(temp.book_writer[2], book_writer_3);
			strcpy(temp.book_publish, book_publish);
			
			book_head = AddBookNode(book_head, temp);

			SetBox(BOX_NO);
			SetMessage(MESSAGE_NO, NULL);
		}
		else
		{
			SetMessage(MESSAGE_YES, "Invalid input !");
		}
	}

	if (button(GenUIID(0), x + w / 4, y - dy * 12, w / 2, h, "Cancel"))
	{
		SetBox(BOX_NO);
		SetMessage(MESSAGE_NO, NULL);
	}
}




//编辑图书
void DrawEditBookBox(void)
{
	double x = 4.0;
	double y = winheight - GetFontHeight() * 10;
	double w = 1.5;
	double h = GetFontHeight() * 1.5;
	double dx = 1.8;
	double dy = GetFontHeight() * 2.0;

	static int box_level = 1;
	
	static char book_id_str[4] = "1";
	static int book_id;

	if (box_level == 1)
	{
		drawLabel(x, y, "Book ID:");
		textbox(GenUIID(0), x, y - dy, w, h, book_id_str, sizeof(book_id_str));

		if (button(GenUIID(0), x + w / 4, y - dy * 3, w / 2, h, "OK"))
		{
			book_id = atoi(book_id_str);

			if (book_id > 0 && book_id <= CheckBookAmount(book_head, SEARCH_ALL) && ReadNodeInt(book_head, BOOK, book_id, BOOK_STATUS) == EXIST)
			{
				box_level = 2;
			}
			else
			{
				SetMessage(MESSAGE_YES, "Invalid input !");
			}
		}
		

		if (button(GenUIID(0), x + w / 4, y - dy * 4, w / 2, h, "Cancel"))
		{
			SetBox(BOX_NO);
			SetMessage(MESSAGE_NO, NULL);
		}
	}
	else
	{
		char temp_str[5];

		static struct BookNode temp;

		if (box_level == 2)
			temp = ReadBookNode(book_head, book_id);
			
		drawLabel(x, y, "Book Name:");
		textbox(GenUIID(0), x, y - dy, w, h, temp.book_name, sizeof(temp.book_name));

		drawLabel(x, y - dy * 2, "Book Keyword:");
		textbox(GenUIID(0), x - dx * 2, y - dy * 3, w, h, temp.book_keyword[0], sizeof(temp.book_keyword[0]));
		textbox(GenUIID(0), x - dx, y - dy * 3, w, h, temp.book_keyword[1], sizeof(temp.book_keyword[1]));
		textbox(GenUIID(0), x, y - dy * 3, w, h, temp.book_keyword[2], sizeof(temp.book_keyword[2]));
		textbox(GenUIID(0), x + dx, y - dy * 3, w, h, temp.book_keyword[3], sizeof(temp.book_keyword[3]));
		textbox(GenUIID(0), x + dx * 2, y - dy * 3, w, h, temp.book_keyword[4], sizeof(temp.book_keyword[4]));

		drawLabel(x, y - dy * 4, "Book Writer:");
		textbox(GenUIID(0), x - dx, y - dy * 5, w, h, temp.book_writer[0], sizeof(temp.book_writer[0]));
		textbox(GenUIID(0), x, y - dy * 5, w, h, temp.book_writer[1], sizeof(temp.book_writer[1]));
		textbox(GenUIID(0), x + dx, y - dy * 5, w, h, temp.book_writer[2], sizeof(temp.book_writer[2]));

		drawLabel(x, y - dy * 6, "Book Publish:");
		textbox(GenUIID(0), x, y - dy * 7, w, h, temp.book_publish, sizeof(temp.book_publish));


		static char book_date_year[5];
		static char book_date_month[3];
		static char book_date_day[3];

			
		if (box_level == 2)
		{
			strcpy(book_date_year, itoa(temp.book_date.year, temp_str, 10));
			strcpy(book_date_month, itoa(temp.book_date.month, temp_str, 10));
			strcpy(book_date_day, itoa(temp.book_date.day, temp_str, 10));
		}


		drawLabel(x, y - dy * 8, "Book Publish Date:");
		textbox(GenUIID(0), x - dx, y - dy * 9, w, h, book_date_year, sizeof(book_date_year));
		textbox(GenUIID(0), x, y - dy * 9, w, h, book_date_month, sizeof(book_date_month));
		textbox(GenUIID(0), x + dx, y - dy * 9, w, h, book_date_day, sizeof(book_date_day));

		box_level = 3;

		if (button(GenUIID(0), x + w / 4, y - dy * 11, w / 2, h, "OK"))
		{
			temp.book_date = AddDate(atoi(book_date_year), atoi(book_date_month), atoi(book_date_day));
			if (temp.book_date.year != 0)
			{
				ChangeNodeString(book_head, BOOK, book_id, BOOK_NAME, temp.book_name);
				ChangeNodeStringArray(book_head, BOOK, book_id, BOOK_KEYWORD, temp.book_keyword);
				ChangeNodeStringArray(book_head, BOOK, book_id, BOOK_WRITER, temp.book_writer);
				ChangeNodeString(book_head, BOOK, book_id, BOOK_PUBLISH, temp.book_publish);
				ChangeNodeDate(book_head, BOOK, book_id, BOOK_DATE, temp.book_date);

				box_level = 1;

				SetBox(BOX_NO);
				SetMessage(MESSAGE_NO, NULL);
			}
			else
			{
				SetMessage(MESSAGE_YES, "Invalid input !");
			}
		}

		if (button(GenUIID(0), x + w / 4, y - dy * 12, w / 2, h, "Cancel"))
		{
			SetBox(BOX_NO);
			SetMessage(MESSAGE_NO, NULL);
		}
	}
}




//删除图书
void DrawDeleteBookBox(void)
{
	double x = 4.0;
	double y = winheight - GetFontHeight() * 10;
	double w = 1.5;
	double h = GetFontHeight() * 1.5;
	double dx = 1.8;
	double dy = GetFontHeight() * 2.0;

	drawLabel(x, y, "Book ID:");
	static char book_id_str[4] = "1";
	textbox(GenUIID(0), x, y - dy, w, h, book_id_str, sizeof(book_id_str));

	if (button(GenUIID(0), x + w / 4, y - dy * 3, w / 2, h, "OK"))
	{
		int book_id = atoi(book_id_str);

		if (book_id > 0 && book_id <= CheckBookAmount(book_head, SEARCH_ALL) && ReadNodeInt(book_head, BOOK, book_id, BOOK_STATUS) == EXIST)
		{
			DeleteNode(book_head, BOOK, book_id);
			SetBox(BOX_NO);
			SetMessage(MESSAGE_NO, NULL);
		}
		else
		{
			SetMessage(MESSAGE_YES, "Invalid input !");
		}
	}

	if (button(GenUIID(0), x + w / 4, y - dy * 4, w / 2, h, "Cancel"))
	{
		SetBox(BOX_NO);
		SetMessage(MESSAGE_NO, NULL);
	}
}




//审核用户
void DrawPassUserBox(void)
{
	double x = 4.0;
	double y = winheight - GetFontHeight() * 10;
	double w = 1.5;
	double h = GetFontHeight() * 1.5;
	double dx = 1.8;
	double dy = GetFontHeight() * 2.0;

	drawLabel(x, y, "User ID:");
	static char user_id_str[4] = "1";
	textbox(GenUIID(0), x, y - dy, w, h, user_id_str, sizeof(user_id_str));

	if (button(GenUIID(0), x + w / 4, y - dy * 3, w / 2, h, "OK"))
	{
		int user_id = atoi(user_id_str);

		if (user_id > 0 && user_id <= CheckUserAmount(user_head, SEARCH_ALL) && ReadNodeInt(user_head, USER, user_id, USER_STATUS) == NOT_PASS)
		{
			ChangeNodeInt(user_head, USER, user_id, USER_STATUS, EXIST);
			SetBox(BOX_NO);
			SetMessage(MESSAGE_NO, NULL);
		}
		else
		{
			SetMessage(MESSAGE_YES, "Invalid input !");
		}
	}

	if (button(GenUIID(0), x + w / 4, y - dy * 4, w / 2, h, "Cancel"))
	{
		SetBox(BOX_NO);
		SetMessage(MESSAGE_NO, NULL);
	}
}




//编辑用户-Admin模式
void DrawEditUserBoxAdmin(void)
{
	double x = 4.0;
	double y = winheight - GetFontHeight() * 10;
	double w = 1.5;
	double h = GetFontHeight() * 1.5;
	double dx = 1.8;
	double dy = GetFontHeight() * 2.0;

	static int box_level = 1;

	static char user_id_str[4] = "1";
	static int user_id;

	if (box_level == 1)
	{
		drawLabel(x, y, "User ID:");
		textbox(GenUIID(0), x, y - dy, w, h, user_id_str, sizeof(user_id_str));

		if (button(GenUIID(0), x + w / 4, y - dy * 3, w / 2, h, "OK"))
		{
			user_id = atoi(user_id_str);

			if (user_id > 0 && user_id <= CheckUserAmount(user_head, SEARCH_ALL) && ReadNodeInt(user_head, USER, user_id, USER_STATUS) == EXIST)
			{
				box_level = 2;
				SetMessage(MESSAGE_NO, NULL);
			}
			else
			{
				SetMessage(MESSAGE_YES, "Invalid input !");
			}
		}

		if (button(GenUIID(0), x + w / 4, y - dy * 4, w / 2, h, "Cancel"))
		{
			SetBox(BOX_NO);
			SetMessage(MESSAGE_NO, NULL);
		}
	}
	else
	{
		char temp_str[2];

		static struct UserNode temp;

		if (box_level == 2)
			temp = ReadUserNode(user_head, user_id);

		drawLabel(x, y, "User Name:");
		textbox(GenUIID(0), x, y - dy, w, h, temp.user_name, sizeof(temp.user_name));
		
		static char user_sex_str[2];

		if (box_level == 2)
		{
			strcpy(user_sex_str, itoa(temp.user_sex, temp_str, 10));
		}
		
		drawLabel(x, y - dy * 2, "Sex: (Male-0 Female-1)");
		textbox(GenUIID(0), x, y - dy * 3, w, h, user_sex_str, sizeof(user_sex_str));
		

		drawLabel(x, y - dy * 4, "Workplace:");
		textbox(GenUIID(0), x, y - dy * 5, w, h, temp.user_work, sizeof(temp.user_work));

		box_level = 3;

		if (button(GenUIID(0), x + w / 4, y - dy * 7, w / 2, h, "OK"))
		{
			temp.user_sex = atoi(user_sex_str);
			
			if (temp.user_sex == MALE || temp.user_sex == FEMALE)
			{
				ChangeNodeString(user_head, USER, user_id, USER_NAME, temp.user_name);
				ChangeNodeInt(user_head, USER, user_id, USER_SEX, temp.user_sex);
				ChangeNodeString(user_head, USER, user_id, USER_WORK, temp.user_work);

				box_level = 1;

				SetBox(BOX_NO);
				SetMessage(MESSAGE_NO, NULL);
			}
			else
			{
				SetMessage(MESSAGE_YES, "Invalid input !");
			}
		}

		if (button(GenUIID(0), x + w / 4, y - dy * 8, w / 2, h, "Cancel"))
		{
			SetBox(BOX_NO);
			SetMessage(MESSAGE_NO, NULL);
		}
	}
}




//编辑用户-User模式
void DrawEditUserBoxUser(void)
{
	double x = 4.0;
	double y = winheight - GetFontHeight() * 10;
	double w = 1.5;
	double h = GetFontHeight() * 1.5;
	double dx = 1.8;
	double dy = GetFontHeight() * 2.0;

	static int box_level = 1;


	char temp_str[2];

	static struct UserNode temp;

	if (box_level == 1)
		temp = ReadUserNode(user_head, current_user_id);

	drawLabel(x, y, "User Name:");
	textbox(GenUIID(0), x, y - dy, w, h, temp.user_name, sizeof(temp.user_name));

	static char user_sex_str[2];

	if (box_level == 1)
	{
		strcpy(user_sex_str, itoa(temp.user_sex, temp_str, 10));
	}

	drawLabel(x, y - dy * 2, "Sex: (Male-0 Female-1)");
	textbox(GenUIID(0), x, y - dy * 3, w, h, user_sex_str, sizeof(user_sex_str));


	drawLabel(x, y - dy * 4, "Workplace:");
	textbox(GenUIID(0), x, y - dy * 5, w, h, temp.user_work, sizeof(temp.user_work));

	box_level = 2;

	if (button(GenUIID(0), x + w / 4, y - dy * 7, w / 2, h, "OK"))
	{
		temp.user_sex = atoi(user_sex_str);

		if (temp.user_sex == MALE || temp.user_sex == FEMALE)
		{
			ChangeNodeString(user_head, USER, current_user_id, USER_NAME, temp.user_name);
			ChangeNodeInt(user_head, USER, current_user_id, USER_SEX, temp.user_sex);
			ChangeNodeString(user_head, USER, current_user_id, USER_WORK, temp.user_work);

			box_level = 1;

			SetBox(BOX_NO);
			SetMessage(MESSAGE_NO, NULL);
		}
		else
		{
			SetMessage(MESSAGE_YES, "Invalid input !");
		}
	}

	if (button(GenUIID(0), x + w / 4, y - dy * 8, w / 2, h, "Cancel"))
	{
		SetBox(BOX_NO);
		SetMessage(MESSAGE_NO, NULL);
	}
}




//删除用户
void DrawDeleteUserBox(void)
{
	double x = 4.0;
	double y = winheight - GetFontHeight() * 10;
	double w = 1.5;
	double h = GetFontHeight() * 1.5;
	double dx = 1.8;
	double dy = GetFontHeight() * 2.0;

	drawLabel(x, y, "User ID:");
	static char user_id_str[4] = "1";
	textbox(GenUIID(0), x, y - dy, w, h, user_id_str, sizeof(user_id_str));

	if (button(GenUIID(0), x + w / 4, y - dy * 3, w / 2, h, "OK"))
	{
		int user_id = atoi(user_id_str);

		if (user_id > 0 && user_id <= CheckUserAmount(user_head, SEARCH_ALL) && ReadNodeInt(user_head, USER, user_id, USER_STATUS) == EXIST)
		{
			DeleteNode(user_head, USER, user_id);
			SetBox(BOX_NO);
			SetMessage(MESSAGE_NO, NULL);
		}
		else
		{
			SetMessage(MESSAGE_YES, "Invalid input !");
		}
	}

	if (button(GenUIID(0), x + w / 4, y - dy * 4, w / 2, h, "Cancel"))
	{
		SetBox(BOX_NO);
		SetMessage(MESSAGE_NO, NULL);
	}
}




//借书-Admin模式
void DrawBorrowBoxAdmin(void)
{
	double x = 4.0;
	double y = winheight - GetFontHeight() * 10;
	double w = 1.5;
	double h = GetFontHeight() * 1.5;
	double dx = 1.8;
	double dy = GetFontHeight() * 2.0;

	drawLabel(x, y, "Borrow Book ID:");
	static char book_id_str[4] = "1";
	textbox(GenUIID(0), x, y - dy, w, h, book_id_str, sizeof(book_id_str));

	drawLabel(x, y - dy * 2, "Borrow User ID:");
	static char user_id_str[4] = "1";
	textbox(GenUIID(0), x, y - dy * 3, w, h, user_id_str, sizeof(book_id_str));

	drawLabel(x, y - dy * 4, "Borrow Date:");
	static char borrow_date_year[5] = "2020";
	textbox(GenUIID(0), x - dx, y - dy * 5, w, h, borrow_date_year, sizeof(borrow_date_year));
	static char borrow_date_month[3] = "1";
	textbox(GenUIID(0), x, y - dy * 5, w, h, borrow_date_month, sizeof(borrow_date_month));
	static char borrow_date_day[3] = "1";
	textbox(GenUIID(0), x + dx, y - dy * 5, w, h, borrow_date_day, sizeof(borrow_date_day));

	drawLabel(x, y - dy * 6, "Return Date:");
	static char return_date_year[5] = "2020";
	textbox(GenUIID(0), x - dx, y - dy * 7, w, h, return_date_year, sizeof(return_date_year));
	static char return_date_month[3] = "1";
	textbox(GenUIID(0), x, y - dy * 7, w, h, return_date_month, sizeof(return_date_month));
	static char return_date_day[3] = "2";
	textbox(GenUIID(0), x + dx, y - dy * 7, w, h, return_date_day, sizeof(return_date_day));

	if (button(GenUIID(0), x + w / 4, y - dy * 9, w / 2, h, "OK"))
	{
		struct BorrowNode temp;
		temp.book_id = atoi(book_id_str);
		temp.user_id = atoi(user_id_str);
		temp.borrow_date = AddDate(atoi(borrow_date_year), atoi(borrow_date_month), atoi(borrow_date_day));
		temp.return_date = AddDate(atoi(return_date_year), atoi(return_date_month), atoi(return_date_day));

		if 
		(
			temp.book_id > 0
			&& temp.book_id <= CheckBookAmount(book_head, SEARCH_ALL)
			&& ReadNodeInt(book_head, BOOK, temp.book_id, BOOK_STATUS) == EXIST 
			&& temp.user_id > 0
			&& temp.user_id <= CheckUserAmount(user_head, SEARCH_ALL)
			&& ReadNodeInt(user_head, USER, temp.user_id, USER_STATUS) == EXIST 
			&& DateInterval(temp.borrow_date, temp.return_date) > 0
		)
		{
			borrow_head = AddBorrowNode(borrow_head, temp);

			SetBox(BOX_NO);
			SetMessage(MESSAGE_NO, NULL);
		}
		else
		{
			SetMessage(MESSAGE_YES, "Invalid input !");
		}
	}

	if (button(GenUIID(0), x + w / 4, y - dy * 10, w / 2, h, "Cancel"))
	{
		SetBox(BOX_NO);
		SetMessage(MESSAGE_NO, NULL);
	}
}




//借书-User模式
void DrawBorrowBoxUser(void)
{
	double x = 4.0;
	double y = winheight - GetFontHeight() * 10;
	double w = 1.5;
	double h = GetFontHeight() * 1.5;
	double dx = 1.8;
	double dy = GetFontHeight() * 2.0;

	drawLabel(x, y, "Borrow Book ID:");
	static char book_id_str[4] = "1";
	textbox(GenUIID(0), x, y - dy, w, h, book_id_str, sizeof(book_id_str));

	drawLabel(x, y - dy * 4, "Borrow Date:");
	static char borrow_date_year[5] = "2020";
	textbox(GenUIID(0), x - dx, y - dy * 5, w, h, borrow_date_year, sizeof(borrow_date_year));
	static char borrow_date_month[3] = "1";
	textbox(GenUIID(0), x, y - dy * 5, w, h, borrow_date_month, sizeof(borrow_date_month));
	static char borrow_date_day[3] = "1";
	textbox(GenUIID(0), x + dx, y - dy * 5, w, h, borrow_date_day, sizeof(borrow_date_day));


	if (button(GenUIID(0), x + w / 4, y - dy * 9, w / 2, h, "OK"))
	{
		struct BorrowNode temp;
		temp.book_id = atoi(book_id_str);
		temp.user_id = current_user_id;
		temp.borrow_date = AddDate(atoi(borrow_date_year), atoi(borrow_date_month), atoi(borrow_date_day));
		temp.return_date = NextNDate(temp.borrow_date, borrow_day);

		if
		(
			temp.book_id > 0
			&& temp.book_id <= CheckBookAmount(book_head, SEARCH_ALL)
			&& ReadNodeInt(book_head, BOOK, temp.book_id, BOOK_STATUS) == EXIST
			&& temp.user_id > 0
			&& temp.user_id <= CheckUserAmount(user_head, SEARCH_ALL)
			&& ReadNodeInt(user_head, USER, temp.user_id, USER_STATUS) == EXIST  
			&& UserBorrowTimeExist(user_head, temp.user_id, borrow_head) < max_borrow_time
		)
		{
			borrow_head = AddBorrowNode(borrow_head, temp);

			SetBox(BOX_NO);
			SetMessage(MESSAGE_NO, NULL);
		}
		else
		{
			SetMessage(MESSAGE_YES, "Invalid input !");
		}
	}

	if (button(GenUIID(0), x + w / 4, y - dy * 10, w / 2, h, "Cancel"))
	{
		SetBox(BOX_NO);
		SetMessage(MESSAGE_NO, NULL);
	}
}




//还书-Admin模式
void DrawReturnBoxAdmin(void)
{
	double x = 4.0;
	double y = winheight - GetFontHeight() * 10;
	double w = 1.5;
	double h = GetFontHeight() * 1.5;
	double dx = 1.8;
	double dy = GetFontHeight() * 2.0;

	drawLabel(x, y, "Borrow ID:");
	static char borrow_id_str[4] = "1";
	textbox(GenUIID(0), x, y - dy, w, h, borrow_id_str, sizeof(borrow_id_str));

	if (button(GenUIID(0), x + w / 4, y - dy * 3, w / 2, h, "OK"))
	{
		int borrow_id = atoi(borrow_id_str);

		if 
		(
			borrow_id > 0 
			&& borrow_id <= CheckBorrowAmount(borrow_head, SEARCH_ALL) 
			&& ReadNodeInt(borrow_head, BORROW, borrow_id, BORROW_STATUS) == EXIST
		)
		{
			DeleteNode(borrow_head, BORROW, borrow_id);
			SetBox(BOX_NO);
			SetMessage(MESSAGE_NO, NULL);
		}
		else
		{
			SetMessage(MESSAGE_YES, "Invalid input !");
		}
	}

	if (button(GenUIID(0), x + w / 4, y - dy * 4, w / 2, h, "Cancel"))
	{
		SetBox(BOX_NO);
		SetMessage(MESSAGE_NO, NULL);
	}
}




//还书-User模式
void DrawReturnBoxUser(void)
{
	double x = 4.0;
	double y = winheight - GetFontHeight() * 10;
	double w = 1.5;
	double h = GetFontHeight() * 1.5;
	double dx = 1.8;
	double dy = GetFontHeight() * 2.0;

	drawLabel(x, y, "Borrow ID:");
	static char borrow_id_str[4] = "1";
	textbox(GenUIID(0), x, y - dy, w, h, borrow_id_str, sizeof(borrow_id_str));

	if (button(GenUIID(0), x + w / 4, y - dy * 3, w / 2, h, "OK"))
	{
		int borrow_id = atoi(borrow_id_str);

		if 
		(
			borrow_id > 0 
			&& borrow_id <= CheckBorrowAmount(borrow_head, SEARCH_ALL)
			&& ReadNodeInt(borrow_head, BORROW, borrow_id, BORROW_STATUS) == EXIST
			&& ReadNodeInt(borrow_head, BORROW, borrow_id, USER_ID) == current_user_id
		)
		{
			DeleteNode(borrow_head, BORROW, borrow_id);
			SetBox(BOX_NO);
			SetMessage(MESSAGE_NO, NULL);
		}
		else
		{
			SetMessage(MESSAGE_YES, "Invalid input !");
		}
	}

	if (button(GenUIID(0), x + w / 4, y - dy * 4, w / 2, h, "Cancel"))
	{
		SetBox(BOX_NO);
		SetMessage(MESSAGE_NO, NULL);
	}
}




//通过ID搜索图书
void DrawSearchBookIDBox(void)
{
	double x = 4.0;
	double y = winheight - GetFontHeight() * 10;
	double w = 1.5;
	double h = GetFontHeight() * 1.5;
	double dx = 1.8;
	double dy = GetFontHeight() * 2.0;

	drawLabel(x, y, "Book ID:");
	static char book_id_str[4] = "1";
	textbox(GenUIID(0), x, y - dy, w, h, book_id_str, sizeof(book_id_str));

	if (button(GenUIID(0), x + w / 4, y - dy * 3, w / 2, h, "OK"))
	{
		int book_id = atoi(book_id_str);

		if (book_id <= CheckBookAmount(book_head, SEARCH_ALL) && ReadNodeInt(book_head, BOOK, book_id, BOOK_STATUS) == EXIST)
		{
			int* list;

			list = calloc(2, sizeof(int));

			list[0] = book_id;
			
			SetList(LIST_BOOK, list);
			
			SetBox(BOX_NO);
			SetMessage(MESSAGE_NO, NULL);

		}
		else
		{
			SetMessage(MESSAGE_YES, "No result.");
		}
	}

	if (button(GenUIID(0), x + w / 4, y - dy * 4, w / 2, h, "Cancel"))
	{
		SetBox(BOX_NO);
		SetMessage(MESSAGE_NO, NULL);
	}
}




//通过名称模糊搜索图书
void DrawSearchBookNameBox(void)
{
	double x = 4.0;
	double y = winheight - GetFontHeight() * 10;
	double w = 1.5;
	double h = GetFontHeight() * 1.5;
	double dx = 1.8;
	double dy = GetFontHeight() * 2.0;

	drawLabel(x, y, "Book Name:");
	static char book_name[MAX_LEN] = "name";
	textbox(GenUIID(0), x, y - dy, w, h, book_name, sizeof(book_name));

	if (button(GenUIID(0), x + w / 4, y - dy * 3, w / 2, h, "OK"))
	{
		int* list;
		
		list = FuzzySearchNodeString(book_head, BOOK, BOOK_NAME, book_name, SEARCH_EXIST);

		if (list[0] != 0)
		{
			SetList(LIST_BOOK, list);

			SetBox(BOX_NO);
			SetMessage(MESSAGE_NO, NULL);

		}
		else
		{
			SetMessage(MESSAGE_YES, "No result.");
		}
	}

	if (button(GenUIID(0), x + w / 4, y - dy * 4, w / 2, h, "Cancel"))
	{
		SetBox(BOX_NO);
		SetMessage(MESSAGE_NO, NULL);
	}
}




//通过作者模糊搜索图书
void DrawSearchBookWriterBox(void)
{
	double x = 4.0;
	double y = winheight - GetFontHeight() * 10;
	double w = 1.5;
	double h = GetFontHeight() * 1.5;
	double dx = 1.8;
	double dy = GetFontHeight() * 2.0;

	drawLabel(x, y, "Book Writer:");
	static char book_writer[MAX_LEN] = "writer";
	textbox(GenUIID(0), x, y - dy, w, h, book_writer, sizeof(book_writer));

	if (button(GenUIID(0), x + w / 4, y - dy * 3, w / 2, h, "OK"))
	{
		int* list;

		list = FuzzySearchNodeStringArray(book_head, BOOK, BOOK_WRITER, book_writer, SEARCH_EXIST);

		if (list[0] != 0)
		{
			SetList(LIST_BOOK, list);

			SetBox(BOX_NO);
			SetMessage(MESSAGE_NO, NULL);

		}
		else
		{
			SetMessage(MESSAGE_YES, "No result.");
		}
	}

	if (button(GenUIID(0), x + w / 4, y - dy * 4, w / 2, h, "Cancel"))
	{
		SetBox(BOX_NO);
		SetMessage(MESSAGE_NO, NULL);
	}
}




//通过关键词模糊搜索图书
void DrawSearchBookKeywordBox(void)
{
	double x = 4.0;
	double y = winheight - GetFontHeight() * 10;
	double w = 1.5;
	double h = GetFontHeight() * 1.5;
	double dx = 1.8;
	double dy = GetFontHeight() * 2.0;

	drawLabel(x, y, "Book Keyword:");
	static char book_keyword[MAX_LEN] = "key";
	textbox(GenUIID(0), x, y - dy, w, h, book_keyword, sizeof(book_keyword));

	if (button(GenUIID(0), x + w / 4, y - dy * 3, w / 2, h, "OK"))
	{
		int* list;

		list = FuzzySearchNodeStringArray(book_head, BOOK, BOOK_KEYWORD, book_keyword, SEARCH_EXIST);

		if (list[0] != 0)
		{
			SetList(LIST_BOOK, list);

			SetBox(BOX_NO);
			SetMessage(MESSAGE_NO, NULL);

		}
		else
		{
			SetMessage(MESSAGE_YES, "No result.");
		}
	}

	if (button(GenUIID(0), x + w / 4, y - dy * 4, w / 2, h, "Cancel"))
	{
		SetBox(BOX_NO);
		SetMessage(MESSAGE_NO, NULL);
	}
}




//通过ID搜索用户
void DrawSearchUserIDBox(void)
{
	double x = 4.0;
	double y = winheight - GetFontHeight() * 10;
	double w = 1.5;
	double h = GetFontHeight() * 1.5;
	double dx = 1.8;
	double dy = GetFontHeight() * 2.0;

	drawLabel(x, y, "User ID:");
	static char user_id_str[4] = "1";
	textbox(GenUIID(0), x, y - dy, w, h, user_id_str, sizeof(user_id_str));

	if (button(GenUIID(0), x + w / 4, y - dy * 3, w / 2, h, "OK"))
	{
		int user_id = atoi(user_id_str);

		if (user_id <= CheckUserAmount(user_head, SEARCH_ALL) && ReadNodeInt(user_head, USER, user_id, USER_STATUS) == EXIST)
		{
			int* list;

			list = calloc(2, sizeof(int));

			list[0] = user_id;

			SetList(LIST_USER, list);

			SetBox(BOX_NO);
			SetMessage(MESSAGE_NO, NULL);

		}
		else
		{
			SetMessage(MESSAGE_YES, "No result.");
		}
	}

	if (button(GenUIID(0), x + w / 4, y - dy * 4, w / 2, h, "Cancel"))
	{
		SetBox(BOX_NO);
		SetMessage(MESSAGE_NO, NULL);
	}
}




//通过名称模糊搜索用户
void DrawSearchUserNameBox(void)
{
	double x = 4.0;
	double y = winheight - GetFontHeight() * 10;
	double w = 1.5;
	double h = GetFontHeight() * 1.5;
	double dx = 1.8;
	double dy = GetFontHeight() * 2.0;

	drawLabel(x, y, "User Name:");
	static char user_name[MAX_LEN] = "name";
	textbox(GenUIID(0), x, y - dy, w, h, user_name, sizeof(user_name));

	if (button(GenUIID(0), x + w / 4, y - dy * 3, w / 2, h, "OK"))
	{
		int* list;

		list = FuzzySearchNodeString(user_head, USER, USER_NAME, user_name, SEARCH_EXIST);

		if (list[0] != 0)
		{
			SetList(LIST_USER, list);

			SetBox(BOX_NO);
			SetMessage(MESSAGE_NO, NULL);

		}
		else
		{
			SetMessage(MESSAGE_YES, "No result.");
		}
	}

	if (button(GenUIID(0), x + w / 4, y - dy * 4, w / 2, h, "Cancel"))
	{
		SetBox(BOX_NO);
		SetMessage(MESSAGE_NO, NULL);
	}
}




//通过工作单位模糊搜索用户
void DrawSearchUserWorkBox(void)
{
	double x = 4.0;
	double y = winheight - GetFontHeight() * 10;
	double w = 1.5;
	double h = GetFontHeight() * 1.5;
	double dx = 1.8;
	double dy = GetFontHeight() * 2.0;

	drawLabel(x, y, "User Workplace:");
	static char user_work[MAX_LEN] = "work";
	textbox(GenUIID(0), x, y - dy, w, h, user_work, sizeof(user_work));

	if (button(GenUIID(0), x + w / 4, y - dy * 3, w / 2, h, "OK"))
	{
		int* list;

		list = FuzzySearchNodeString(user_head, USER, USER_WORK, user_work, SEARCH_EXIST);

		if (list[0] != 0)
		{
			SetList(LIST_USER, list);

			SetBox(BOX_NO);
			SetMessage(MESSAGE_NO, NULL);
		}
		else
		{
			SetMessage(MESSAGE_YES, "No result.");
		}
	}

	if (button(GenUIID(0), x + w / 4, y - dy * 4, w / 2, h, "Cancel"))
	{
		SetBox(BOX_NO);
		SetMessage(MESSAGE_NO, NULL);
	}
}




//数量统计
void DrawStatAmountBox(void)
{
	double x = 3.5;
	double y = winheight - GetFontHeight() * 10;
	double w = 1.5;
	double h = GetFontHeight() * 1.5;
	double dx = 1.8;
	double dy = GetFontHeight() * 2.0;

	if (book_head == NULL || user_head == NULL || borrow_head == NULL)
	{	
		SetMessage(MESSAGE_YES, "Need more data for stat.");
	}
	else
	{
		char temp_str[5]; //满足itoa函数的参数需要

		//书的总量
		drawLabel(x, y, "Total Book:");
		drawLabel(x + dx, y, itoa(CheckBookAmount(book_head, SEARCH_EXIST), temp_str, 10));

		//当前被借出的数量
		drawLabel(x, y - dy, "Lent Book:");
		drawLabel(x + dx, y - dy, itoa(CheckBorrowAmount(borrow_head, SEARCH_EXIST), temp_str, 10));

		//最多的关键词
		drawLabel(x, y - dy * 2, "Most Book Keyword:");
		drawLabel(x + dx, y - dy * 2, FindMostBookKey(book_head));

		//最受欢迎的的书
		drawLabel(x, y - dy * 3, "Most Favorite Book:");
		drawLabel(x + dx, y - dy * 3, ReadNodeString(book_head, BOOK, FindMostFavoriteBook(book_head, borrow_head), BOOK_NAME));

		//最不受欢迎的的书
		drawLabel(x, y - dy * 4, "Least Favorite Book:");
		drawLabel(x + dx, y - dy * 4, ReadNodeString(book_head, BOOK, FindLeastFavoriteBook(book_head, borrow_head), BOOK_NAME));

		//用户总数
		drawLabel(x, y - dy * 5, "Total User:");
		drawLabel(x + dx, y - dy * 5, itoa(CheckUserAmount(user_head, SEARCH_EXIST), temp_str, 10));

		//借书次数最多的用户
		drawLabel(x, y - dy * 6, "Most Borrow User:");
		drawLabel(x + dx, y - dy * 6, ReadNodeString(user_head, USER, FindMostBorrowUser(user_head, borrow_head), USER_NAME));

		//借阅总次数
		drawLabel(x, y - dy * 7, "Total lent time:");
		drawLabel(x + dx, y - dy * 7, itoa(CheckBorrowAmount(borrow_head, SEARCH_ALL), temp_str, 10));
	}


	if (button(GenUIID(0), x + w / 2, y - dy * 9, w / 2, h, "OK"))
	{
		SetBox(BOX_NO);
		SetMessage(MESSAGE_NO, NULL);
	}
}




//频率统计
void DrawStatFreqBox(void)
{
	//图形相关
	double x = 3.5;
	double y = winheight - GetFontHeight() * 10;
	double dx = 0.6;
	double dy = GetFontHeight() * 1.5;
	
	double w = 1.5;
	double h = GetFontHeight() * 1.5;

	int i = 0;


	if (book_head == NULL || user_head == NULL || borrow_head == NULL)
	{
		SetMessage(MESSAGE_YES, "Need more data for stat.");
	}
	else
	{
		drawLabel
		(
			x,
			y,
			"ID    Name                          Lent Freq"
		);

		int* list = SortBookNode(book_head, BOOK_ID, ASCENDING);

		for ( ; list[i] != 0; i++) //按列显示
		{
			char temp_str[10]; //满足sprintf函数的参数需要
			char(*p_keyword)[MAX_LEN] = ReadNodeStringArray(book_head, BOOK, list[i], BOOK_KEYWORD);
			char(*p_writer)[MAX_LEN] = ReadNodeStringArray(book_head, BOOK, list[i], BOOK_WRITER);

			//ID
			drawLabel(x, y - dy * (i + 1), itoa(list[i], temp_str, 10));

			//书名
			drawLabel(x + dx * 0.5, y - dy * (i + 1), ReadNodeString(book_head, BOOK, list[i], BOOK_NAME));

			//频率
			sprintf(temp_str, "%.2f %%", ((double)BookBorrowTime(book_head, list[i], borrow_head) / CheckBorrowAmount(borrow_head, SEARCH_ALL)) * 100.0);
			drawLabel(x + dx * 3, y - dy * (i + 1), temp_str);
		}
	}

	if (button(GenUIID(0), x + w / 2, y - dy * (i + 2), w / 2, h, "OK"))
	{
		SetBox(BOX_NO);
		SetMessage(MESSAGE_NO, NULL);
	}
}




//设置借阅天数
void DrawSetBorrowDay(void)
{
	double x = 4.0;
	double y = winheight - GetFontHeight() * 10;
	double w = 1.5;
	double h = GetFontHeight() * 1.5;
	double dx = 1.8;
	double dy = GetFontHeight() * 2.0;

	static int box_open_time = 1;

	char temp_str[4];
	static char borrow_day_str[10];

	if (box_open_time == 1)
	{
		strcpy(borrow_day_str, itoa(borrow_day, temp_str, 10));
	}

	box_open_time++;

	drawLabel(x, y, "Borrow Day:");
	textbox(GenUIID(0), x, y - dy, w, h, borrow_day_str, sizeof(borrow_day_str));

	if (button(GenUIID(0), x + w / 4, y - dy * 3, w / 2, h, "OK"))
	{
		int borrow_day_int = atoi(borrow_day_str);

		if (borrow_day_int >= 1)
		{
			borrow_day = borrow_day_int;

			box_open_time = 1;

			SetBox(BOX_NO);
			SetMessage(MESSAGE_NO, NULL);

		}
		else
		{
			SetMessage(MESSAGE_YES, "Invalid input !");
		}
	}

	if (button(GenUIID(0), x + w / 4, y - dy * 4, w / 2, h, "Cancel"))
	{
		SetBox(BOX_NO);
		SetMessage(MESSAGE_NO, NULL);
	}
}




//设置最大借阅数量
void DrawSetMaxBorrowTime(void)
{
	double x = 4.0;
	double y = winheight - GetFontHeight() * 10;
	double w = 1.5;
	double h = GetFontHeight() * 1.5;
	double dx = 1.8;
	double dy = GetFontHeight() * 2.0;

	static int box_open_time = 1;

	char temp_str[4];
	static char borrow_time_str[10];

	if (box_open_time == 1)
	{
		strcpy(borrow_time_str, itoa(max_borrow_time, temp_str, 10));
	}


	box_open_time++;

	drawLabel(x, y, "Max Borrow Book Amount:");
	textbox(GenUIID(0), x, y - dy, w, h, borrow_time_str, sizeof(borrow_time_str));

	if (button(GenUIID(0), x + w / 4, y - dy * 3, w / 2, h, "OK"))
	{
		int borrow_time_int = atoi(borrow_time_str);

		if (borrow_time_int >= 1)
		{
			max_borrow_time = borrow_time_int;

			SetBox(BOX_NO);
			SetMessage(MESSAGE_NO, NULL);
		}
		else
		{
			SetMessage(MESSAGE_YES, "Invalid input !");
		}
	}

	if (button(GenUIID(0), x + w / 4, y - dy * 4, w / 2, h, "Cancel"))
	{
		SetBox(BOX_NO);
		SetMessage(MESSAGE_NO, NULL);
	}
}




//显示版本信息
void DrawVersionBox(void)
{
	double x = 4.0;
	double y = winheight - GetFontHeight() * 10;
	double w = 1.5;
	double h = GetFontHeight() * 1.5;
	double dx = 1.8;
	double dy = GetFontHeight() * 2.0;

	drawLabel(x, y, "Library Manager v1.2");
	drawLabel(x, y - dy, "Copyright(C)2020 GHL-Group");

	if (button(GenUIID(0), x + w / 4, y - dy * 3, w / 2, h, "OK"))
	{
		SetBox(BOX_NO);
	}
}




//显示帮助信息
void DrawHelpBox(void)
{
	double x = 3.0;
	double y = winheight - GetFontHeight() * 10;
	double w = 1.5;
	double h = GetFontHeight() * 1.5;
	double dx = 1.8;
	double dy = GetFontHeight() * 2.0;

	drawLabel(x, y, "LManager is a simple library manage system.");
	drawLabel(x, y - dy, "The default database is book1 and borrow1.");
	drawLabel(x, y - dy * 2, "You can find detailed usage in our report.");

	if (button(GenUIID(0), x + w / 2, y - dy * 4, w / 2, h, "OK"))
	{
		SetBox(BOX_NO);
	}
}




//绘制图标-Vistor模式
void DrawButtonBoxVistor(void)
{
	double w = 0.2;
	double h = w;
	double dx = 0.3;
	double x = winwidth - 5 * dx;
	double y = 0.01;



	if (button(GenUIID(0), x, y, w, h, "+"))
	{
		SetBox(REGISTER);
	}

	if (button(GenUIID(0), x + dx, y, w, h, "L"))
	{
		SetBox(USER_LOG);
	}

	if (button(GenUIID(0), x + dx * 2, y, w, h, "A"))
	{
		SetBox(ADMIN_LOG);
	}

	if (button(GenUIID(0), x + dx * 3, y, w, h, "V"))
	{
		SetBox(VERSION);
	}

	if (button(GenUIID(0), x + dx * 4, y, w, h, "X"))
	{
		exit(0);
	}
}




//绘制图标-User模式
void DrawButtonBoxUser(void)
{
	double w = 0.2;
	double h = w;
	double dx = 0.3;
	double x = winwidth - 5 * dx;
	double y = 0.01;



	if (button(GenUIID(0), x, y, w, h, "+"))
	{
		SetBox(BORROW_BOOK_USER);
	}

	if (button(GenUIID(0), x + dx, y, w, h, "B"))
	{
		SetBox(RETURN_BOOK_USER);
	}

	if (button(GenUIID(0), x + dx * 2, y, w, h, "L"))
	{
		SetList(LIST_BORROW_USER, SortBorrowNode(borrow_head, BOOK_ID, ASCENDING));
	}

	if (button(GenUIID(0), x + dx * 3, y, w, h, "E"))
	{
		SetBox(EDIT_USER_USER);
	}

	if (button(GenUIID(0), x + dx * 4, y, w, h, "X"))
	{
		exit(0);
	}
}




//绘制图标-Admin模式
void DrawButtonBoxAdmin(void)
{
	double w = 0.2;
	double h = w;
	double dx = 0.3;
	double x = winwidth - 5 * dx;
	double y = 0.01;
	


	if (button(GenUIID(0), x, y, w, h, "+"))
	{
		SetBox(ADD_BOOK);
	}

	if (button(GenUIID(0), x + dx, y, w, h, "-"))
	{
		SetBox(DELETE_BOOK);
	}

	if (button(GenUIID(0), x + dx * 2, y, w, h, "L"))
	{
		SetList(LIST_BOOK, SortBookNode(book_head, BOOK_ID, ASCENDING));
	}
	
	if (button(GenUIID(0), x + dx * 3, y, w, h, "E"))
	{
		SetBox(EDIT_BOOK);
	}

	if (button(GenUIID(0), x + dx * 4, y, w, h, "X"))
	{
		exit(0);
	}
}




//设置显示内容
void SetBox(int set_box_content)
{
	box_content = set_box_content;
}




//显示交互窗口
void DrawBox(void)
{
	if (box_content != BOX_NO)
		SetList(LIST_NO, NULL);

	switch (log_status)
	{
	case VISTOR: DrawButtonBoxVistor(); break;
	case USER: DrawButtonBoxUser(); break;
	case ADMIN: DrawButtonBoxAdmin();
	}

	switch (box_content)
	{
	case REGISTER: DrawRegisterBox(); break;
	case USER_LOG: DrawUserLogBox(); break;
	case ADMIN_LOG: DrawAdminLogBox(); break;
	case OPEN_DB: DrawFileOpenBox(); break;
	case ADD_BOOK: DrawAddBookBox(); break;
	case EDIT_BOOK: DrawEditBookBox(); break;
	case DELETE_BOOK: DrawDeleteBookBox(); break;
	case PASS: DrawPassUserBox(); break;
	case EDIT_USER_ADMIN: DrawEditUserBoxAdmin(); break;
	case EDIT_USER_USER: DrawEditUserBoxUser(); break;
	case DELETE_USER: DrawDeleteUserBox(); break;
	case BORROW_BOOK_ADMIN: DrawBorrowBoxAdmin(); break;
	case BORROW_BOOK_USER: DrawBorrowBoxUser(); break;
	case RETURN_BOOK_ADMIN: DrawReturnBoxAdmin(); break;
	case RETURN_BOOK_USER: DrawReturnBoxUser(); break;
	case SEARCH_BOOK_ID: DrawSearchBookIDBox(); break;
	case SEARCH_BOOK_NAME: DrawSearchBookNameBox(); break;
	case SEARCH_BOOK_WRITER: DrawSearchBookWriterBox(); break;
	case SEARCH_BOOK_KEYWORD: DrawSearchBookKeywordBox(); break;
	case SEARCH_USER_ID: DrawSearchUserIDBox(); break;
	case SEARCH_USER_NAME: DrawSearchUserNameBox(); break;
	case SEARCH_USER_WORK: DrawSearchUserWorkBox(); break;
	case STAT_AMOUNT: DrawStatAmountBox(); break;
	case STAT_FREQ:	DrawStatFreqBox(); break;
	case SET_BORROW_DAY: DrawSetBorrowDay(); break;
	case SET_BORROW_TIME: DrawSetMaxBorrowTime(); break;
	case VERSION: DrawVersionBox(); break;
	case HELP: DrawHelpBox();
	}
}