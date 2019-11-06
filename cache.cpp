#include "cache.h"

Cache::Cache(int capacity) : mCapacity(capacity)
{
}

std::string Cache::find(std::string &key)
{
    return std::string();
}

bool Cache::upsert(std::string &key, std::string &value)
{
    return false;
}
