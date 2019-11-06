#pragma once
#include "cache.h"
#include <string>
#include <vector>
#include <mutex>
#include <unordered_map>

// Service class - where the backend portion of the APIs live; serves as an access point to the cache.
// The service contains a mutex to ensure atomic operations in some functions, such as when SET, MSET, etc.
class Service
{
public:
    Service(int capacity) : cache(Cache(capacity)) {}

    void SET(const std::string &clientName, const std::string &key, const std::string &value);

    std::string GET(const std::string &clientName, const std::string &key);

    bool INCDEC(const std::string &clientName, const std::string &key, const bool isInc);

    void lockMtx();

    void unlockMtx();

private:
    Cache cache;
    std::mutex mtx;
};
