#pragma once

#include "inputs.h"
#include "helpers.h"
#include "service.h"
#include <map>
#include <thread>
#include <iostream>
#include <chrono>
#include <mutex>
#include <fstream>

void get(Service &service, const std::string &clientName, const std::vector<std::string> &args, std::vector<std::string> &output)
{
    output.emplace_back(service.GET(clientName, args[1]));
}

void set(Service &service, const std::string &clientName, const std::vector<std::string> &args, std::vector<std::string> &output)
{
    service.SET(clientName, args[1], args[2]);
    output.emplace_back("OK");
}

void mget(Service &service, const std::string &clientName, const std::vector<std::string> &args, std::vector<std::string> &output)
{
    for (unsigned int i = 1; i < args.size(); ++i)
    {
        get(service, clientName, std::vector<std::string>{clientName, args[i]}, output);
    }
}

void mset(Service &service, const std::string &clientName, const std::vector<std::string> &args, std::vector<std::string> &output)
{
    service.lockMtx();
    for (unsigned int i = 1; i < args.size(); i += 2)
    {
        set(service, clientName, std::vector<std::string>{clientName, args[i], args[i + 1]}, output);
    }
    service.unlockMtx();
}

void incDec(Service &service, const std::string &clientName, const std::vector<std::string> &args, std::vector<std::string> &output, const bool isInc)
{
    output.emplace_back(service.INCDEC(clientName, args[1], isInc) ? "OK" : "ERROR");
}
