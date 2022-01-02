#include "CLI.h"
#include <iostream>
#include <sstream>
#include <string>

CLI::CLI(DefaultIO* dio) {
    this->dio = dio;
    commamnds.push_back(new uploadCVS(dio));
    commamnds.push_back(new AlgorithmSettings(dio));
    commamnds.push_back(new DetectAnomalies(dio));
    commamnds.push_back(new DisplayResults(dio));
    commamnds.push_back(new UploadAnomalies(dio));
}
/**
 * show all the commands on screen. (the options)
 */
void CLI::showCommands() {
    for (int i = 0; i < commands.size(); i++) {
        dio->write(commands[i].getDesc());
    }
}
void CLI::start(){
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
            commands[0]->execute();
            continue;
        }

        if (opt == 2) {
            commands[1]->execute();
            continue;
        }
        if (opt == 3) {
            commands[2]->execute();
            continue;
        }
        if (opt == 4) {
            commands[3]->execute();
            continue;
        }
        if (opt == 5) {
            commands[4]->execute();
            continue;
        }
        if (opt == 6) {
            for (int i = 0; i < commands.size(); i++) {
                delete command[i];
            }
            break;
        }

    }


}

// delete commands i think?
// ye
CLI::~CLI(DefaultIO* io) {
}

