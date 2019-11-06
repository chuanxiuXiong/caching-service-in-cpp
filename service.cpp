#include "service.h"
#include <iostream>

bool Service::SET(const std::string &clientName, const std::string &key, const std::string value, const bool NX, const bool XX)
{
    mtx.lock();
    if (cache.find(key).empty())
    {
        mtx.unlock();
        return false;
    }
    cache.upsert(key, value);
    mtx.unlock();
    return true;
};

std::string Service::GET(const std::string &clientName, const std::string &key)
{
    return cache.find(key);
}

std::vector<bool> Service::MSET(const std::string &clientName, const std::vector<std::string> &keys, const std::vector<std::string> &values)
{
    if (keys.size() != values.size())
    {
        return {};
    }

    std::vector<bool> returnValues(keys.size());

    mtx.lock();
    for (int i = 0; i < keys.size(); ++i)
    {
        if (cache.find(keys[i]).empty())
        {
            returnValues[i] = false;
        }
        else
        {
            returnValues[i] = true;
            cache.upsert(keys[i], values[i]);
        }
    }
    mtx.unlock();
    return returnValues;
}

std::vector<std::string> Service::MGET(const std::string &clientName, const std::vector<std::string> &keys)
{
    std::vector<std::string> returnValues(keys.size());
    mtx.lock();
    for (int i = 0; i < keys.size(); ++i)
    {
        returnValues[i] = cache.find(keys[i]);
    }
    mtx.unlock();
}
