# TinyChatServer
A Tiny ChatServer based on muduo

# 运行环境
Ubuntu 20.04.1

# 依赖环境
nginx 1.12.2

redis

hiredis库

mysql

# 编译方式
1. 清空build文件内的内容

cd ./build

rm -rf *

2. cmake

`cd ..`

`cmake`

3. make

`make`

# 文件结构
-TinyChatServer

--bin：可执行文件

--build：cmake中间文件

--include：头文件

----server

----client

--src：源文件

----server

----client

--thirdparty：第三方库文件json

