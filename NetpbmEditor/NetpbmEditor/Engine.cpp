#include "Engine.h"

void Engine::start()
{
    parseCommandsFrom(std::cin);
}

void Engine::parseCommandsFrom(std::istream& ifs) 
{
    while (true)
    {
        std::cout << "> ";
        char line[Constants::BASIC_BUFFER_SIZE];
        ifs.getline(line, Constants::BASIC_BUFFER_SIZE);
        std::stringstream ss(line);
        char command[Constants::BASIC_BUFFER_SIZE];
        ss >> command;

        if (std::strcmp(command, Constants::LOAD_COMMAND) == 0)
        {
            char fileName[Constants::BASIC_BUFFER_SIZE];
            ss >> fileName;

            LoadCommand* cmd = new LoadCommand(fileName);

            commands.addCommand(cmd);
        }
        else if (std::strcmp(command, Constants::SAVE_COMMAND) == 0)
        {
            this->executeCommands();
            this->editor.serializeAllFilesInCurrentSession();
            this->removeCommands();
        }
        else if(std::strcmp(command, Constants::GRAYSCALE_COMMAND) == 0)
        {
            GrayscaleCommand* cmd = new GrayscaleCommand();

            commands.addCommand(cmd);
        }
        else if (std::strcmp(command, Constants::MONOCHROME_COMMAND) == 0)
        {
            MonochromeCommand* cmd = new MonochromeCommand();

            commands.addCommand(cmd);
        }
        else if (std::strcmp(command, Constants::NEGATIVE_COMMAND) == 0)
        {
            NegativeCommand* cmd = new NegativeCommand();

            commands.addCommand(cmd);
        }
        else if (std::strcmp(command, Constants::ROTATE_COMMAND) == 0)
        {
            char direction[Constants::BASIC_BUFFER_SIZE];
            ss >> direction;

            if (std::strcmp(direction, Constants::LEFT_COMMAND) == 0)
            {
                RotateCommand* cmd = new RotateCommand(Direction::Left);
                commands.addCommand(cmd);
            }
            else if (std::strcmp(direction, Constants::RIGHT_COMMAND) == 0)
            {
                RotateCommand* cmd = new RotateCommand(Direction::Right);
                commands.addCommand(cmd);
            }
            else 
            {
                //TODO
                throw std::exception();
            }
        }
        else if (std::strcmp(command, Constants::ADD_COMMAND) == 0) 
        {
            char fileName[Constants::BASIC_BUFFER_SIZE];
            ss >> fileName;

            AddCommand* cmd = new AddCommand(fileName);

            commands.addCommand(cmd);
        }
        else if (std::strcmp(command, Constants::COLLAGE_COMMAND) == 0)
        {
            char direction[Constants::BASIC_BUFFER_SIZE];
            ss >> direction;

            char firstFile[Constants::BASIC_BUFFER_SIZE];
            ss >> firstFile;

            char secondFile[Constants::BASIC_BUFFER_SIZE];
            ss >> secondFile;

            char outImage[Constants::BASIC_BUFFER_SIZE];
            ss >> outImage;

            if (std::strcmp(direction, Constants::HORIZONTAL_COMMAND) == 0)
            {
                CollageCommand* cmd = new CollageCommand(Direction::Horizontal, firstFile, secondFile, outImage);

                commands.addCommand(cmd);
            }
            else if (std::strcmp(direction, Constants::VERTICAL_COMMAND) == 0)
            {
                CollageCommand* cmd = new CollageCommand(Direction::Vertical, firstFile, secondFile, outImage);

                commands.addCommand(cmd);
            }
        }
        else if (std::strcmp(command, Constants::SWITCH_COMMAND) == 0) 
        {
            int id;
            ss >> id;

            SwitchCommand* cmd = new SwitchCommand(id);

            commands.addCommand(cmd);
        }
        else if (std::strcmp(command, Constants::SESSION_INFO_COMMAND) == 0) 
        {
            char infoText[Constants::BASIC_BUFFER_SIZE];
            ss >> infoText;
            if (std::strcmp(infoText, "info") != 0)
            {
                continue;
            }
            this->sessionInfo();
        }
        else if (std::strcmp(command, Constants::UNDO_COMMAND) == 0) 
        {
            this->undoCommand();
        }
    }
}

void Engine::undoCommand() 
{
    for (int i = this->commands.getSize() - 1; i >= 0; i--)
    {
        UndoableCommand* cmd = dynamic_cast<UndoableCommand*>(this->commands[i]);
        if (cmd != nullptr)
        {
            this->commands.removeAt(i);
            return;
        }
    }
    std::cout << Constants::UNDOABLE_MESSAGE << std::endl;
}

void Engine::sessionInfo() const 
{
    this->editor.currentSessionInfo();
}

// Executes the commands consequentialy
void Engine::executeCommands()
{
    for (size_t i = 0; i < this->commands.getSize(); i++)
    {
        this->commands[i]->execute(this->editor);
    }
}

// Removes all commands
void Engine::removeCommands() 
{
    int size = this->commands.getSize();
    for (size_t i = 0; i < size; i++)
    {
        this->commands.removeLast();
    }
}