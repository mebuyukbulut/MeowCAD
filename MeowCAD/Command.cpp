#include "Command.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Engine.h"
#include "LogUtils.h"
#include "MaterialManager.h"
#include "MeshManager.h"

#include "Transform.h"
#include "Mesh.h"
#include "Cube.h"
#include "Cylinder.h"

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


void AddNewCubeCommand::execute(){
	Mesh* new_mesh = new Mesh();
	new_mesh->set_ID(112); // Every mesh need a unique ID 
	new_mesh->set_name("New cube");

	Shape3D* shape = new Cube();
	new_mesh->set_data(shape->get_data());

	auto material = MaterialManager::get().get_default_material();
	new_mesh->set_material(material);
	//new_mesh->set_texture(&texture);
	Transform transform;
	transform.make_dirty();
	transform.set_position(glm::vec3(0, 0, 0));
	new_mesh->set_transform(transform);
	Engine::get().scene.mesh_manager.add_mesh(new_mesh);

	LogUtils::get().log("A new cube was created");
}
void AddNewCylinderCommand::execute(){
	Mesh* new_mesh = new Mesh();
	new_mesh->set_ID(111); // Every mesh need a unique ID 
	new_mesh->set_name("New cylinder");

	Shape3D* shape = new Cylinder();
	new_mesh->set_data(shape->get_data());

	auto material = MaterialManager::get().get_default_material();
	new_mesh->set_material(material);
	//new_mesh->set_texture(&texture);
	Transform transform;
	transform.make_dirty();
	transform.set_position(glm::vec3(0, 0, 0));
	new_mesh->set_transform(transform);
	Engine::get().scene.mesh_manager.add_mesh(new_mesh);


	LogUtils::get().log("A new cylinder was created");
}





//GLFWwindow* window=0; // there must be a better approach
void CommandManager::init() {
	commands.resize(6);

	commands[static_cast<int>(CommandID::PolygonModeFill)] = new PolygonModeFillCommand();
	commands[static_cast<int>(CommandID::PolygonModeLine)] = new PolygonModeLineCommand();
	commands[static_cast<int>(CommandID::PolygonModePoint)] = new PolygonModePointCommand();
	commands[static_cast<int>(CommandID::ExitProgram)] = new ExitProgramCommand();
	commands[static_cast<int>(CommandID::AddNewCube)] = new AddNewCubeCommand();
	commands[static_cast<int>(CommandID::AddNewCylinder)] = new AddNewCylinderCommand();

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

void DeleteSelectedMeshCommand::init(MeshManager* meshman){
	this->meshman = meshman;
}

void DeleteSelectedMeshCommand::execute(){
	meshman->destroy_mesh();
}
