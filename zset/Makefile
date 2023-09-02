zset:zset.cc
	g++ -std=c++17 -o $@ $^ /usr/local/lib64/libredis++.a  /usr/local/lib/libhiredis.a   -lpthread 


.PHONY:clean
clean:
	rm zset