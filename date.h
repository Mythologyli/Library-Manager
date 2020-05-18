/*
文件：date.h

作者：李培生

内容：
日期结构；
用于新建日期的函数的声明；
用于计算间隔天数的函数的声明。
*/




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