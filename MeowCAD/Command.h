#pragma once
#include <vector>

enum class CommandID : int {
	PolygonModeFill = 0,
	PolygonModeLine = 1,
	PolygonModePoint = 2,
	ExitProgram = 3
};

class Command{
public:
	virtual void execute() = 0;
};

class PolygonModeFillCommand : public Command {
public:
	void execute();
};
class PolygonModeLineCommand : public Command {
public:
	void execute();
};
class PolygonModePointCommand : public Command {
public:
	void execute();
};

struct GLFWwindow;
class ExitProgramCommand : public Command {
	GLFWwindow* window;
public:
	ExitProgramCommand(GLFWwindow* window);
	void execute();
};


class CommandManager { // probably we should implement skeleton pattern
	std::vector<Command*> commands;
	void init();

public:
	CommandManager();
	~CommandManager();
	void exec(CommandID commandID);

};