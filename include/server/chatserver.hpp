#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
using namespace muduo;
using namespace muduo::net;

class ChatServer
{
public:
    ChatServer(EventLoop *loop,
               const InetAddress &listenAddr,
               const string &nameArg);
    void start();

private:
    //连接相关信息的回调
    void onConnection(const TcpConnectionPtr &);
    //读写事件相关回调
    void onMessage(const TcpConnectionPtr &conn,
                   Buffer *buffer,
                   Timestamp receiveTime);
    TcpServer _server;  //muduo TcpServer
    EventLoop* _loop;    //baseLoop
};

#endif //