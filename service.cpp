#include "service.h"
#include <iostream>

void Service::lockMtx()
{
    mtx.try_lock();
}

void Service::unlockMtx()
{
    mtx.unlock();
}

bool Service::SET(const std::string &clientName, const std::string &key, const std::string value, const bool NX, const bool XX)
{
    lockMtx();
    if (cache.find(key).empty())
    {
        unlockMtx();
        return false;
    }
    cache.upsert(key, value);
    unlockMtx();
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

    lockMtx();
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
    unlockMtx();
    return returnValues;
}

std::vector<std::string> Service::MGET(const std::string &clientName, const std::vector<std::string> &keys)
{
    std::vector<std::string> returnValues(keys.size());
    lockMtx();
    for (int i = 0; i < keys.size(); ++i)
    {
        returnValues[i] = cache.find(keys[i]);
    }
    unlockMtx();
}

bool Service::INCDEC(const std::string &clientName, const std::string &key, const bool isInc)
{
    lockMtx();
    int intValue;
    try
    {
        intValue = std::stoi(cache.find(key));
    }
    catch (std::exception e)
    {
        unlockMtx();
        return false;
    }
    cache.upsert(key, std::to_string(intValue + (isInc ? 1 : -1)));
    unlockMtx();
    return true;
};
