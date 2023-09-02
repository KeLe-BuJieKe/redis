#include <iostream>
#include <string> 
#include <sw/redis++/redis++.h>
#include <vector>
#include "Util.hpp"


void testZaddAndZrange(sw::redis::Redis& redis) {
    std::cout << "zadd and zrange" << std::endl;

    redis.flushall();
    redis.zadd("key1", "zhangfei", 69.5);

    redis.zadd("key1", {
        std::make_pair("lisi", 88.1),
        std::make_pair("wangwu", 78.1)
    });
    // zrange 支持两种主要的风格：
    // 1. 只查询member, 不带 score
    // 2. 查询member,同时带 score
    // 关键就是看插入迭代器指向的容器的类型
    // 指向的容器只是包含一个 string, 就是只查询 member
    // 指向的容器包含的是一个 pair，里面有string 和double，就可以查询到member和score
    std::vector<std::string> res;
    std::insert_iterator<std::vector<std::string>> it1 = std::inserter(res, res.end());
    redis.zrange("key1", 0, -1, it1);

    std::vector<std::pair<std::string, double>> result;
    std::insert_iterator<std::vector<std::pair<std::string, double>>> it2 = std::inserter(result, result.end());
    redis.zrange("key1", 0, -1, it2);
    printContainer(result);
}


void testZcard(sw::redis::Redis& redis) {
    std::cout << "zcard" << std::endl;
    redis.zadd("key1", "zhangfei", 69.5);

    redis.zadd("key1", {
        std::make_pair("lisi", 88.1),
        std::make_pair("wangwu", 78.1)
    });

    std::cout << redis.zcard("key1") << std::endl;
}



void testZrem(sw::redis::Redis& redis) {
    std::cout << "zrem" << std::endl;
    redis.zadd("key1", "zhangfei", 69.5);

    redis.zadd("key1", {
        std::make_pair("lisi", 88.1),
        std::make_pair("wangwu", 78.1)
    });
    redis.zrem("key1", "lisi");
    std::vector<std::pair<std::string, double>> result;
    std::insert_iterator<std::vector<std::pair<std::string, double>>> it2 = std::inserter(result, result.end());
    redis.zrange("key1", 0, -1, it2);
    printContainer(result);
}


void testZscore(sw::redis::Redis& redis) {
    std::cout << "zscore" << std::endl;
    redis.zadd("key1", "zhangfei", 69.5);

    redis.zadd("key1", {
        std::make_pair("lisi", 88.1),
        std::make_pair("wangwu", 78.1)
    });



    sw::redis::OptionalDouble res = redis.zscore("key1", "zhangfei");
    if (res) {
        std::cout << res.value() << std::endl;
    }
    else {
        std::cout << "无效" << std::endl;
    }
}


void testZrank(sw::redis::Redis& redis) {
    std::cout << "zrank" << std::endl;
    redis.zadd("key1", "zhangfei", 69.5);

    redis.zadd("key1", {
        std::make_pair("lisi", 88.1),
        std::make_pair("wangwu", 78.1)
    });

    sw::redis::OptionalLongLong res = redis.zrank("key1", "zhangfei");
    if (res) {
        std::cout << res.value() << std::endl;
    }
    else {
        std::cout << "无效" << std::endl;
    }
}


int main() {
    //创建 Redis 对象的时候，需要在构造函数中指定 redis 服务器的地址和端口
    sw::redis::Redis redis("tcp://127.0.0.1:6379");
    //testZaddAndZrange(redis);
    testZcard(redis);
    testZrem(redis);
    testZscore(redis);
    testZrank(redis);
    return 0;
}