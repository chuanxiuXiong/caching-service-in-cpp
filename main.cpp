#include "inputs.h"
#include "helpers.h"
#include "service.h"
#include <unordered_map>
#include <thread>
#include <iostream>

void parseCommands(std::unordered_map<std::string, std::vector<std::string>> &clientCommands)
{
    for (auto &i : inputs)
    {
        clientCommands[i[0]].emplace_back(i[1]);
    }
}

void run(std::string clientName, std::vector<std::string> commands, Service &service)
{
    std::vector<std::string> args;
    for (auto &command : commands)
    {
        args = splitBySpace(command);
        if (args[0] == "GET")
        {
            service.GET(args[1]);
        }
        else if (args[0] == "SET")
        {
            bool NX = false;
            bool XX = false;
            if (args.size() >= 4)
            {
                NX = (args[3] == "true") ? true : false;
            }
            if (args.size() == 5)
            {
                XX = (args[4] == "true") ? true : false;
            }
            service.SET(clientName, args[1], args[2], NX, XX);
        }
    }
}

int main(int argc)
{
    std::unordered_map<std::string, std::vector<std::string>> clientCommands;
    std::vector<std::thread> clients;

    Service service(cacheSize);

    parseCommands(clientCommands);

    for (auto &p : clientCommands)
    {
        std::cout << "Started connection with: " << p.first << "...\n";
        clients.emplace_back(std::thread(run, p.first, p.second, service));
    }
}
