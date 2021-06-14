#ifndef CHAT_SERVICE_H
#define CHAT_SERVICE_H

#include "json.hpp"
using json = nlohmann::json;

#include <muduo/net/TcpConnection.h>
#include <unordered_map>
#include <functional>
using namespace std;
using namespace muduo;
using namespace muduo::net;

#include "user_model.hpp"

// 表示处理消息的事件回调方法类型
using MsgHandler = std::function<void(const TcpConnectionPtr &conn, json &js, Timestamp)>;

// 聊天服务器业务类
class ChatService
{
public:
	// 获取单例对象的接口函数
	static ChatService* instance();
	// 处理登录业务
	void login(const TcpConnectionPtr &conn, json &js, Timestamp time);
	// 处理注册业务
	void reg(const TcpConnectionPtr &conn, json &js, Timestamp time);
	// 获取消息对应的处理器
	MsgHandler get_handler(int msgid);

private:
	ChatService();

	// 存储消息id和其对应的业务处理方法
	unordered_map<int, MsgHandler> _msg_handler_map;

	// 数据操作类对象
	UserModel _user_model;
};

#endif  // CHAT_SERVICE_H