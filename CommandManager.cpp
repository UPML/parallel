//
// Created by kagudkov on 19.09.15.
//

#include "CommandManager.h"
#include "Exceptions.h"
#include "ThreadManager.h"
#include "Field.h"
#include "Worker.h"

ThreadManager threadManager;
Field field;

size_t toInt(const std::string number);

CommandManager::CommandManager() {
    init();
}

void CommandManager::deleteCommand(std::string commandName) {
    commandMap_.erase(commandName);
}



void CommandManager::addCommand(std::string commandName, CommandHandler commandHandler) {
    commandMap_[commandName] = commandHandler;
}

void start(Params params) {
    if (threadManager.getState_() != ThreadManager::NOT_STARTED) {
        throw IncorrectCommandWorkException("already started");
    }

    long numberOfWorkers = toInt(params.at(1));
    if (numberOfWorkers <= 0) {
        throw IncorrectCommandWorkException("Incorrect number of workers");
    }

    if (params.size() == 4) {
        size_t height = toInt(params.at(2));
        size_t weight = toInt(params.at(3));
        field = Field(height, weight);
    }
    field.print();
    Field tmp(field.getHeight(), field.getWeight());
    Worker().makeIterations(field, tmp);
    tmp.print();
    //threadManager.start(field, numberOfWorkers);




}


size_t toInt(const std::string number) {
    if (number.size() > 8) {
        throw ParseIntException("too long for int");
    };
    long answer = 0;
    long balance = 1;
    for (size_t i = 0; i < number.length(); ++i) {
        if (number.at(i) >= '0' && number.at(i) <= '9') {
            answer += (number.at(i) - '0') * balance;
            balance *= 10;
        } else {
            throw ParseIntException("it is not a number");
        }
    }
    return answer;
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
    for(size_t i = 0; i < commandName.size(); ++i) {
        commandName.at(i) = (char) toupper(commandName.at(i));
    }
    std::map<std::string, CommandHandler>::iterator iterator = commandMap_.find(commandName);
    if (iterator == commandMap_.end()) {
        throw IncorrectCommandNameException("Unknouwn command - " + commandName);
    } else {
        iterator->second(params);
    }
}

