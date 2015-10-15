//
// Created by kagudkov on 19.09.15.
//

#include "CommandManager.h"
#include "Exceptions.h"
#include "ThreadManager.h"
#include "Field.h"
#include "Worker.h"

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

void start(Params params, CommandManager &commandManager) {
    if (commandManager.threadManager.getState() != Manager::NOT_STARTED) {
        throw IncorrectCommandWorkException("already started");
    }

    long numberOfWorkers = toInt(params.at(1));
    if (numberOfWorkers <= 0) {
        throw IncorrectCommandWorkException("Incorrect number of workers");
    }

    if (params.size() == 3) {
        commandManager.field = Field(params.at(2));
    }

    if (params.size() == 4) {
        size_t height = toInt(params.at(2));
        size_t weight = toInt(params.at(3));
        commandManager.field = Field(height, weight);
    }
//    commandManager.field.print();
    commandManager.threadManager.start(commandManager.field, toInt(params.at(1)));
}


size_t toInt(const std::string number) {
    if (number.size() > 8) {
        throw ParseIntException("too long for int");
    };
    size_t answer = 0;
    long balance = 1;
    for (int i = (int) (number.length() - 1); i >= 0; --i) {
        if (number.at((unsigned long) i) >= '0' && number.at((unsigned long) i) <= '9') {
            answer += (number.at((unsigned long) i) - '0') * balance;
            balance *= 10;
        } else {
            throw ParseIntException("it is not a number");
        }
    }
    return answer;
}

void status(Params params, CommandManager &commandManager) {
    Manager::State state = commandManager.threadManager.getState();

    std::cout << "System state: " << commandManager.threadManager.stateToString(state) << "\n";
    if (state != Manager::NOT_STARTED && state != Manager::RUNNING) {
        std::cout << "After iteration " << commandManager.threadManager.getShared().getStop() << ":\n";
        commandManager.field.print();
    }
}

void stop(Params params, CommandManager &commandManager) {
    switch (commandManager.threadManager.getState()) {
        case Manager::RUNNING:
            //debug(TAG + "stopping");
            commandManager.threadManager.pauseAll();
            commandManager.threadManager.wakeWhenStateIs(Manager::STOPPED);
            // debug(TAG + "awake and stopped");
            std::cout << "Stopped at " << commandManager.threadManager.getShared().getStop() << "\n";
            break;
        default:
            throw IncorrectCommandWorkException("STOP not running");
    }
}

void run(Params params, CommandManager &commandManager) {
    static const std::string TAG("RUN: ");
    size_t runs;
    switch (commandManager.threadManager.getState()) {
        case Manager::NOT_STARTED:
            throw IncorrectCommandNameException(
                    TAG + "task unknown, use START to initialize.");
        case Manager::STOPPED:
            runs = toInt(params.at(1));
            // debug(TAG + "trying to add " + p[0] + " iterations");
            commandManager.threadManager.runForMore(runs);
            break;
        default:
            throw IncorrectCommandWorkException(TAG + "system is busy");
    }
}

void quit(Params params, CommandManager &commandManager) {
    if (commandManager.threadManager.getState() != Manager::NOT_STARTED) {
        //debug(TAG + "manager has started, trying to shut him");
        commandManager.threadManager.shutdown();
        commandManager.threadManager.join();
        //    debug(TAG + "joined the manager");
    }
    //debug(TAG + "exiting the program gracefully ----------");
    std::cout << time(NULL) - commandManager.getTime();
    exit(0);
}

void block(Params params, CommandManager &commandManager) {
    static const std::string TAG("BLOCK: ");
    if (commandManager.threadManager.getState() == Manager::NOT_STARTED) {
        throw IncorrectCommandWorkException(TAG + "not running");
    }
    commandManager.threadManager.wakeWhenStateIs(Manager::STOPPED);
}

void CommandManager::init() {
    addCommand("START", start);
    addCommand("STATUS", status);
    addCommand("STOP", stop);
    addCommand("RUN", run);
    addCommand("QUIT", quit);
    addCommand("BLOCK", block);

}

void CommandManager::runCommand(Params params) {
    std::string commandName = params[0];
    for (size_t i = 0; i < commandName.size(); ++i) {
        commandName.at(i) = (char) toupper(commandName.at(i));
    }
    std::map<std::string, CommandHandler>::iterator iterator = commandMap_.find(commandName);
    if (iterator == commandMap_.end()) {
        throw IncorrectCommandNameException("Unknouwn command - " + commandName);
    } else {
        iterator->second(params, *this);
    }
}

