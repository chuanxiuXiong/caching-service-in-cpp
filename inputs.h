#include <vector>
#include <string>

namespace inputs
{
const std::string outputFileName = "log.txt";

const int cacheSize = 5;

const std::vector<std::vector<std::string>> commands{
    {"client 1", "SET key1 value1"},
    {"client 2", "GET key1"},
    {"client 1", "GET key2"},
    {"client 2", "SET key2 value2"},
    {"client 2", "GET key2"},
    {"client 2", "SET key3 value3"},
    {"client 2", "SET key4 value4"},
    {"client 2", "SET key5 value5"},
    {"client 1", "SET key6 value6"},
    {"client 1", "GET key1"}};
}; // namespace inputs
