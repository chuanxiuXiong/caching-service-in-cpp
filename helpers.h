#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <mutex>

namespace helpers
{
const std::mutex outputMutex;

std::vector<std::string> splitBySpace(const std::string &s);

} // namespace helpers
