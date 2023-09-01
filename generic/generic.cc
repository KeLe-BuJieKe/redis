#include <iostream>
#include <string> 
#include <sw/redis++/redis++.h>
#include <vector>
#include <chrono>
#include <thread>
#include "Util.hpp"
void testSetGet(sw::redis::Redis& redis) {
    std::cout << "get 和 set 的使用" << std::endl;

    // 清空一个数据库，避免之前残留的数据有干扰
    redis.flushall();

    // 使用 set 来设置 key
    redis.set("key1", "111");
    redis.set("key2", "222");
    redis.set("key3", "333");
    
    sw::redis::OptionalString value1 = redis.get("key1");
    sw::redis::OptionalString value2 = redis.get("key2");
    sw::redis::OptionalString value3 = redis.get("key3");
    sw::redis::OptionalString value4 = redis.get("key4");  //不存在

    if (value1.has_value()) {
        std::cout << "value1 = " << value1.value() << std::endl;
    }
    if (value2.has_value()) {
        std::cout << "value2 = " << value2.value() << std::endl;
    }
    if (value3.has_value()) {
        std::cout << "value3 = " << value3.value() << std::endl;
    }
    if (value4.has_value()) {
        std::cout << "value4 = " << value4.value() << std::endl;
    }
}


void testExists(sw::redis::Redis& redis) {
    std::cout << "exist " << std::endl;
    redis.flushall();

    redis.set("key1", "111");
    long long res1 = redis.exists("key1");
    if (res1 == 0) {
        std::cerr << "key 不存在: " << res1 <<std::endl;
    }
    else {
        std::cout << "key 存在: " << res1 <<std::endl;
    }

    long long res2 = redis.exists("key2");
    if (res2 == 0) {
        std::cerr << "key 不存在: " << res2 <<std::endl;
    }
    else {
        std::cout << "key 存在: " << res2 <<std::endl;
    }


    long long res3 = redis.exists({"key1", "key2", "key3"});  
    if (res3 == 0) {
        std::cerr << "key 不存在 key数量为: " << res3 <<std::endl;
    }
    else {
        std::cout << "key 存在 key数量为: " << res3 <<std::endl;
    }

}


void testDel(sw::redis::Redis& redis) {
    std::cout << "del " << std::endl;
    redis.flushall();
    redis.set("key1", "111");
    long long res1 = redis.exists("key1");
    if (res1 == 0) {
        std::cerr << "key 不存在: " << res1 <<std::endl;
    }
    else {
        std::cout << "key 存在: " << res1 <<std::endl;
    }

    long long delres1 = redis.del("key1");
    if (delres1 == 0) {
        std::cerr << "删除：" << delres1 << " 个 key" << std::endl;
    }
    else {
        std::cout << "成功删除：" << delres1 << " 个 key" << std::endl;
    }

    long long res2 = redis.exists("key1");
    if (res2 == 0) {
        std::cerr << "key 不存在: " << res2 <<std::endl;
    }
    else {
        std::cout << "key 存在: " << res2 <<std::endl;
    }


    long long delres2 = redis.del({"key1", "key2", "key3"});
    if (delres2 == 0) {
        std::cerr << "删除：" << delres2 << " 个 key" << std::endl;
    }
    else {
        std::cout << "成功删除：" << delres2 << " 个 key" << std::endl;
    }

}

void testKeys(sw::redis::Redis& redis) {
    std::cout << "test keys" << std::endl;
    redis.flushall();
    redis.set("key1", "111");
    redis.set("key2", "222");
    redis.set("key3", "333");
    redis.set("key4", "444");
    redis.set("key5", "555");
    redis.set("key6", "666");
    redis.set("key7", "777");

    //keys 的第二个参数，是一个 ”插入迭代器“，需要先创建一个保存结果的容器
    //接下来再创建一个插入迭代器指向容器的位置，就可以把 keys 获取到的记过依次通过刚才的插入迭代器插入到容器的指定位置中
    std::vector<std::string> result;
    std::back_insert_iterator<std::vector<std::string>> it = std::back_inserter(result);
    redis.keys("*", it);
    printContainer(result);
}

void testExpireTtl(sw::redis::Redis& redis) {
    std::cout << "expire  and ttl" << std::endl;
    redis.flushall();


    redis.set("key1", "111");
    bool res = redis.expire("key1", std::chrono::seconds(10));
    if (res) {
        std::cout << "设置成功" << std::endl;
    }
    using namespace std::chrono_literals;  
    std::this_thread::sleep_for(3s);  //字面值常量，存储在 std::chrono_literals 命名空间内
    long long time = redis.ttl("key1");
    std::cout << time << std::endl;
}


void testType(sw::redis::Redis& redis) {
    std::cout << "testType" << std::endl;
    redis.set("key1", "111");
    std::string res = redis.type("key1");
    std::cout << res << std::endl;

    redis.lpush("key2", "222");
    res = redis.type("key2");
    std::cout << res << std::endl;

    redis.hset("key3", "f1", "333");
    res = redis.type("key3");
    std::cout << res << std::endl;

    redis.sadd("key4", "444");
    res = redis.type("key4");
    std::cout << res << std::endl;

    redis.zadd("key5", "张三", 10);
    res = redis.type("key5");
    std::cout << res << std::endl;

}

int main() {
    //创建 Redis 对象的时候，需要在构造函数中指定 redis 服务器的地址和端口
    sw::redis::Redis redis("tcp://127.0.0.1:6379");
    //testSetGet(redis);
    //testExists(redis);
    //testDel(redis);
    //testKeys(redis);
    //testExpireTtl(redis);
    testType(redis);
    return 0;
}