//
// Created by kagudkov on 19.09.15.
//

#ifndef PARALLEL_COMMANDMANAGERM_H
#define PARALLEL_COMMANDMANAGERM_H

#include <string>
#include <map>
#include <vector>
#include "Exceptions.h"
#include "ThreadManager.h"
#include "Field.h"
#include "Worker.h"

typedef const std::vector<std::string> &Params;

class CommandManager;
typedef void (*CommandHandler)(Params, CommandManager&);

class CommandManager {
public:
    CommandManager();

private:
    std::map<std::string, CommandHandler> commandMap_;

    void init();

public:
    ThreadManager threadManager;
    Field field;
    void deleteCommand(std::string commandName);

    void runCommand(Params params);

    void addCommand(std::string commandName, CommandHandler commandHandler);

};

#endif //PARALLEL_COMMANDMANAGERM_H
