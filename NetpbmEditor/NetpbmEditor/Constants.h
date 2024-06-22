#pragma once

struct Constants
{
	static const char* COULD_NOT_OPEN_FILE_ERROR_MESSAGE;
	static const char* INVALID_FILE_ERROR_MESSAGE;
	static const char* INVALID_INDEX_ERROR_MESSAGE;
	static const char* INVALID_SESSION_ERROR_MESSAGE;
	static const char* SWITCH_MESSAGE;
	static const char* INVALID_SWITCH_MESSAGE;
	static const char* UNDOABLE_MESSAGE;
	static const char* COLLAGE_MESSAGE;
	static const char* CLOSE_SESSION_MESSAGE;
	static const char* HELP_MESSAGE;
	static const char* CONSOLE_PREFIX;
	static const char* INVALID_MAGIC_NUMBER;
	static const char* INVALID_WIDTH;
	static const char* INVALID_HEIGHT;
	static const char* INVALID_MAXVALUE;
	static const char* LOAD_COMMAND;
	static const char* SAVE_COMMAND;
	static const char* GRAYSCALE_COMMAND;
	static const char* MONOCHROME_COMMAND;
	static const char* NEGATIVE_COMMAND;
	static const char* ROTATE_COMMAND;
	static const char* LEFT_COMMAND;
	static const char* RIGHT_COMMAND;
	static const char* ADD_COMMAND;
	static const char* COLLAGE_COMMAND;
	static const char* HORIZONTAL_COMMAND;
	static const char* VERTICAL_COMMAND;
	static const char* SWITCH_COMMAND;
	static const char* SESSION_INFO_COMMAND;
	static const char* UNDO_COMMAND;
	static const char* EXIT_COMMAND;
	static const char* CLOSE_COMMAND;
	static const char* HELP_COMMAND;
	static constexpr unsigned BASIC_BUFFER_SIZE = 1024;
	static constexpr double GRAYSCALE_RED = .299;
	static constexpr double GRAYSCALE_GREEN = .587;
	static constexpr double GRAYSCALE_BLUE = .144;
};