#pragma once

#include <iostream>
#include <vector>
#include <regex>
#include <unordered_map>

#include"..\..\Libraries\imgui\imgui.h"

/**
 * @brief ANSI Color Code to ImGui Color Mapping
 *
 * This unordered map is used to map ANSI color codes to ImGui color representations.
 */
const std::unordered_map<std::string, ImVec4> ANSI_COLOR_MAP = {
	{"\x1B[31m", ImVec4(1.0f, 0.0f, 0.0f, 1.0f)}, // RED
	{"\x1B[32m", ImVec4(0.0f, 1.0f, 0.0f, 1.0f)}, // GREEN
	{"\x1B[33m", ImVec4(1.0f, 1.0f, 0.0f, 1.0f)}, // YELLOW
	{"\x1B[34m", ImVec4(0.0f, 0.0f, 1.0f, 1.0f)}, // BLUE
	{"\x1B[35m", ImVec4(1.0f, 0.0f, 1.0f, 1.0f)}, // MAGENTA
	{"\x1B[36m", ImVec4(0.0f, 1.0f, 1.0f, 1.0f)}, // CYAN
	{"\x1B[37m", ImVec4(1.0f, 1.0f, 1.0f, 1.0f)}, // WHITE

	{"\x1B[38;5;210m", ImVec4(1.0f, 0.6f, 0.7f, 1.0f)}, // PASTEL RED (Soft Pink)
	{"\x1B[38;5;150m", ImVec4(0.6f, 1.0f, 0.6f, 1.0f)}, // PASTEL GREEN (Mint)
	{"\x1B[38;5;229m", ImVec4(1.0f, 1.0f, 0.8f, 1.0f)}, // PASTEL YELLOW (Light Cream)
	{"\x1B[38;5;147m", ImVec4(0.6f, 0.8f, 1.0f, 1.0f)}, // PASTEL BLUE (Sky Blue)
	{"\x1B[38;5;183m", ImVec4(0.8f, 0.6f, 1.0f, 1.0f)}, // PASTEL MAGENTA (Lavender)
	{"\x1B[38;5;159m", ImVec4(0.6f, 1.0f, 0.9f, 1.0f)}, // PASTEL CYAN (Aqua)
	{"\x1B[38;5;141m", ImVec4(0.7f, 0.5f, 0.9f, 1.0f)}, // PASTEL PURPLE
	{"\033[0m", ImVec4(1.0f, 1.0f, 1.0f, 1.0f)} // RESET (Default white)
};

/**
 * @brief ImGuiConsoleManager class for managing and rendering console logs in an ImGui interface.
 *
 * This class handles logging messages with ANSI color codes, stores them, and displays them with the appropriate ImGui color formatting.
 */
class ImGuiConsoleManager
{
public:
	/**
	 * @brief Retrieves the singleton instance of ImGuiConsoleManager.
	 *
	 * @return The singleton instance of the ImGuiConsoleManager.
	 */
	static ImGuiConsoleManager& GetInstance()
	{
		static ImGuiConsoleManager instance;
		return instance;
	}

	/**
	 * @brief Logs a message to the console with ANSI color parsing.
	 *
	 * @param message The message to log.
	 *
	 * This function parses the ANSI color codes in the input message and stores the segments for rendering.
	 */
	void Log(const std::string& message)
	{
		std::vector<std::pair<std::string, ImVec4>> parsedSegments = ParseAnsiColors(message);

		if (logs.size() >= 100)
		{
			logs.erase(logs.begin()); // Limit log size to 100
		}
		logs.push_back(parsedSegments);
		scrollToBottom = true;
	}

	/**
	 * @brief Clears all logged messages from the console.
	 */
	void Clear()
	{
		logs.clear();
	}

	/**
	 * @brief Draws the console logs in the ImGui window.
	 *
	 * @param title The title to display at the top of the ImGui window.
	 */
	void Draw(const char* title)
	{
		ImGui::Begin(title);
		ImGui::BeginChild("ScrollingRegion", ImVec2(ImGui::GetWindowWidth(), ImGui::GetWindowHeight()), true);

		for (const auto& logLine : logs)
		{
			for (const auto& segment : logLine)
			{
				ImGui::TextColored(segment.second, "%s", segment.first.c_str());
				ImGui::SameLine();
			}
			ImGui::NewLine(); // Move to the next log line
		}

		if (scrollToBottom)
		{
			ImGui::SetScrollHereY(1.0f);
			scrollToBottom = false;
		}

		ImGui::EndChild();
		ImGui::End();
	}

	/**
	 * @brief Draws an input field for the user to type messages in the ImGui window.
	 */
	void DrawInput()
	{
		if (ImGui::InputText("Input", inputBuffer, IM_ARRAYSIZE(inputBuffer)))
		{
			if (inputBuffer[0] != '\0')
			{
				Log(inputBuffer);
				memset(inputBuffer, 0, sizeof(inputBuffer));
			}
		}
	}

	/**
	 * @brief Deleted copy constructor to prevent copying of the singleton instance.
	 */
	ImGuiConsoleManager(const ImGuiConsoleManager&) = delete;

	/**
	 * @brief Deleted assignment operator to prevent assigning of the singleton instance.
	 *
	 * @return Reference to the ImGuiConsoleManager instance.
	 */
	ImGuiConsoleManager& operator=(const ImGuiConsoleManager&) = delete;

private:
	/**
	 * @brief Private constructor to prevent direct instantiation of ImGuiConsoleManager.
	 */
	ImGuiConsoleManager() : scrollToBottom(false) {}

	/**
	 * @brief Destructor for ImGuiConsoleManager.
	 */
	~ImGuiConsoleManager() {}

	/**
	 * @brief A vector holding the log entries, with each log containing multiple segments (text and color).
	 */
	std::vector<std::vector<std::pair<std::string, ImVec4>>> logs;

	/**
	 * @brief A buffer for user input text.
	 */
	char inputBuffer[256] = "";

	/**
	 * @brief A flag indicating whether the console should scroll to the bottom.
	 */
	bool scrollToBottom;

	/**
	 * @brief Parses ANSI color codes from the given text and returns a vector of pairs (text, color).
	 *
	 * @param text The input text containing ANSI color codes.
	 *
	 * @return A vector of pairs where each pair consists of the text and its corresponding color.
	 */
	std::vector<std::pair<std::string, ImVec4>> ParseAnsiColors(const std::string& text)
	{
		std::vector<std::pair<std::string, ImVec4>> result;
		std::regex ansiPattern(R"((\x1B\[[0-9;]*m))"); // Match ANSI color codes
		std::sregex_token_iterator iter(text.begin(), text.end(), ansiPattern, {-1, 0});
		std::sregex_token_iterator end;

		ImVec4 currentColor = ANSI_COLOR_MAP.at("\033[0m"); // Default to white
		std::string currentText;

		for (; iter != end; ++iter)
		{
			std::string part = iter->str();
			if (ANSI_COLOR_MAP.find(part) != ANSI_COLOR_MAP.end())
			{
				if (!currentText.empty())
				{
					result.emplace_back(currentText, currentColor);
					currentText.clear();
				}
				currentColor = ANSI_COLOR_MAP.at(part);
			}
			else
			{
				currentText += part;
			}
		}

		if (!currentText.empty())
		{
			result.emplace_back(currentText, currentColor);
		}

		return result;
	}
};
