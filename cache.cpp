#include "cache.h"

Cache::Cache(int capacity) : mCapacity(capacity), doublyLinkedList(), cacheData()
{
}

std::string Cache::find(const std::string &key)
{
    auto result = cacheData.find(key);
    if (result != cacheData.end())
    {
        auto &it = result->second;
        doublyLinkedList.splice(doublyLinkedList.begin(), doublyLinkedList, it);
        return it->second;
    }
    return "";
}

void Cache::upsert(const std::string &key, const std::string &value)
{
    auto result = cacheData.find(key);
    if (result != cacheData.end()) // update: does not increase the size
    {
        auto &it = result->second;
        doublyLinkedList.splice(doublyLinkedList.begin(), doublyLinkedList, it);
        it->second = value; // update
    }
    else // insert: could increase the size
    {
        if (doublyLinkedList.size() == mCapacity)
        {
            // remove the least recently accessed item
            cacheData.erase(doublyLinkedList.back().first);
            doublyLinkedList.pop_back();
        }
        // insert it at the front of the list (most recently accessed)
        doublyLinkedList.emplace_front(key, value);
        cacheData[key] = doublyLinkedList.begin();
    }
}
