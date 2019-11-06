#include <vector>
#include <string>

namespace inputs
{
const int delayBetweenRequests = 0;

const std::string outputFileName = "log.txt";

const int cacheSize = 5;

const std::vector<std::vector<std::string>> commands{
    {"c empty", ""},
    {"client 1", "SET key1 value1"},
    {"client 1", "GET key1"},
    {"client 2", "GET key2"},
    {"client 2", "SET key2 value2"},
    {"client 2", "GET key2"},
    {"client 3", "SET key3 value3"},
    {"client 4", "SET key4 value4"},
    {"client 5", "SET key5 value5"},
    {"client 6", "SET key6 value6"},
    {"client 7", "GET key1"},
    {"client 8", "MSET key1 1 key2 2 key3 3 key4 4 key5 5 key6 6"},
    {"client 9", "MGET key1 key2 key3 key4 key5 key6 key7"},
    {"client 10", "MULTI"},
    {"client 10", "GET TransactionKey"},
    {"client 10", "SET TransactionKey TransactionValue"},
    {"client 10", "GET TransactionKey"},
    {"client 10", "MSET key1 1 key2 2 key3 3 key4 4 key5 5 key6 6"},
    {"client 10", "MGET key1 key2 key3 key4 key5 key6 key7"},
    {"client 10", "EXEC"},
    {"client 1", "INC key1"},
    {"client 1", "DEC key1"},
    {"client 1", "SET key1 1"},
    {"client 1", "SET key2 2"},
    {"client 1", "INC key1"},
    {"client 1", "INC key2"},
    {"client 1", "GET key1"},
    {"client 1", "GET key2"}

};
}; // namespace inputs
