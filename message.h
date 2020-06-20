/*
文件：message.h

作者：李培生

内容：
控制显示内容的宏定义；
设置显示内容的函数的声明；
消息显示的函数的声明。
*/


#ifndef __MESSAGE_H__
#define __MESSAGE_H__


//控制显示内容的宏定义
#define MESSAGE_NO 0
#define MESSAGE_YES 1




//设置显示内容
void SetMessage(int set_message_content, char* set_message);




//消息显示
void DrawMessage(void);


#endif