#include "chat_server.hpp"
#include <iostream>
using namespace std;

int main()
{
	EventLoop eloop;
	InetAddress addr("127.0.0.1", 6000);
	ChatServer server(&eloop, addr, "ChatServer");

	server.start();
	eloop.loop();

	return 0;
}