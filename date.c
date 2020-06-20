/*
文件：date.c

作者：黄怀萱

内容：
判断是否为闰年的函数的定义；
新建日期的函数的定义；
计算间隔天数的函数的定义；
计算给定起始日期的下一天的日期的函数的定义；
计算给定起始日期后n天的日期的函数的定义。
*/




#include "date.h"




//判断是否为闰年，是则返回1，否则返回0
int IsLeap(struct Date date)
{
	if ((date.year % 4 == 0 && date.year % 100 != 0) || date.year % 400 == 0)//判断是否为闰年
		return 1;
	else
		return 0;
}




//新建日期;若日期不合法，返回的结构数据均为0
struct Date AddDate(int year, int month, int day)
{
    int month_day[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; //平年每月的天数

    struct Date output_date;

	output_date.year = year;
    output_date.month = month;
    output_date.day = day;

    if (IsLeap(output_date)) //如果为闰年，2月多一天
    {
        month_day[1]++;
    }

    if 
	(
		(output_date.day <= month_day[month - 1]) 
		&& output_date.day > 0 
		&& output_date.month > 0 
		&& output_date.month < 13
	) //日期合法
    {
        return output_date;
    }
    else //日期不合法
    {
        output_date.year = 0;
        output_date.month = 0;
        output_date.day = 0;

		return output_date;
    }
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




//计算给定起始日期的下一天的日期
struct Date NextDate(struct Date start_date)
{
	int month_day[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; //平年每月的天数
	
	int m_day;//定义m_day，用于存放当月天数
	struct Date next_date; //存放下一天的日期


	if (IsLeap(start_date)) //如果为闰年，2月多一天
    {
        month_day[1]++;
    }

	m_day = month_day[start_date.month  - 1];

	if (start_date.day < m_day)//输入日期不是当月最后一天,只需将日加1
	{
		next_date.year = start_date.year;
		next_date.month = start_date.month;
		next_date.day = start_date.day + 1;
	}

	else if (start_date.day == m_day && start_date.month != 12)//输入日期是当月最后一天且该月不是12月，将月份加1，日改为1
	{
		next_date.year = start_date.year;
		next_date.month = start_date.month + 1;
		next_date.day = 1;
	}

	else if (start_date.month == 12 && start_date.day == 31)//输入日期为当年最后一天，则年加1，日、月均改为1
	{
		next_date.year = start_date.year + 1;
		next_date.month = 1;
		next_date.day = 1;
	}

	return next_date;
}




//计算给定起始日期后n天的日期
struct Date NextNDate(struct Date start_date, int n)
{
	struct Date next_n_date = start_date;

	while (n--)
	{
		next_n_date = NextDate(next_n_date);//通过计算n次下一天的日期，得到n天后的日期
	}

	return next_n_date;
}