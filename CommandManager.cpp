//
// Created by kagudkov on 19.09.15.
//

#include "CommandManager.h"
#include "Exception.h"

ThreadManager threadManager;

CommandManager::CommandManager(){
    init();
}

void CommandManager::deleteCommand(std::string commandName) {
    commandMap_.erase(commandName);
}

void CommandManager::addCommand(std::string commandName, CommandHandler commandHandler) const {
    commandMap_.insert(commandName, commandHandler);
}

void start(Params params) {

}

void status(Params params) {

}

void stop(Params params) {

}

void run(Params params) {

}

void quit(Params params) {

}

void CommandManager::init() {
    addCommand("START", start);
    addCommand("STATUS", status);
    addCommand("STOP", stop);
    addCommand("RUN", run);
    addCommand("QUIT", quit);
}

void CommandManager::runCommand(Params params) {
    std::string commandName = params[0];
    commandName = toupper(commandName);
    std::map<std::string, CommandHandler>::iterator iterator = commandMap_.find(commandName);
    if (iterator == commandMap_.end()) {
        throw IncorrectCommandNameException("Unknouwn command - " + commandName);
    } else {
        iterator->second(params);
    }
}

