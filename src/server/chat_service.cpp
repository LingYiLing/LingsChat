#include "chat_service.hpp"
#include "public.hpp"
#include <muduo/base/Logging.h>
using namespace muduo;

// 获取单列对象的接口函数
ChatService* ChatService::instance()
{
	static ChatService service;
	return &service;
}

// 注册消息以及对应的Handler回调操作
ChatService::ChatService()
{
	_msg_handler_map.insert({LOGIN_MSG, std::bind(&ChatService::login, this, _1, _2, _3)});
	_msg_handler_map.insert({REG_MSG, std::bind(&ChatService::reg, this, _1, _2, _3)});
}

// 获取消息对应的处理器
MsgHandler ChatService::get_handler(int msgid)
{
	// 记录错误日志，msgid没有对应的事件处理回调
	auto it = _msg_handler_map.find(msgid);
	if (it == _msg_handler_map.end())
	{
		// 返回一个默认的处理器，空操作
		return [=](const TcpConnectionPtr &conn, json &js, Timestamp)
		{
			LOG_ERROR << "msgid:" << msgid << " can not find handler!";
		};
	}
	else
	{
		return _msg_handler_map[msgid];
	}
}

// 处理登录业务
void ChatService::login(const TcpConnectionPtr &conn, json &js, Timestamp time)
{
	LOG_INFO << "do login service!!!";
}

// 处理注册业务
void ChatService::reg(const TcpConnectionPtr &conn, json &js, Timestamp time)
{
	LOG_INFO << "do reg service!!!";

}
