//
// Created by kagudkov on 19.09.15.
//

#ifndef LIFETHEFIRSTVERSION_COMANDMANAGER_H
#define LIFETHEFIRSTVERSION_COMANDMANAGER_H

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


#endif //LIFETHEFIRSTVERSION_COMANDMANAGER_H