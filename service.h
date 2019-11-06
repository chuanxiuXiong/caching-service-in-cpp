#pragma once
#include "cache.h"
#include <string>
#include <vector>
#include <mutex>

class Service
{
public:
    Service(int capacity) : cache(Cache(capacity)) {}

    bool SET(const std::string &clientName, const std::string &key, const std::string value, const bool NX = false, const bool XX = false);

    std::string GET(const std::string &clientName, const std::string &key);

    std::vector<bool> MSET(const std::string &clientName, const std::vector<std::string> &keys, const std::vector<std::string> &values);

    std::vector<std::string> MGET(const std::string &clientName, const std::vector<std::string> &keys);

private:
    Cache cache;
    std::mutex mtx;
};
