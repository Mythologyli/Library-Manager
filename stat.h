/*
文件：stat.h

作者：李培生、黄怀萱

内容：
查询图书总借阅次数的函数的声明；
查询用户总借阅次数的函数的声明；
查询用户当前借阅数量的函数的声明；
查询被借阅数量最多的图书的函数的声明；
查询被借阅数量最少的图书的函数的声明；
查询借阅数量最多的用户的函数的声明；
查询出现数量最多的图书关键词的函数的声明。
*/




//查询图书总借阅次数
int BookBorrowTime(struct BookNode* book_node, int book_id, struct BorrowNode* borrow_node);

//查询用户总借阅次数
int UserBorrowTime(struct UserNode* user_node, int user_id, struct BorrowNode* borrow_node);

//查询用户当前借阅数量
int UserBorrowTimeExist(struct UserNode* user_node, int user_id, struct BorrowNode* borrow_node);

//查询被借阅数量最多的图书
int FindMostFavoriteBook(struct BookNode* book_node, struct BorrowNode* borrow_node);

//查询被借阅数量最少的图书
int FindLeastFavoriteBook(struct BookNode* book_node, struct BorrowNode* borrow_node);

//查询借阅数量最多的用户
int FindMostBorrowUser(struct UserNode* user_node, struct BorrowNode* borrow_node);

//查询出现数量最多的图书关键词
char* FindMostBookKey(struct BookNode* book_node);