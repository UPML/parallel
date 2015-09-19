//
// Created by kagudkov on 19.09.15.
//

#ifndef PARALLEL_COMMANDMANAGERM_H
#define PARALLEL_COMMANDMANAGERM_H

#include <string>
#include <map>
#include <vector>

typedef const std::vector<std::string>& Params;
typedef void (*CommandHandler)(Params);
class CommandManager {
public:
    CommandManager();
private:
    std::map<std::string, CommandHandler> commandMap_;
    void init();

public:
    void addCommand(std::string commandName, CommandHandler commandHandler) const;
    void deleteCommand(std::string commandName);
    void runCommand(Params params);
};

#endif //PARALLEL_COMMANDMANAGERM_H
