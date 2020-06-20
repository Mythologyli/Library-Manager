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
	{
		return 1;
	}
	else
	{
		return 0;
	}
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




//比较两日期，若日期1在日期2之前则返回1，若日期1在日期2之后则返回-1，若两日期相等则返回0
int DateCmp(struct Date date1, struct Date date2)
{
	int flag = 0;
	if (date1.year != date2.year)
	{
		flag = date1.year < date2.year ? 1 : -1;
		return flag;
	}

	if (date1.month != date2.month)
	{
		flag = date1.month < date2.month ? 1 : -1;
		return flag;
	}

	if (date1.day != date2.day)
	{
		flag = date1.day < date2.day ? 1 : -1;
		return flag;
	}

	return 0;

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

	m_day = month_day[start_date.month - 1];

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




//计算天数间隔
int DateInterval(struct Date start_date, struct Date end_date)
{
	if (DateCmp(start_date, end_date) < 0)//若start_date在end_date之后
		return -1 * DateInterval(end_date, start_date);

	if (DateCmp(start_date, end_date) == 0)//若两日期相等则天数间隔为0
		return 0;

	int n = 0;
	struct Date tmp_date = start_date;

	for (n = 1;; n++)
	{
		//反复计算下一天的日期，用n记录循环次数，直到算出的日期与end_date相等
		tmp_date = NextDate(tmp_date);

		if (DateCmp(tmp_date, end_date) == 0)
			break;
	}

	return n;
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