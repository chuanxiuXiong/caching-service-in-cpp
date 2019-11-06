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

void Service::SET(const std::string &clientName, const std::string &key, const std::string &value)
{
    lockMtx();
    cache.upsert(key, value);
    unlockMtx();
};

std::string Service::GET(const std::string &clientName, const std::string &key)
{
    return cache.find(key);
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
