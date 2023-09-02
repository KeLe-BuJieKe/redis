#include <iostream>
#include <string> 
#include <sw/redis++/redis++.h>
#include <chrono>
#include <vector>
#include "Util.hpp"
void testStringSetGet(sw::redis::Redis& redis) {
    std::cout << "string get and set" << std::endl;
    redis.flushall();

    redis.set("key1", "111");
    sw::redis::OptionalString value1 = redis.get("key1");
    if (value1.has_value()) {
        std::cout << "value1: " << value1.value() << std::endl;
    }

    redis.set("key2", "222");
    sw::redis::OptionalString value2 = redis.get("key2");
    if (value2) {  //重载了 OptionalString 的 bool
        std::cout << "value2: " << value2.value() << std::endl;
    }
    redis.expire("key2", std::chrono::seconds(10));

    long long time = redis.ttl("key2");
    std::cout << time << std::endl;
}

void testStringMgetMset(sw::redis::Redis& redis) {
    std::cout << "mset and mget" << std::endl;
    redis.flushall();

    redis.mset({std::make_pair("key1", 111), std::make_pair("key2", 222)});
    //当然这里也可以使用std::string，但是如果mget一个不存在的值时，会抛出异常，此时需要catch
    //或者就是用 OptionalString类型，它内部是 std::optional<std::string> 类型，optional包装作用是用来表示一个可能包含或不包含值的容器
    std::vector<sw::redis::OptionalString> res;  
    std::back_insert_iterator<std::vector<sw::redis::OptionalString>> it = std::back_inserter(res);
    redis.mget({"key1", "key2", "key3"} , it);
    printContainerOptional(res);
} 


void testGetRangeAndSetRange(sw::redis::Redis& redis) {
    std::cout << "getrange and setrange" << std::endl;
    redis.flushall();
    
    redis.set("key1", "abcdefghijk");

    std::string res = redis.getrange("key1", 2, 5);
    std::cout << "res: " << res << std::endl;

    redis.setrange("key1", 2, "123");
    res = redis.getrange("key1", 2, 5);
    std::cout << "res: " << res << std::endl;
} 


void testIncrAndDecr(sw::redis::Redis& redis) {
    std::cout << "incr and decr" << std::endl;
    redis.flushall();

    redis.set("key1", "100");
    long long res = redis.incr("key1");
    std::cout << res << std::endl;

    sw::redis::OptionalString value = redis.get("key1");
    if (value) {
        std::cout << value.value() << std::endl;
    }

    //decr与incr操作相同，就不写了 
    //...
}

int main() {
    //创建 Redis 对象的时候，需要在构造函数中指定 redis 服务器的地址和端口
    sw::redis::Redis redis("tcp://127.0.0.1:6379");
    //testStringSetGet(redis);
    //testStringMgetMset(redis);
    //testGetRangeAndSetRange(redis);
    testIncrAndDecr(redis);
    return 0;
}
