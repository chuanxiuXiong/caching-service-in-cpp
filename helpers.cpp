#include "helpers.h"

std::vector<std::string>
helpers::splitBySpace(const std::string &s)
{
    std::vector<std::string> ans;
    ans.reserve(5);
    unsigned int next = 0;
    int curr = 0;
    while (next < s.size())
    {

        next = s.find(' ', curr);
        ans.emplace_back(s.substr(curr, next - curr));
        curr = next + 1;
    }
    return ans;
} // namespace helper conststd::vector<std::string>splitBySpace(const std::string&s)
