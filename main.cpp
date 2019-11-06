#include "main.h"

void parseCommands(std::map<std::string, std::vector<std::string>> &clientCommands)
{
    for (auto &i : inputs::commands)
    {
        clientCommands[i[0]].emplace_back(i[1]);
    }
}

void processCommand(const std::string clientName, const std::string command,
                    Service &service, std::mutex &outputMutex, std::ofstream &outputFile, std::vector<std::string> &args)
{

    // get the arguments of the command
    std::vector<std::string> output;

    if (args[0] == "GET")
    {
        get(service, clientName, args, output);
    }
    else if (args[0] == "SET")
    {
        set(service, clientName, args, output);
    }
    else if (args[0] == "MGET")
    {
        mget(service, clientName, args, output);
    }
    else if (args[0] == "MSET")
    {
        mset(service, clientName, args, output);
    }
    else if (args[0] == "INC")
    {
        incDec(service, clientName, args, output, true);
    }
    else if (args[0] == "DEC")
    {
        incDec(service, clientName, args, output, false);
    }
    else
    {
        output.emplace_back("WRONG COMMAND!");
    }

    // output the result to the log file
    outputMutex.try_lock();
    outputFile << clientName << " " << command << ":\n";
    if (output.empty())
    {
        outputFile << "NULL" << std::endl;
    }
    for (auto &result : output)
    {
        if (result.empty())
        {
            result = "NULL";
        }
        outputFile << result << std::endl;
    }
    outputMutex.unlock();
}

void run(const std::string clientName, const std::vector<std::string> commands,
         Service &service, std::mutex &outputMutex, std::ofstream &outputFile)
{

    std::vector<std::string> queuedCommands;
    std::vector<std::vector<std::string>> queuedArgs;
    bool isTransaction = false;
    unsigned int i;
    for (auto &command : commands)
    {
        std::vector<std::string> args = helpers::splitBySpace(command);
        if (isTransaction)
        {
            if (args[0] == "EXEC")
            {
                service.lockMtx();
                outputMutex.try_lock();
                outputFile << "EXEC: " << std::endl;
                for (i = 0; i < queuedCommands.size(); ++i)
                {
                    outputMutex.try_lock();
                    outputFile << i + 1 << ") ";
                    outputMutex.unlock();
                    processCommand(clientName, queuedCommands[i], service, outputMutex, outputFile, queuedArgs[i]);
                }
                outputMutex.unlock(); // outputMutex is unlocked here to ensure other outputs do not interrupt the transaction's output.
                service.unlockMtx();
            }
            else
            {
                outputMutex.try_lock();
                outputFile << clientName << " " << command << std::endl;
                outputFile << "Queued" << std::endl;
                outputMutex.unlock();
                queuedCommands.emplace_back(command);
                queuedArgs.emplace_back(args);
            }
        }
        else
        {
            if (args[0] == "MULTI")
            {
                isTransaction = true;
                outputMutex.try_lock();
                outputFile << clientName << " " << command << std::endl;
                outputMutex.unlock();
                continue;
            }
            else
            {
                processCommand(clientName, command, service, outputMutex, outputFile, args);
            }
        }
    }
}

int main(int argc, char **argv)
{
    std::map<std::string, std::vector<std::string>> clientCommands;

    std::vector<std::thread> clients;

    // lock for outputing the result
    std::mutex outputMtx;

    // log file
    std::ofstream outputFile(inputs::outputFileName, std::ofstream::out);

    Service service(inputs::cacheSize);

    parseCommands(clientCommands);

    for (auto &p : clientCommands)
    {
        outputMtx.lock();
        std::cout << "Started connection with: " << p.first << "...\n";
        outputMtx.unlock();
        clients.emplace_back(std::thread(run, std::ref(p.first),
                                         std::ref(p.second), std::ref(service),
                                         std::ref(outputMtx), std::ref(outputFile)));
        // sleep for some time to approximate the delay between the requests.
        std::this_thread::sleep_for(std::chrono::milliseconds(inputs::delayBetweenRequests));
    }
    for (auto &c : clients)
    {
        c.join();
    }
    outputFile.close();
    std::cout << "All requests have been handled." << std::endl;
    return 0;
}
