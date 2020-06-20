/*
文件：main.c

作者：李培生
*/




#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>
#include "graphics.h"
#include "extgraph.h"
#include "imgui.h"


#include "database.h"
#include "file.h"
#include "list.h"
#include "menu.h"
#include "box.h"
#include "message.h"




//登录状态的宏定义
#define VISTOR 0
#define USER 1
#define ADMIN 2




//全局变量
struct BookNode* book_head; //当前打开的图书链表
struct UserNode* user_head; //当前打开的用户链表
struct BorrowNode* borrow_head; //当前打开的借阅链表

int log_status = VISTOR; //当前登录状态，默认为Vistor

int current_user_id; //当前用户id（User模式）

int db_num; //当前打开的图书/借阅库的序号

int borrow_day; //当前设置的借阅天数
int max_borrow_time; //当前设置的最大借阅数量

double winheight; //窗口高度
double winwidth; //窗口宽度




//清屏函数的声明
void DisplayClear(void); 


//显示函数的声明
void Display(void); 


//键盘回调函数
void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key, event);
	Display();
}


//鼠标回调函数
void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x, y, button, event);
	Display(); 
}


//字符回调函数
void CharEventProcess(char ch)
{
	uiGetChar(ch);
	Display();
}




//主函数
void Main() 
{
	SetWindowTitle("Library Manager v1.2 by GHL-Group"); //设置程序名称
	
    InitGraphics(); //初始化图形界面

	//获得窗口信息
    winwidth = GetWindowWidth();
    winheight = GetWindowHeight();

	//设置配色
	usePredefinedColors(3);


	//注册回调函数
	registerKeyboardEvent(KeyboardEventProcess);
	registerMouseEvent(MouseEventProcess); 
	registerCharEvent(CharEventProcess);


	//获得当前图书/借阅库的数量
	db_num = FileCheckInfo();

	if (db_num >= 1) //数量大于等于1，默认打开序号为1的图书/借阅库
	{
		book_head = FileReadBook(1);
		borrow_head = FileReadBorrow(1);
	}
	else //不存在图书/借阅库，自动创建库并更新数量信息
	{
		db_num = FileUpdateInfo();
	}
	

	//检测用户库是否存在，若不存在则新建用户库
	FileCheckUser();
	
	//打开用户库
	user_head = FileReadUser();


	//获得当前借阅设置
	borrow_day = FileCheckBorrowDay();
	max_borrow_time = FileCheckBorrowTime();
}




//显示函数的定义
void Display()
{
	DisplayClear(); //清屏


	DrawMenu(); //显示菜单

	DrawList(); //显示列表

	DrawBox(); //显示交互窗口

	DrawMessage(); //显示消息
}