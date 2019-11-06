# caching-service-in-cpp

A naive LRU caching service implemented in C++. It is intended to provide some of the similar functionality as Redis.

1. Major Assumptions and Design Choices:

   1. I chose to implement a C++ based caching service because C++ allows customizations on how to access and modify variables (whether it is through pointer or reference or using move syntax, etc.), which is great for building this caching layer because it has a performance requirement. C++ is slightly faster than other languages such as python in general settings.

   2. The downside to C++ is that it is not as easy to be integrated with the web application and implementing REST APIs that listen to a network port and return response is nontrivial. Therefore, I simplified the network portion of the API (listening to a port, receiving request and sending response). I made the assumption that all the network requests are represented as C++ function calls here. The header information (which connection the request is coming from) is converted to a string representing the client name (e.g. "client 1", "client 2", "client 3"). The requests/inputs are being received from the `commands` variable `inputs.h`, where each `string` is a `command`. Since the server should be able to concurrently handle multiple requests, each client's connection corresponds to a thread that is scheduled by the server. I used mutex/lock to ensure the atomic property of some of the features. For response/outputs, I chose to ouput it to the ouput file (`outputFileName` in `inputs.h`), where each input command is followed by the response ouput in the next line. Under this assumption, I could implement the functionality and the service could be wrapped with a network API that supports easy ways to listen to requests and sending response.

   3. I assume that the cache has a size limit (which could be customized under inputs.h). The size of the input and output and the cache should not overflow the machine's memory.

   4. I assume that all values are `string` (since this is also how redis backend is working).

   5. I assume I do not have cover the case to recover from a fatal cache server error. The only interrupt from other clients happen when one client thread is switched out of CPU and other client get swithed into the same CPU. I use lock to ensure the writing operations and transaction operations are atmoic to avoid race condition.

   6. The design: business logic / `main.cpp` --> service logic / `service.cpp` --> caching datastore / `cache.cpp`. `main.cpp` serves as the main entry of the program. All the detailed logics are separated in `main.h` to make it more readable and maintainable. The main business logic, the service logic and the caching layer are separated to make them independent of each other so that when we change one of them (for exmaple, change to a different eviction policy), we don't have to change other layers of the program.

   7. Cache / Perfomance: I chose to implement a LRU cache with a doubly linked list and a hash map, which ensures constant O(1) insertion and lookup while keeping the cache under its capacity. I pass the `string` or `vector` by reference to avoid unnecessary copy. I use `reserve` to avoid dynamic allocation os `string` or `vector` in some cases.

2. How to setup?
   Please compile it in a c++ runnable environment and use g++/gcc compiler. If the operating system supports Makefile, compile by typing `make all`. If the above step does not work, please compile the following files separately by typing:
   `g++ -g -std=c++11 -c cache.cpp -o cache.o`

   `g++ -g -std=c++11 -c helpers.cpp -o helpers.o`

   `g++ -g -std=c++11 -c service.cpp -o service.o`

   `g++ -g -std=c++11 -o main main.cpp helpers.o service.o cache.o`

   After compiling, you could change any of the inputs in the `inputs.h` and run `main` or `./main`, depending the operating system that you have.

3. Supported features:

   1. `SET` and `GET` (assume there are no expiration request, and does not support additional flags such as `NX` and `XX` because of the time limit but they could be easily extended based on the current program). Examples:
      `SET key1 value1`
      `GET key1`
   2. `MGET` and `MSET` (assuming `MSET` never fails and always upserts the data. In the implementaion just reuse the above functions). Examples:
      `MSET key1 1 key2 2 key3 3 key4 4 key5 5 key6 6`
      `MGET key1 key2 key3 key4 key5 key6 key7`
   3. A cache eviction policy based on Least Recently Used Cache.
   4. `INCR` and `DECR` (assuming we allow overflow (INT_MAX + 1 = INT_MIN is acceptable) and integer is int32).
   5. `MULTI` and `EXEC` in `Transaction`.
