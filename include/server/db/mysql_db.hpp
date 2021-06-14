#ifndef MYSQL_DB_H
#define MYSQL_DB_H

#include <mysql/mysql.h>
#include <string>
using namespace std;

// 数据库操作类
class MySQL
{
public:
	// 初始化数据库连接
	MySQL();
	// 释放连接资源
	~MySQL();
	// 连接数据库
	bool connect();
	// 更新操作
	bool update(string sql);
	// 查询操作
	MYSQL_RES* query(string sql);
	// 获取MySQL连接
	MYSQL* get_connection();

private:
	MYSQL *_conn;
};


#endif  // MYSQL_DB_H