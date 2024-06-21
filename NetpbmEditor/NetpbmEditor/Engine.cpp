#include "Engine.h"

void Engine::start()
{
    parseCommandsFrom(std::cin);
}

void Engine::parseCommandsFrom(std::istream& ifs) 
{
    while (true)
    {
        std::cout << Constants::CONSOLE_PREFIX;
        char line[Constants::BASIC_BUFFER_SIZE];
        ifs.getline(line, Constants::BASIC_BUFFER_SIZE);
        std::stringstream ss(line);
        char command[Constants::BASIC_BUFFER_SIZE];
        ss >> command;

        if (std::strcmp(command, Constants::LOAD_COMMAND) == 0)
        {
            char fileName[Constants::BASIC_BUFFER_SIZE];
            ss >> fileName;

            this->editor.load(fileName);
        }
        else if (std::strcmp(command, Constants::SAVE_COMMAND) == 0)
        {
            this->editor.save();
        }
        else if(std::strcmp(command, Constants::GRAYSCALE_COMMAND) == 0)
        {
            this->editor.addGrayscaleCommandToCurrentSession();
        }
        else if (std::strcmp(command, Constants::MONOCHROME_COMMAND) == 0)
        {
            this->editor.addMonochromeCommandToCurrentSession();
        }
        else if (std::strcmp(command, Constants::NEGATIVE_COMMAND) == 0)
        {
            this->editor.addNegativeCommandToCurrentSession();
        }
        else if (std::strcmp(command, Constants::ROTATE_COMMAND) == 0)
        {
            char direction[Constants::BASIC_BUFFER_SIZE];
            ss >> direction;

            this->editor.addRotateCommand(direction);
        }
        else if (std::strcmp(command, Constants::ADD_COMMAND) == 0) 
        {
            char fileName[Constants::BASIC_BUFFER_SIZE];
            ss >> fileName;

            this->editor.addAddCommand(fileName);
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

            this->editor.addCollageCommand(direction, firstFile, secondFile, outImage);
        }
        else if (std::strcmp(command, Constants::SWITCH_COMMAND) == 0) 
        {
            int id;
            ss >> id;

            this->editor.switchSessions(id);
        }
        else if (std::strcmp(command, Constants::SESSION_INFO_COMMAND) == 0) 
        {
            char infoText[Constants::BASIC_BUFFER_SIZE];
            ss >> infoText;
            if (std::strcmp(infoText, "info") != 0)
            {
                continue;
            }
            this->editor.currentSessionInfo();
        }
        else if (std::strcmp(command, Constants::UNDO_COMMAND) == 0) 
        {
            this->editor.undoCommandFromCurrentSession();
        }
        else if (std::strcmp(command, Constants::EXIT_COMMAND) == 0)
        {
            break;
        }
    }
}