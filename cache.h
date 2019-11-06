#pragma once
#include <string>

class Cache
{
public:
    Cache(int capacity);
    std::string find(std::string &key);
    bool upsert(std::string &key, std::string &value);

private:
    int mCapacity;
};
