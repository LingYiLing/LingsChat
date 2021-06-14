#ifndef USER_MODEL_H
#define USER_MODEL_H

#include "user.hpp"

// User表的数据操作类
class UserModel
{
public:
	// User表的增加方法
	bool insert(User &user);
};

#endif  // USER_MODEL_H