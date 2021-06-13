#include "chat_server.hpp"

#include <functional>
using namespace std;
using namespace placeholders;

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
void on_connection(const TcpConnectionPtr &)
{

}

// 上报读写事件相关信息的回调函数
void on_message(const TcpConnectionPtr &, 
			Buffer *, 
			Timestamp)
{

}