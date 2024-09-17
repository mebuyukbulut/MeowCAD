#pragma once
#include <vector>

enum class CommandID : int {
	PolygonModeFill = 0,
	PolygonModeLine = 1,
	PolygonModePoint = 2,

	ExitProgram = 3,

	AddNewCube = 4,
	AddNewCylinder = 5,
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

class ExitProgramCommand : public Command {
public:
	void execute();
};


class AddNewCubeCommand : public Command {
public:
	void execute();
};

class AddNewCylinderCommand : public Command {
public:
	void execute();
};

class DeleteSelectedMeshCommand : public Command {
	class MeshManager* meshman;
public:
	void init(MeshManager* meshman);
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