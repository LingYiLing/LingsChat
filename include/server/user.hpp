#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

// 匹配User表的ORM类
class User
{
public:
	User(int id = -1, string name = "", string password = "", string state = "offline")
		:_id(id), _name(name), _password(password), _state(state) { }

	void set_id(int id) { _id = id; }
	void set_name(string name) { _name = name; }
	void set_password(string password) { _password = password; }
	void set_state(string state) { _state = state; }

	int get_id() { return _id; }
	string get_name() { return _name; }
	string get_password() { return _password; }
	string get_state() { return _state; }

private:
	int _id;
	string _name;
	string _password;
	string _state;
};

#endif  // USER_H