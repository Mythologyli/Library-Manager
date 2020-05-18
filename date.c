/*
文件：date.c

作者：黄怀萱

内容：
新建日期的函数；
计算间隔天数的函数。
*/





#include "date.h"




//新建日期;若日期不合法，返回的结构数据均为0
struct Date AddDate(int year, int month, int day)
{
    int month_day[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; //每月的天数

    struct Date output_date;

    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) //如果为闰年，2月多一天
    {
        month_day[1]++;
    }
    if ((day <= month_day[month - 1]) && day > 0 && month > 0 && month < 13) //日期合法
    {
        output_date.year = year;
        output_date.month = month;
        output_date.day = day;
    }
    else //日期不合法
    {
        output_date.year = 0;
        output_date.month = 0;
        output_date.day = 0;
    }

    return output_date;
}




//计算天数间隔
int DateInterval(struct Date start_date, struct Date end_date)
{
    int year_start, month_start, day_start;

    int year_end, month_end, day_end;

    //计算start_date到0年3月1日的天数
    month_start = (start_date.month + 9) % 12;
    year_start = start_date.year - month_start / 10;
    day_start = 365 * year_start + year_start / 4 - year_start / 100 + year_start / 400 + (month_start * 306 + 5) / 10 + (start_date.day - 1);

    //计算end_date到0年3月1日的天数
    month_end = (end_date.month + 9) % 12;
    year_end = end_date.year - month_end / 10;
    day_end = 365 * year_end + year_end / 4 - year_end / 100 + year_end / 400 + (month_end * 306 + 5) / 10 + (end_date.day - 1);

    return day_end - day_start;
}