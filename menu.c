/*
文件：menu.c

作者：李培生

内容：
控制菜单的函数的定义。
*/




#include <stdlib.h>
#include "graphics.h"
#include "extgraph.h"
#include "imgui.h"


#include "database.h"
#include "list.h"
#include "sort.h"
#include "box.h"
#include "file.h"


#include "menu.h"




//外部全局变量
extern struct BookNode* book_head; //当前打开的图书链表
extern struct UserNode* user_head; //当前打开的用户链表
extern struct BorrowNode* borrow_head; //当前打开的借阅链表

extern int log_status; //当前登录状态

extern int db_num; //当前打开的图书/借阅库的序号

extern int borrow_day; //当前设置的借阅天数
extern int max_borrow_time; //当前设置的最大借阅数量

extern double winheight; //窗口高度




//菜单显示
void DrawMenu(void)
{ 
    //菜单图形参数
    double x = 0;
    double w = TextStringWidth("Book Srch") * 1.2;
    double wlist = TextStringWidth("Book Keyword | Ctrl - K");
    double h = GetFontHeight() * 1.5;
    double y = winheight - h;

    switch (log_status)
    {
    case VISTOR: //VISTOR模式
    {
        //VISTOR模式-文件菜单
        char* menuListFile[] =
        {
            "File",
            "Exit | Ctrl-E"
        };

        int File_select = menuList
        (
            GenUIID(0),
            x,
            y,
            w,
            wlist,
            h,
            menuListFile,
            sizeof(menuListFile) / sizeof(menuListFile[0])
        );

        if (File_select == 1) //VISTOR模式-退出
        {
            exit(0);
        }

        //VISTOR模式-用户菜单
        char* menuListUser[] =
        {
            "User",
            "Register | Ctrl-R",
            "Log | Ctrl-L",
            "Admin | Ctrl-A"
        };

        int User_select = menuList
        (
            GenUIID(0),
            x + w,
            y,
            w,
            wlist,
            h,
            menuListUser,
            sizeof(menuListUser) / sizeof(menuListUser[0])
        );

        switch (User_select)
        {
        case 1: //VISTOR模式-注册
        {
            SetBox(REGISTER);

            FileWriteUser(user_head);
        }
        break;

        case 2: //VISTOR模式-普通用户登录
        {
            SetBox(USER_LOG);
        }
        break;

        case 3: //VISTOR模式-管理员登录
        {
            SetBox(ADMIN_LOG);
        }
        }

        //VISTOR模式-关于菜单
        char* menuListAbout[] =
        {
            "About",
            "Version",
            "Help | Ctrl-H"
        };

        int About_select = menuList
        (
            GenUIID(0),
            x + 2 * w,
            y,
            w,
            wlist,
            h,
            menuListAbout,
            sizeof(menuListAbout) / sizeof(menuListAbout[0])
        );

        switch (About_select)
        {
        case 1: //VISTOR模式-版本
        {
            SetBox(VERSION);
        }
        break;

        case 2: //VISTOR模式-帮助
        {
            SetBox(HELP);
        }
        }
    }
    break;

    case USER: //USER模式
    {
        //USER模式-文件菜单
        char* menuListFile[] =
        {
            "File",
            "Open | Ctrl-O",
            "Save | Ctrl-S",
            "Exit | Ctrl-E"
        };

        int File_select = menuList
        (
            GenUIID(0),
            x,
            y,
            w,
            wlist,
            h,
            menuListFile,
            sizeof(menuListFile) / sizeof(menuListFile[0])
        );

        switch (File_select)
        {
        case 1: //USER模式-打开图书和借阅库
        {
            SetBox(OPEN_DB);
        }
        break;

        case 2: //USER模式-保存
        {
            SetList(LIST_NO, NULL);
            SetBox(BOX_NO);

            FileWriteUser(user_head);
            FileWriteBorrow(borrow_head, db_num);
        }
        break;

        case 3: //USER模式-退出
        {
            exit(0);
        }
        }

        //USER模式-图书菜单
        char* menuListBook[] =
        {
            "Book",
            "List | Ctrl-L"
        };

        int Book_select = menuList
        (
            GenUIID(0),
            x + w,
            y,
            w,
            wlist,
            h,
            menuListBook,
            sizeof(menuListBook) / sizeof(menuListBook[0])
        );

        if (Book_select == 1) //USER模式-列出图书
        {
            SetList(LIST_BOOK, SortBookNode(book_head, BOOK_ID, ASCENDING));
        }

        //USER模式-用户菜单
        char* menuListUser[] =
        {
            "User",
            "Edit"
        };

        int User_select = menuList
        (
            GenUIID(0),
            x + 2 * w,
            y,
            w,
            wlist,
            h,
            menuListUser,
            sizeof(menuListUser) / sizeof(menuListUser[0])
        );


        if (User_select == 1)
        {
            SetBox(EDIT_USER_USER);
        }
        

        //USER模式-借阅菜单
        char* menuListService[] =
        {
            "Service",
            "List",
            "Borrow | Ctrl-B",
            "Return | Ctrl-R"
        };

        int Service_select = menuList
        (
            GenUIID(0),
            x + 3 * w,
            y,
            w,
            wlist,
            h,
            menuListService,
            sizeof(menuListService) / sizeof(menuListService[0])
        );

        switch (Service_select)
        {
        case 1: //USER模式-列出本用户借阅
        {
            SetList(LIST_BORROW_USER, SortBorrowNode(borrow_head, BORROW_ID, ASCENDING));
        }
        break;

        case 2: //USER模式-借阅
        {
            SetBox(BORROW_BOOK_USER);
        }
        break;

        case 3: //USER模式-归还
        {
            SetBox(RETURN_BOOK_USER);
        }
        break;
        }

        //USER模式-排序菜单
        char* menuListSort[] =
        {
            "Sort",
            "Book Name | Ctrl-N",
            "Book Writer | Ctrl-W"
        };

        int Sort_select = menuList
        (
            GenUIID(0),
            x + 4 * w,
            y,
            w,
            wlist,
            h,
            menuListSort,
            sizeof(menuListSort) / sizeof(menuListSort[0])
        );

        switch (Sort_select)
        {
        case 1: //USER模式-按书名排序
        {
            SetList(LIST_BOOK, SortBookNode(book_head, BOOK_NAME, ASCENDING));
        }
        break;

        case 2: //USER模式-按第一作者排序
        {
            SetList(LIST_BOOK, SortBookNode(book_head, BOOK_WRITER, ASCENDING));
        }
        }

        //USER模式-图书搜索菜单
        char* menuListBookSearch[] =
        {
            "Book Srch",
            "Book ID | Ctrl-I",
            "Book Name",
            "Book Writer",
            "Book Keyword | Ctrl-K"
        };

        int BookSearch_select = menuList
        (
            GenUIID(0),
            x + 5 * w,
            y,
            w,
            wlist,
            h,
            menuListBookSearch,
            sizeof(menuListBookSearch) / sizeof(menuListBookSearch[0])
        );

        switch (BookSearch_select)
        {
        case 1: //USER模式-按图书ID搜索
        {
            SetBox(SEARCH_BOOK_ID);
        }
        break;

        case 2: //USER模式-按图书名模糊搜索
        {
            SetBox(SEARCH_BOOK_NAME);
        }
        break;

        case 3: //USER模式-按图书作者模糊搜索
        {
            SetBox(SEARCH_BOOK_WRITER);
        }
        break;

        case 4: //USER模式-按图书关键词模糊搜索
        {
            SetBox(SEARCH_BOOK_KEYWORD);
        }
        }

        //USER模式-关于菜单
        char* menuListAbout[] =
        {
            "About",
            "Version",
            "Help | Ctrl-H"
        };

        int About_select = menuList
        (
            GenUIID(0),
            x + 6 * w,
            y,
            w,
            wlist,
            h,
            menuListAbout,
            sizeof(menuListAbout) / sizeof(menuListAbout[0])
        );

        switch (About_select)
        {
        case 1: //USER模式-版本
        {
            SetBox(VERSION);
        }
        break;

        case 2: //USER模式-帮助
        {
            SetBox(HELP);
        }
        }
    }
    break;


    //ADMIN模式
    case ADMIN:
    {
        //ADMIN模式-文件菜单
        char* menuListFile[] =
        {
            "File",
            "New | Ctrl-N",
            "Open | Ctrl-O",
            "Save | Ctrl-S",
            "Exit | Ctrl-E"
        };

        int File_select = menuList
        (
            GenUIID(0),
            x,
            y,
            w,
            wlist,
            h,
            menuListFile,
            sizeof(menuListFile) / sizeof(menuListFile[0])
        );

        switch (File_select)
        {
        case 1: //ADMIN模式-新建图书和借阅库
        {
            SetList(LIST_NO, NULL);
            SetBox(BOX_NO);
            
            int db_num = FileUpdateInfo();
            book_head = FileReadBook(db_num);
            borrow_head = FileReadBorrow(db_num);
        }
        break;

        case 2: //ADMIN模式-打开图书和借阅库
        {
            SetBox(OPEN_DB);
        }
        break;

        case 3: //ADMIN模式-保存
        {
            SetList(LIST_NO, NULL);
            SetBox(BOX_NO);
            
            FileWriteBook(book_head, db_num);
            FileWriteUser(user_head);
            FileWriteBorrow(borrow_head, db_num);
            FileWriteBorrowDay(borrow_day);
            FileWriteBorrowTime(max_borrow_time);
        }
        break;

        case 4: //ADMIN模式-退出
        {
            exit(0);
        }
        }

        //ADMIN模式-图书菜单
        char* menuListBook[] =
        {
            "Book",
            "New",
            "List | Ctrl-L",
            "Edit",
            "Delete | Ctrl-D"
        };

        int Book_select = menuList
        (
            GenUIID(0),
            x + w,
            y,
            w,
            wlist,
            h,
            menuListBook,
            sizeof(menuListBook) / sizeof(menuListBook[0])
        );

        switch (Book_select)
        {
        case 1: //ADMIN模式-新建图书
        {
            SetBox(ADD_BOOK);
        }
        break;

        case 2: //ADMIN模式-列出图书
        {
            SetList(LIST_BOOK, SortBookNode(book_head, BOOK_ID, ASCENDING));
        }
        break;

        case 3: //ADMIN模式-编辑图书
        {
            SetBox(EDIT_BOOK);
        }
        break;

        case 4: //ADMIN模式-删除图书
        {
            SetBox(DELETE_BOOK);
        }
        }

        //ADMIN模式-用户菜单
        char* menuListUser[] =
        {
            "User",
            "Pass | Ctrl-P",
            "List",
            "Edit",
            "Delete"
        };

        int User_select = menuList
        (
            GenUIID(0),
            x + 2 * w,
            y,
            w,
            wlist,
            h,
            menuListUser,
            sizeof(menuListUser) / sizeof(menuListUser[0])
        );

        switch (User_select)
        {
        case 1: //ADMIN模式-通过用户
        {
            SetBox(PASS);
        }
        break;
        
        case 2: //ADMIN模式-列出用户
        {
            SetList(LIST_USER, SortUserNode(user_head, USER_ID, ASCENDING));
        }
        break;

        case 3: //ADMIN模式-编辑用户
        {
            SetBox(EDIT_USER_ADMIN);
        }
        break;

        case 4: //ADMIN模式-删除用户
        {
            SetBox(DELETE_USER);
        }
        }

        //ADMIN模式-借阅菜单
        char* menuListService[] =
        {
            "Service",
            "List",
            "Borrow | Ctrl-B",
            "Return | Ctrl-R"
        };

        int Service_select = menuList
        (
            GenUIID(0),
            x + 3 * w,
            y,
            w,
            wlist,
            h,
            menuListService,
            sizeof(menuListService) / sizeof(menuListService[0])
        );

        switch (Service_select)
        {
        case 1: //ADMIN模式-列出借阅
        {
            SetList(LIST_BORROW_ADMIN, SortBorrowNode(borrow_head, BORROW_ID, ASCENDING));
        }
        break;
        
        case 2: //ADMIN模式-借阅
        {
            SetBox(BORROW_BOOK_ADMIN);
        }
        break;

        case 3: //ADMIN模式-归还
        {
            SetBox(RETURN_BOOK_ADMIN);
        }
        }

        //ADMIN模式-排序菜单
        char* menuListSort[] =
        {
            "Sort",
            "Book Name",
            "Book Writer | Ctrl-W",
            "User Name",
            "User Workplace"
        };

        int Sort_select = menuList
        (
            GenUIID(0),
            x + 4 * w,
            y,
            w,
            wlist,
            h,
            menuListSort,
            sizeof(menuListSort) / sizeof(menuListSort[0])
        );

        switch (Sort_select)
        {
        case 1: //ADMIN模式-按书名排序
        {
            SetList(LIST_BOOK, SortBookNode(book_head, BOOK_NAME, ASCENDING));
        }
        break;

        case 2: //ADMIN模式-按第一作者排序
        {
            SetList(LIST_BOOK, SortBookNode(book_head, BOOK_WRITER, ASCENDING));
        }
        break;

        case 3: //ADMIN模式-按用户名排序
        {
            SetList(LIST_USER, SortUserNode(user_head, USER_NAME, ASCENDING));
        }
        break;

        case 4: //ADMIN模式-按工作单位排序
        {
            SetList(LIST_USER, SortUserNode(user_head, USER_WORK, ASCENDING));
        }
        }

        //ADMIN模式-图书搜索菜单
        char* menuListBookSearch[] =
        {
            "Book Srch",
            "Book ID | Ctrl-I",
            "Book Name",
            "Book Writer",
            "Book Keyword | Ctrl-K"
        };

        int BookSearch_select = menuList
        (
            GenUIID(0),
            x + 5 * w,
            y,
            w,
            wlist,
            h,
            menuListBookSearch,
            sizeof(menuListBookSearch) / sizeof(menuListBookSearch[0])
        );

        switch (BookSearch_select)
        {
        case 1: //ADMIN模式-按图书ID搜索
        {
            SetBox(SEARCH_BOOK_ID);
        }
        break;

        case 2: //ADMIN模式-按图书名模糊搜索
        {
            SetBox(SEARCH_BOOK_NAME);
        }
        break;

        case 3: //ADMIN模式-按图书作者模糊搜索
        {
            SetBox(SEARCH_BOOK_WRITER);
        }
        break;

        case 4: //ADMIN模式-按图书关键词模糊搜索
        {
            SetBox(SEARCH_BOOK_KEYWORD);
        }
        }

        //ADMIN模式-用户搜索菜单
        char* menuListUserSearch[] =
        {
            "User Srch",
            "User ID",
            "User Name",
            "User Workplace"
        };

        int UserSearch_select = menuList
        (
            GenUIID(0),
            x + 6 * w,
            y,
            w,
            wlist,
            h,
            menuListUserSearch,
            sizeof(menuListUserSearch) / sizeof(menuListUserSearch[0])
        );

        switch (UserSearch_select)
        {
        case 1: //ADMIN模式-按用户ID搜索
        {
            SetBox(SEARCH_USER_ID);
        }
        break;

        case 2: //ADMIN模式-按用户名模糊搜索
        {
            SetBox(SEARCH_USER_NAME);
        }
        break;

        case 3: //ADMIN模式-按用户工作单位模糊搜索
        {
            SetBox(SEARCH_USER_WORK);
        }
        }

        //ADMIN模式-统计菜单
        char* menuListStat[] =
        {
            "Stat",
            "Amount | Ctrl-A",
            "Frequency | Ctrl-F"        
        };

        int Stat_select = menuList
        (
            GenUIID(0),
            x + 7 * w,
            y,
            w,
            wlist,
            h,
            menuListStat,
            sizeof(menuListStat) / sizeof(menuListStat[0])
        );

        switch (Stat_select)
        {
        case 1: //ADMIN模式-按数量统计
        {
            SetBox(STAT_AMOUNT);
        }
        break;

        case 2: //ADMIN模式-按频率统计
        {
            SetBox(STAT_FREQ);
        }
        }

        //ADMIN模式-设置菜单
        char* menuListSet[] =
        {
            "Setting",
            "Borrow Day",
            "Borrow Times"
        };

        int Set_select = menuList
        (
            GenUIID(0),
            x + 8 * w,
            y,
            w,
            wlist,
            h,
            menuListSet,
            sizeof(menuListSet) / sizeof(menuListSet[0])
        );

        switch (Set_select)
        {
        case 1: //ADMIN模式-设置借阅天数
        {
            SetBox(SET_BORROW_DAY);
        }
        break;

        case 2: //ADMIN模式-设置最大借阅次数
        {
            SetBox(SET_BORROW_TIME);
        }
        }

        //ADMIN模式-关于菜单
        char* menuListAbout[] =
        {
            "About",
            "Version",
            "Help | Ctrl-H"
        };

        int About_select = menuList
        (
            GenUIID(0),
            x + 9 * w,
            y,
            w,
            wlist,
            h,
            menuListAbout,
            sizeof(menuListAbout) / sizeof(menuListAbout[0])
        );

        switch (About_select)
        {
        case 1: //ADMIN模式-版本
        {
            SetBox(VERSION);
        }
        break;

        case 2: //ADMIN模式-帮助
        {
            SetBox(HELP);
        }
        }
    }
    }
}