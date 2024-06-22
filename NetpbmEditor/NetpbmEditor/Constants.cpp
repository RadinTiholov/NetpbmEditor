#include "Constants.h"

const char* Constants::COULD_NOT_OPEN_FILE_ERROR_MESSAGE = "Could not open file!";
const char* Constants::INVALID_FILE_ERROR_MESSAGE = "Invalid file!";
const char* Constants::INVALID_INDEX_ERROR_MESSAGE = "Invalid index!";
const char* Constants::INVALID_SESSION_ERROR_MESSAGE = "No active session! Please choose (switch) or create a new one (load)!";
const char* Constants::INVALID_MAGIC_NUMBER = "Invalid magic number!";
const char* Constants::INVALID_WIDTH = "Invalid width!";
const char* Constants::INVALID_HEIGHT = "Invalid height!";
const char* Constants::INVALID_MAXVALUE = "Invalid max value!";
const char* Constants::COLLAGE_MESSAGE = "Cannat make collage if the two files are not the same format!";
const char* Constants::CLOSE_SESSION_MESSAGE = "Current session is closed. Please choose (switch) or create a new one (load)!";
const char* Constants::HELP_MESSAGE = "Welcome to the Image Processing Program! Below are the available commands:\n 1. load <file1> <file2> ...: Starts a new user session with the given image files.\n 2. close: Closes the current session.\n 3. save: Saves all images in the current session with all applied transformations.\n 4. saveas <new_filename>: Saves the first loaded image under a new name with all applied transformations.\n 5. exit: Exits the program.\n Transformations:\n 1. grayscale: Converts all color images in the current session to grayscale.\n 2. monochrome: Converts all color images in the current session to black and white.\n 3. negative: Applies a negative filter to all images in the current session.\n 4. rotate <direction>: Rotates all images in the current session 90 degrees. <direction>: left or right.\n 5. collage <direction> <image1> <image2> <outimage>: Creates a collage from two images and adds the result to the current session. <direction>: horizontal or vertical.\n Session Management:\n 1. undo: Reverts the last transformation applied in the current session.\n 2. add <image>: Adds a new image to the current session without applying existing transformations.\n 3. session info: Displays information about the current session, including the session ID, loaded images, and pending transformations.\n 4. switch <session>: Switches to the session with the given ID.\n";

const char* Constants::CONSOLE_PREFIX = "> ";
const char* Constants::SWITCH_MESSAGE = "You switched to session with ID: ";
const char* Constants::INVALID_SWITCH_MESSAGE = "Session with such ID does not exist!";
const char* Constants::UNDOABLE_MESSAGE = "No undoable commands available in current session!";

const char* Constants::LOAD_COMMAND = "load";
const char* Constants::SAVE_COMMAND = "save";
const char* Constants::GRAYSCALE_COMMAND = "grayscale";
const char* Constants::MONOCHROME_COMMAND = "monochrome";
const char* Constants::NEGATIVE_COMMAND = "negative";
const char* Constants::ROTATE_COMMAND = "rotate";
const char* Constants::LEFT_COMMAND = "left";
const char* Constants::RIGHT_COMMAND = "right";
const char* Constants::ADD_COMMAND = "add";
const char* Constants::COLLAGE_COMMAND = "collage";
const char* Constants::VERTICAL_COMMAND = "vertical";
const char* Constants::HORIZONTAL_COMMAND = "horizontal";
const char* Constants::SWITCH_COMMAND = "switch";
const char* Constants::SESSION_INFO_COMMAND = "session";
const char* Constants::UNDO_COMMAND = "undo";
const char* Constants::EXIT_COMMAND = "exit";
const char* Constants::CLOSE_COMMAND = "close";
const char* Constants::HELP_COMMAND = "help";