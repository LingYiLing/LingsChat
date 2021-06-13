#include "chat_server.hpp"
#include "json.hpp"
#include "chat_service.hpp"

#include <functional>
#include <string>
using namespace std;
using namespace placeholders;
using json = nlohmann::json;

ChatServer::ChatServer(EventLoop *loop,
					const InetAddress &listen_addr,
					const string &name_arg)
	:_server(loop, listen_addr, name_arg), _loop(loop)
{
	// 注册连接回调
	_server.setConnectionCallback(std::bind(&ChatServer::on_connection, this, _1));

	// 注册消息回调
	_server.setMessageCallback(std::bind(&ChatServer::on_message, this, _1, _2, _3));
	
	// 设置线程数量
	_server.setThreadNum(4);
}

// 启动服务
void ChatServer::start()
{
	_server.start();
}

// 上报连接相关信息的回调函数
void ChatServer::on_connection(const TcpConnectionPtr &conn)
{
	// 客户端断开连接
	if (!conn->connected()) { conn->shutdown(); }

}

// 上报读写事件相关信息的回调函数
void ChatServer::on_message(const TcpConnectionPtr & conn, 
			Buffer *buffer, 
			Timestamp time)
{
	string buf = buffer->retrieveAllAsString();
	// 数据的反序列化
	json js = json::parse(buf);
	// 达到的目的：完全解耦网络模块的代码和业务模块的代码
	// C++没有接口，通过抽象类或者回调函数
	// 通过js["msgid"] 获取=》 业务handler =》 conn js time
	auto msg_handler = ChatService::instance()->get_handler(js["msgid"].get<int>());
	// 回调消息绑定好的事件处理器，来执行相应的业务处理
	msg_handler(conn, js, time);
}