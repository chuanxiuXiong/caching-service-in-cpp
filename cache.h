#pragma once
#include <string>

class Cache
{
public:
    Cache(int capacity);
    std::string find(const std::string &key);
    bool upsert(const std::string &key, const std::string &value);

private:
    int mCapacity;
};
