#include "CLI.h"

#include <iostream>
#include <sstream>
#include <string>
using namespace std;


CLI::CLI(DefaultIO* dio) {
    this->dio = dio;
    commands.push_back(new UploadFile(dio));
    commands.push_back(new AlgorithmSettings(dio));
    commands.push_back(new DetectAnomalies(dio));
    commands.push_back(new DisplayResults(dio));
    commands.push_back(new UploadAnomalies(dio));
}
/**
 * show all the commands on screen. (the options)
 */
void CLI::showCommands() {
    for (int i = 0; i < commands.size(); i++) {
        string id = to_string(i + 1);
        dio->write(id + "." + commands[i]->getDesc());
    }
    dio->write("6.exit\n");
}
void CLI::start() {
    Data data;
    int opt;
    std::string stringOpt;

    while(true) {
        dio->write("Welcome to the Anomaly Detection Server.\n");
        dio->write("Please choose an option:\n");
        showCommands();

        stringOpt = dio->read();
        std::stringstream num(stringOpt);
        num >> opt;

        if (opt == 1) {
            commands[0]->execute(&data);
            continue;
        }

        if (opt == 2) {
            commands[1]->execute(&data);
            continue;
        }
        if (opt == 3) {
            commands[2]->execute(&data);
            continue;
        }
        if (opt == 4) {
            commands[3]->execute(&data);
            continue;
        }
        if (opt == 5) {
            commands[4]->execute(&data);
            continue;
        }
        if (opt == 6) {
            // TODO: should use deconstructor
            for (int i = 0; i < commands.size(); i++) {
                delete commands[i];
            }
            break;
        }

    }


}

// delete commands i think?
// ye
CLI::~CLI() {
}

