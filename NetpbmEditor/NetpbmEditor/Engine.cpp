#include "Engine.h"

void Engine::start()
{
    //TODO:: Call factory from here. We read it from the console
    //GrayscaleCommand* cmd1 = new GrayscaleCommand();
    //MonochromeCommand* cmd2 = new MonochromeCommand();
    LoadCommand* cmd3 = new LoadCommand("one.pbm");

    //commands.addCommand(cmd1);
    //commands.addCommand(cmd2);
    commands.addCommand(cmd3);

    // If we hit save, undo we call a function here
    saveCommand();
}

void Engine::saveCommand()
{
    // Here we execute the commands consequentialy
    for (size_t i = 0; i < this->commands.getSize(); i++)
    {
        this->commands[i]->execute(this->editor);
    }
}

