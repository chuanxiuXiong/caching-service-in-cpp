#pragma once
#include "cache.h"
#include <string>
#include <vector>

class Service
{
public:
    Service(int capacity) : cache(Cache(capacity)) {}

    std::string SET(const std::string &clientName, const std::string &key, const std::string value, const bool NX = false, const bool XX = false);

    std::string GET(const std::string &clientName, const std::string &key);

    std::string MSET(const std::string &clientName, const std::vector<std::string> &key, const std::vector<std::string> &value);

    std::string MGET(const std::string &clientName, const std::vector<std::string> &key);

private:
    Cache cache;
};
