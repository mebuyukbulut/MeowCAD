#include "Command.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Engine.h"
#include "LogUtils.h"

void PolygonModeFillCommand::execute(){
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	LogUtils::get().log("GL Polygon Mode: GL_FILL");
}
void PolygonModeLineCommand::execute(){
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	LogUtils::get().log("GL Polygon Mode: GL_LINE");
}
void PolygonModePointCommand::execute(){
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	LogUtils::get().log("GL Polygon Mode: GL_POINT");
}
void ExitProgramCommand::execute(){
	Engine::get().exit();
}



//GLFWwindow* window=0; // there must be a better approach
void CommandManager::init() {
	commands.resize(4);

	commands[static_cast<int>(CommandID::PolygonModeFill)] = new PolygonModeFillCommand();
	commands[static_cast<int>(CommandID::PolygonModeLine)] = new PolygonModeLineCommand();
	commands[static_cast<int>(CommandID::PolygonModePoint)] = new PolygonModePointCommand();
	commands[static_cast<int>(CommandID::ExitProgram)] = new ExitProgramCommand();

}
CommandManager::CommandManager() {
	init();
}
CommandManager::~CommandManager() {
	for (auto i : commands)
		delete i;
	commands.clear();
}
void CommandManager::exec(CommandID commandID) {
	commands[static_cast<int>(commandID)]->execute();
}