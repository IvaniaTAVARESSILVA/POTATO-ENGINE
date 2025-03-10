#include "../include/ConsoleManager.h"

void Console::Log(std::string message, API API, LEVEL errorLvl)
{
	switch (errorLvl)
	{
	case LEVEL::SUCCESS:
		{
			std::string successMessage = setLog(API, LEVEL::SUCCESS, message, GREEN);
			std::cout << successMessage << std::endl;
			ImGuiConsoleManager::GetInstance().Log(successMessage);
			break;
		}
	case LEVEL::INFO:
		{
			std::string infoMessage = setLog(API, LEVEL::INFO, message, CYAN);
			std::cout << infoMessage << std::endl;
			ImGuiConsoleManager::GetInstance().Log(infoMessage);
			break;
		}
	case LEVEL::WARNING:
		{
			std::string warnMessage = setLog(API, LEVEL::WARNING, message, YELLOW);
			std::cout << warnMessage << std::endl;
			ImGuiConsoleManager::GetInstance().Log(warnMessage);

			break;
		}
	case LEVEL::PRINT:
		{
			std::string printMessage = setLog(API, LEVEL::PRINT, message, WHITE);
			std::cout << printMessage << std::endl;
			ImGuiConsoleManager::GetInstance().Log(printMessage);
			break;
		}
	case LEVEL::ERRORS:
		{
			std::string errorMessage = setLog(API, LEVEL::ERRORS, message, RED);
			std::cerr << errorMessage << std::endl;
			ImGuiConsoleManager::GetInstance().Log(errorMessage);

			break;
		}
	default:
		break;
	}
}

void Console::Sample()
{
	Log("I'm an info", API::PHYSICS, LEVEL::INFO);
	Log("I'm a success", API::MAIN, LEVEL::SUCCESS);
	Log("I'm a print", API::DX11, LEVEL::PRINT);
	Log("I'm a warning", API::INPUT, LEVEL::INFO);
	Log("I'm a warning", API::SHADER, LEVEL::SUCCESS);
	Log("I'm an error", API::MODEL, LEVEL::ERRORS);
	Log("I'm the default message");
	//Throw(API::OPENGL,LEVEL::ERRORS, "I'm an error and I end the program");
}
