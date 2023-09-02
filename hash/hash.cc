#include <iostream>
#include <string> 
#include <sw/redis++/redis++.h>
#include <vector>
#include "Util.hpp"
void testHsetHget(sw::redis::Redis& redis) {
    std::cout << "hset hget" << std::endl;
    redis.flushall();

    redis.hset("key1", std::make_pair("f1", "111"));
    sw::redis::OptionalString res = redis.hget("key1", "f1");
    if (res) {
        std::cout << res.value() << std::endl;
    }
    else {
        std::cout << "无效" << std::endl;
    }
}


void testHexists(sw::redis::Redis& redis) {
    std::cout << "hexists" << std::endl;
    redis.flushall();

    redis.hset("key1", std::make_pair("f1", "111"));
    bool res = redis.hexists("key1", "f1");
    if (res) {
        std::cout << "存在" << std::endl;
    }
    else {
        std::cout << "不存在" << std::endl;
    }
}


void testHdel(sw::redis::Redis& redis) {
    std::cout << "hedel" << std::endl;
    redis.flushall();

    redis.hset("key1", std::make_pair("f1", "111"));
    bool res = redis.hexists("key1", "f1");
    if (res) {
        std::cout << "存在" << std::endl;
    }
    else {
        std::cout << "不存在" << std::endl;
    }

    redis.hdel("key1", "f1");  //返回值为：成功删除的个数
    res = redis.hexists("key1", "f1");
    if (res) {
        std::cout << "存在" << std::endl;
    }
    else {
        std::cout << "不存在" << std::endl;
    }
}

void testHkeysAndHvals(sw::redis::Redis& redis) {
    std::cout << "hexists" << std::endl;
    redis.flushall();

    redis.hset("key1", {std::make_pair("f1", "111"), std::make_pair("f2", "222"), std::make_pair("f3", "333")});

    std::vector<std::string> res;
    std::insert_iterator<std::vector<std::string>> it = std::inserter(res, res.end());
    redis.hkeys("key1", it);
    printContainer(res);


    std::cout << "------------------" << std::endl;
    res.clear();
    it = std::inserter(res, res.end());
    redis.hvals("key1", it);
    printContainer(res);
}



int main() {
    //创建 Redis 对象的时候，需要在构造函数中指定 redis 服务器的地址和端口
    sw::redis::Redis redis("tcp://127.0.0.1:6379");
    //testHsetHget(redis);
    //testHexists(redis);
    //testHdel(redis);
    testHkeysAndHvals(redis);
    return 0;
}