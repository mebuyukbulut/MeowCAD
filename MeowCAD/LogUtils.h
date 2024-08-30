#pragma once


#include <string>
#include <iostream>
#include <deque>

#include "imgui.h"

//enum class LogColor {
//	red, blue, white, yellow
//};
enum class LogType {
	message, warning, error, success
};

class LogUtils{

	//
	//     SINGLETON PATTERN
	//
	LogUtils() {}
public:
	static LogUtils& get()
	{
		static LogUtils instance; // Guaranteed to be destroyed.
		// Instantiated on first use.
		return instance;
	}
	LogUtils(LogUtils const&) = delete;
	void operator=(LogUtils const&) = delete;


	//
	//     CLASS
	//

private:
	std::deque<std::pair<ImVec4, std::string>> logs;
public:
	std::deque<std::pair<ImVec4, std::string>>& get_log() {
		return logs;
	}
	void log(std::string message, LogType messageType = LogType::message) {
		std::pair<ImVec4, std::string> p;

		switch (messageType){
		case LogType::message:
			p.first = ImVec4(1, 1, 1, 1);
			break;
		case LogType::warning:
			p.first = ImVec4(1, 1, 0, 1);
			break;
		case LogType::error:
			p.first = ImVec4(1, 0, 0, 1);
			break;
		case LogType::success:
			p.first = ImVec4(0, 1, 0, 1);
			break;
		default:
			p.first = ImVec4(1, 1, 1, 1);
			break;
		}
		p.second = message; 

		logs.push_back(p);
	}
	//void log(std::string message, LogType lt = LogType::message) {
	//	switch (lt) {
	//	case LogType::message:
	//		std::cout << "LOG: ";
	//		break;
	//	case LogType::warning:
	//		std::cout << "\033[1;33mWARNING: ";
	//		break;
	//	case LogType::error:
	//		std::cout << "\033[1;31mERROR: ";
	//		break;
	//	case LogType::success:
	//		std::cout << "\033[1;32mSUCCESS: ";
	//		break;
	//	default:
	//		break;
	//	}

	//	std::cout << message;

	//	std::cout << "\033[0m";
	//	std::cout << std::endl;
	//}
	//void hr() {
	//	std::cout << "-<|>-<O>-<|>-<O>-<|>-<O>-<|>-<O>-<|>-<O>-<|>-<O>-<|>-<O>-<|>-<O>-<|>-<O>-<|>-\n";
	//}
	//void br(int i = 1) {
	//	for (int j{}; j < i; j++)
	//		std::cout << std::endl;
	//}

	//void clearScreen() {
	//	// https://mathbits.com/MathBits/CompSci/Introduction/clear.htm#:~:text=To%20clear%20the%20screen%20in,to%20%22flush%22%20the%20iostream.
	//	system("CLS");
	//}
private:

};


///






// Terminal colors
// https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal
// https://en.wikipedia.org/wiki/ANSI_escape_code#Colors

// What is a queue family? 
// https://stackoverflow.com/questions/55272626/what-is-actually-a-queue-family-in-vulkan




// https://stackoverflow.com/questions/55272626/what-is-actually-a-queue-family-in-vulkan