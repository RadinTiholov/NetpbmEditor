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

            this->editor.load();

            while (!ss.eof())
            {
                ss >> fileName;
                this->editor.addAddCommand(fileName);
            }
        }
        else if (std::strcmp(command, Constants::SAVE_COMMAND) == 0)
        {
            try
            {
                this->editor.save();
            }
            catch (const std::logic_error& err)
            {
                std::cout << err.what() << std::endl;
            }
        }
        else if(std::strcmp(command, Constants::GRAYSCALE_COMMAND) == 0)
        {
            try
            {
                this->editor.addGrayscaleCommandToCurrentSession();
            }
            catch (const std::logic_error& err)
            {
                std::cout << err.what() << std::endl;
            }
        }
        else if (std::strcmp(command, Constants::MONOCHROME_COMMAND) == 0)
        {
            try
            {
                this->editor.addMonochromeCommandToCurrentSession();
            }
            catch (const std::logic_error& err)
            {
                std::cout << err.what() << std::endl;
            }
        }
        else if (std::strcmp(command, Constants::NEGATIVE_COMMAND) == 0)
        {
            try
            {
                this->editor.addNegativeCommandToCurrentSession();
            }
            catch (const std::logic_error& err)
            {
                std::cout << err.what() << std::endl;
            }
        }
        else if (std::strcmp(command, Constants::ROTATE_COMMAND) == 0)
        {
            try
            {
                char direction[Constants::BASIC_BUFFER_SIZE];
                ss >> direction;

                this->editor.addRotateCommand(direction);
            }
            catch (const std::logic_error& err)
            {
                std::cout << err.what() << std::endl;
            }
        }
        else if (std::strcmp(command, Constants::ADD_COMMAND) == 0) 
        {
            try
            {
                char fileName[Constants::BASIC_BUFFER_SIZE];
                ss >> fileName;

                this->editor.addAddCommand(fileName);
            }
            catch (const std::logic_error& err)
            {
                std::cout << err.what() << std::endl;
            }
        }
        else if (std::strcmp(command, Constants::COLLAGE_COMMAND) == 0)
        {
            try
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
            catch (const std::logic_error& err)
            {
                std::cout << err.what() << std::endl;
            }
        }
        else if (std::strcmp(command, Constants::SWITCH_COMMAND) == 0) 
        {
            int id;
            ss >> id;

            this->editor.switchSessions(id);
        }
        else if (std::strcmp(command, Constants::SESSION_INFO_COMMAND) == 0) 
        {
            try
            {
                char infoText[Constants::BASIC_BUFFER_SIZE];
                ss >> infoText;
                if (std::strcmp(infoText, "info") != 0)
                {
                    continue;
                }
                this->editor.currentSessionInfo();
            }
            catch (const std::logic_error& err)
            {
                std::cout << err.what() << std::endl;
            }
        }
        else if (std::strcmp(command, Constants::UNDO_COMMAND) == 0) 
        {
            try
            {
                this->editor.undoCommandFromCurrentSession();
            }
            catch (const std::logic_error& err)
            {
                std::cout << err.what() << std::endl;
            }
        }
        else if (std::strcmp(command, Constants::EXIT_COMMAND) == 0)
        {
            break;
        }
        else if (std::strcmp(command, Constants::CLOSE_COMMAND) == 0)
        {
            try
            {
                this->editor.closeCurrentSession();
            }
            catch (const std::logic_error& err)
            {
                std::cout << err.what() << std::endl;
            }
        }
    }
}