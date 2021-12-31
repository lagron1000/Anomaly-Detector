//
// Created by orspiegel on 06/12/2021.
//

#include "Command.h"
class Command {

    // later we make a data structure of commands, so the user can goto command[i]
    // and get the command description, or to execute the current command.
    //
    public String description;
    public:
        virtual void  execute();
};
