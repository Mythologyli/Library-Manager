/*
文件：message.c

作者：李培生

内容：
控制消息有无的全局变量；
消息字符串的全局变量；
设置显示内容的函数的声明；
消息显示的函数的声明。
*/




#include <string.h>
#include "imgui.h"
#include "graphics.h"
#include "extgraph.h"


#include "message.h"




//全局变量
int message_content = MESSAGE_NO; //消息有无

char message[100] = "\0"; //消息字符串




//设置消息显示内容
void SetMessage(int set_message_content, char* set_message)
{
    message_content = set_message_content;
    if (set_message != NULL)
        strcpy(message, set_message);
}




//显示消息
void DrawMessage(void)
{
    drawRectangle(-0.01, 0, 10.01, 0.21, 0);

    if (message_content == MESSAGE_YES)
    {
        drawLabel(0.05, 0.05, message);
    }
}