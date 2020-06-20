/*
文件：date.h

作者：黄怀萱

内容：
日期结构；
新建日期的函数的声明；
计算间隔天数的函数的声明；
计算给定起始日期后n天的日期的函数的声明。
*/


#ifndef __DATE_H__
#define __DATE_H__


//日期结构
struct Date
{
    int year;
    int month;
    int day;
};




//新建日期;若日期不合法，返回的结构数据均为0
struct Date AddDate(int year, int month, int day);




//计算天数间隔
int DateInterval(struct Date start_date, struct Date end_date);




//计算给定起始日期后n天的日期
struct Date NextNDate(struct Date start_date, int n);


#endif