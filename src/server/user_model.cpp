#include "user_model.hpp"
#include "mysql_db.hpp"
#include <muduo/base/Logging.h>

#include <iostream>
using namespace std;

// User表的增加方法
bool UserModel::insert(User &user)
{
	// 1.组装sql语句
	char sql[1024] = {0};
	sprintf(sql, "insert into User(name, password, state) values('%s', '%s', '%s')",
		user.get_name().c_str(), user.get_password().c_str(), user.get_state().c_str());
	
	MySQL mysql;
	if (mysql.connect())
	{
		LOG_INFO << sql;
		// 获取插入成功的用户数据生成的主键id
		if (mysql.update(sql))
		{
			user.set_id(mysql_insert_id(mysql.get_connection()));
			return true;
		}
	}

	return false;
}