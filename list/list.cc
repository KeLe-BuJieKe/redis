#include <iostream>
#include <string> 
#include <sw/redis++/redis++.h>
#include <vector>
#include "Util.hpp"


void testLPushAndLPop(sw::redis::Redis& redis) {
    std::cout << "lpush and lpop" << std::endl;
    redis.flushall();

    redis.lpush("key1", "111");

    redis.lpush("key1", {"222", "333", "444"});

    std::vector<std::string> values = {"555", "666", "777"};
    redis.lpush("key1", values.begin(), values.end());

    std::vector<std::string> result;
    std::back_insert_iterator<std::vector<std::string>> it = std::back_inserter(result);
    redis.lrange("key1", 0, -1, it);
    printContainer(result);

    std::cout << "--------------" << std::endl;

    result.clear();
    sw::redis::OptionalString res = redis.lpop("key1");
    if (res) {
        std::cout << "lpop: " << res.value() << std::endl;
    }
    it = std::back_inserter(result);
    redis.lrange("key1", 0, -1, it);
    printContainer(result);
}


void testRPushAndRPop(sw::redis::Redis& redis) {
    std::cout << "rpush and rpop" << std::endl;
    redis.flushall();

    redis.rpush("key1", "111");

    redis.rpush("key1", {"222", "333", "444"});

    std::vector<std::string> values = {"555", "666", "777"};
    redis.rpush("key1", values.begin(), values.end());

    std::vector<std::string> result;
    std::back_insert_iterator<std::vector<std::string>> it = std::back_inserter(result);
    redis.lrange("key1", 0, -1, it);
    printContainer(result);

    std::cout << "--------------" << std::endl;

    result.clear();
    sw::redis::OptionalString res = redis.rpop("key1");
    if (res) {
        std::cout << "rpop: " << res.value() << std::endl;
    }
    it = std::back_inserter(result);
    redis.lrange("key1", 0, -1, it);
    printContainer(result);
}

 
void testBLPopAndBRPop(sw::redis::Redis& redis) {
    std::cout << "blpop and brpop" << std::endl;
    redis.flushall();

    sw::redis::OptionalStringPair res = redis.blpop("key", std::chrono::seconds(3));
    if (res) {
        //对于 std::optional 类型来说，可以直接使用 -> 来访问 optional 内部包含的元素的成员
        std::cout << "key: " << res.value().first << std::endl;
        std::cout << "second: " << res->second << std::endl;
    }
}


void testLlen(sw::redis::Redis& redis) {
    std::cout << "llen " << std::endl;
    redis.flushall();

    redis.rpush("key1", {"222", "333", "444"});
    long long len = redis.llen("key1");
    std::cout << "len : " << len << std::endl;
}
int main() {
    //创建 Redis 对象的时候，需要在构造函数中指定 redis 服务器的地址和端口
    sw::redis::Redis redis("tcp://127.0.0.1:6379");
    //testLPushAndLPop(redis);
    //testRPushAndRPop(redis);
    //testBLPopAndBRPop(redis);
    testLlen(redis);
    return 0;
}