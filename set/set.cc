#include <iostream>
#include <string> 
#include <sw/redis++/redis++.h>
#include <vector>
#include "Util.hpp"
void testSaddAndSmembers(sw::redis::Redis& redis) {
    std::cout << "sadd and smembers" << std::endl;
    redis.flushall();

    redis.sadd("key1", "111");
    redis.sadd("key1", {"222", "333"});

    std::vector<std::string> result;
    std::back_insert_iterator<std::vector<std::string>> it = std::back_inserter(result);
    redis.smembers("key1", it);

    printContainer(result);
}

void testSismembers(sw::redis::Redis& redis) {
    std::cout << "testSismembers" << std::endl;
    redis.flushall();

    redis.sadd("key1", "111");

    bool res = redis.sismember("key1", "111");
    std::cout << res << std::endl;
}

void testScardAndSpop(sw::redis::Redis& redis) {
    std::cout << "scard" << std::endl;
    redis.flushall();

    redis.sadd("key1", "111");
    redis.sadd("key1", {"222", "333"});
    long long res = redis.scard("key1");
    std::cout << res << std::endl;

    sw::redis::OptionalString result = redis.spop("key1");
    if (result) {
        std::cout << result.value() << std::endl;
    }
    else {
        std::cerr << "无效" << std::endl;
    }
}


void testSInter(sw::redis::Redis& redis) {
    std::cout << "sinter" << std::endl;
    redis.flushall();

    redis.sadd("key1", {"111", "222", "333", "abc"});
    redis.sadd("key2", {"222", "333", "abc"});

    std::vector<std::string> res;
    std::back_insert_iterator<std::vector<std::string>> it = std::back_inserter(res);
    redis.sinter({"key1", "key2"}, it);
    printContainer(res);
}


void testSunion(sw::redis::Redis& redis) {
    std::cout << " sunion " << std::endl;
    redis.flushall();

    redis.sadd("key1", {"111", "222", "333", "abc"});
    redis.sadd("key2", {"222", "333", "abc"});

    std::vector<std::string> res;
    std::back_insert_iterator<std::vector<std::string>> it = std::back_inserter(res);
    redis.sunion({"key1", "key2"}, it);
    printContainer(res);
}

int main() {
    //创建 Redis 对象的时候，需要在构造函数中指定 redis 服务器的地址和端口
    sw::redis::Redis redis("tcp://127.0.0.1:6379");
    //testSaddAndSmembers(redis);
    //testSismembers(redis);
    //testScardAndSpop(redis);
    //testSInter(redis);
    testSunion(redis);
    return 0;
}