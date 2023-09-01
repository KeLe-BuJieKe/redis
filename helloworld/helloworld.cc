#include <iostream>
#include <string> 
#include <sw/redis++/redis++.h>


int main() {
    //创建 Redis 对象的时候，需要在构造函数中指定 redis 服务器的地址和端口
    sw::redis::Redis redis("tcp://127.0.0.1:6379");

    //调用ping 函数，让客户端给服务器发送一个 ping，然后服务器就会返回一个 PONG，就通过 返回值 获取到
    std::string result = redis.ping();
    std::cout << result << std::endl;
    return 0;
}