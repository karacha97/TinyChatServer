#include "chatserver.hpp"
#include "chatservice.hpp"

#include "json.hpp"

#include <iostream>
#include <functional>
#include <string>
using namespace std;
using namespace placeholders;
using json = nlohmann::json;
ChatServer::ChatServer(EventLoop *loop,
                       const InetAddress &listenAddr,
                       const string &nameArg)
    : _server(loop, listenAddr, nameArg),
      _loop(loop)
{
    _server.setConnectionCallback(bind(
        &ChatServer::onConnection, this, _1));
    _server.setMessageCallback(bind(
        &ChatServer::onMessage, this, _1, _2, _3));
    _server.setThreadNum(4);
}

void ChatServer::start()
{
    _server.start();
}

void ChatServer::onConnection(const TcpConnectionPtr &conn)
{
    if (!conn->connected())
    {
        conn->shutdown();
        //如果连接失败-用户下线，释放socket资源
    }
}

void ChatServer::onMessage(const TcpConnectionPtr &conn,
                           Buffer *buffer,
                           Timestamp time)
{
    string buf = buffer->retrieveAllAsString();
    json js = json::parse(buf);
    //数据的解码
    // 希望去耦合：通过js["msgid"]来获取->handler
    // handler(实现绑定的某个方法，在网络模块不关心，在业务模块处理)
    // 由此实现网络模块和业务模块解耦
    // 实现方法：
    // 1. 面向接口的编程 2. 基于回调函数

    auto msgHandler = ChatService::instance()->getHandler(js["msgid"].get<int>());
     // 通过js["msgid"] 获取=》业务handler=》conn  js  time
    msgHandler(conn, js, time);
}

