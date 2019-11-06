#pragma once
#include <string>
#include <list>
#include <unordered_map>

// Cache class - where the cached data is stored and managed.
// The cache uses LRU eviction policy which automatically removes the least recently
// accessed item when the data size has reached the capacity.
class Cache
{
public:
    Cache(int capacity);
    std::string find(const std::string &key);
    void upsert(const std::string &key, const std::string &value);

private:
    unsigned int mCapacity;

    // the doublyLinkedList keeps the access order of the data
    // from the front to the back: the most recently accessed to the least recently accessed
    // this is actually the bottom layer of the cacheData, where the value data lives
    std::list<std::pair<std::string, std::string>> doublyLinkedList;

    // the cacheData is a map that stores from the key to the keyValue pair that in the doublyLinkedList
    // this is actually the top layer of the cacheData
    std::unordered_map<std::string, std::list<std::pair<std::string, std::string>>::iterator> cacheData;
};
