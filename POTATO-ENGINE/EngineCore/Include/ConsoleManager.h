#pragma once

#include <iostream>
#include <cstdlib>

#include "ImGuiConsoleManager.h"

#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE    "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN    "\x1B[36m"
#define WHITE   "\x1B[37m"

#define PASTEL_RED      "\x1B[38;5;210m"
#define PASTEL_GREEN    "\x1B[38;5;150m"
#define PASTEL_YELLOW   "\x1B[38;5;229m"
#define PASTEL_BLUE     "\x1B[38;5;147m"
#define PASTEL_MAGENTA  "\x1B[38;5;183m"
#define PASTEL_CYAN     "\x1B[38;5;159m"
#define PASTEL_PURPLE   "\x1B[38;5;141m"

#define RESET   "\033[0m"

/**
 * @brief Log level enumeration.
 */
enum class LEVEL { INFO, WARNING, ERRORS, PRINT, SUCCESS };

/**
 * @brief API source enumeration.
 */
enum class API { DX11, OPENGL, MAIN, INPUT, PHYSICS, RENDERER, SHADER, MODEL, UI };

/**
 * @brief Console class for logging messages with different APIs and log levels.
 */
class Console
{
public:
	/**
	  * @brief Logs a message with API and error level.
	  * @param message The message to log.
	  * @param API The API source of the log (default: MAIN).
	  * @param errorLvl The log level (default: PRINT).
	  */
	void Log(std::string message, API API = API::MAIN, LEVEL errorLvl = LEVEL::PRINT);
	/**
	 * @brief Retrieves the singleton instance of Console.
	 * @return Reference to the Console instance.
	 */
	static Console& GetInstance()
	{
		static Console instance;
		return instance;
	}

	/**
	 * @brief Retrieves the singleton instance of Console.
	 * @return Reference to the Console instance.
	 */
	Console& operator=(const Console&) = delete;

	/**
   * @brief Here is a simple method to sample of the logs.
   */
	void Sample();

private:
	/**
	 * @brief Retrieves a formatted API string with color.
	 * @param API The API enum value.
	 * @return A formatted string representing the API.
	 */
	static std::string getAPIString(API API)
	{
		switch (API)
		{
		case API::DX11: return "[" + setColor(GREEN, "DX11") + "]";
		case API::OPENGL: return "[" + setColor(BLUE, "OPENGL") + "]";
		case API::MAIN: return "[" + setColor(PASTEL_CYAN, "MAIN") + "]";
		case API::INPUT: return "[" + setColor(CYAN, "INPUT") + "]";
		case API::PHYSICS: return "[" + setColor(MAGENTA, "PHYSICS") + "]";
		case API::RENDERER: return "[" + setColor(RED, "RENDERER") + "]";
		case API::MODEL: return "[" + setColor(PASTEL_MAGENTA, "MODEL") + "]";
		case API::SHADER: return "[" + setColor(PASTEL_RED, "SHADER") + "]";
		case API::UI: return "[" + setColor(PASTEL_GREEN, "UI") + "]";
		default: return "[UNKNOWN]";
		}
	}

	/**
	 * @brief Retrieves a formatted log level string with color.
	 * @param level The log level enum value.
	 * @return A formatted string representing the log level.
	 */
	static std::string getLevelString(LEVEL level)
	{
		switch (level)
		{
		case LEVEL::INFO: return "[" + setColor(BLUE, "INFO") + "] ";
		case LEVEL::WARNING: return "[" + setColor(YELLOW, "WARNING") + "] ";
		case LEVEL::ERRORS: return "[" + setColor(RED, "ERROR") + "] ";
		case LEVEL::PRINT: return "[" + setColor(WHITE, "PRINT") + "] ";
		case LEVEL::SUCCESS: return "[" + setColor(GREEN, "SUCCESS") + "] ";
		default: return "[UNKNOWN]";
		}
	}

	/**
	* @brief Sets color formatting for text.
	* @param color The color code.
	* @param text The text to colorize.
	* @return The formatted string.
	*/
	static std::string setColor(std::string_view color, std::string_view text)
	{
		return std::string(color) + std::string(text) + RESET;
	}

	/**
	 * @brief Formats a log message with API, level, and color.
	 * @param api The API source.
	 * @param level The log level.
	 * @param text The log message.
	 * @param color The color code.
	 * @return The formatted log message.
	 */
	static std::string setLog(API api, LEVEL level, std::string_view text, const char* color)
	{
		return getAPIString(api) + getLevelString(level) + setColor(color, text);
	};
};

/**
 * @brief Global instance of Console.
 */
static Console& console = Console::GetInstance();
