#include <vector>
#include <string>

const int cacheSize = 5;

const std::vector<std::vector<std::string>> inputs{
    {"client 1", "SET key1 value1"},
    {"client 2", "GET key1"},
    {"client 1", "GET key2"},
    {"client 2", "SET key2 value2"},
    {"client 2", "GET key2"}};
