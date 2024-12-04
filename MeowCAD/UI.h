#pragma once
#include <vector>
#include "TextEditor.h"
#include "Command.h"
#include "EViewport.h"

struct GLFWwindow;
class Mesh;

enum class AllWindows {
	TEXT_EDITOR, TEST, DEMO
};

class UI{
	CommandManager CM;

	void MySaveFunction() {}
	TextEditor editor{};
	GLFWwindow* window{};

	bool disabled = false; 

	bool is_text_editor_window_active = false;
	bool is_test_window_active = false;
	bool is_demo_window_active = false;
	bool is_log_window_active = true;
	bool is_credits_window_active = false;
	bool is_outliner_window_active = true;
	bool is_properties_window_active = true;
	bool is_material_window_active = false;
	//bool is_viewport_window_active = true;
	bool is_color_tooltip_active = false; 
	bool is_camera_preferences_active = false;
	bool is_skybox_window_active = true; 
	
	

	void menu_bar();
	void text_editor_window();
	void test_window();
	void demo_window();
	void log_window();
	void credits_window();
	void outliner_window();
	void viewport_window();
	void properties_window();
	void properties_window_transform(Mesh* mesh);
	void properties_window_material(Mesh* mesh);
	void color_tooltip();
	void camera_preferences_window();
	void material_window();
	void skybox_window();
	void skybox_window_skybox();
	void skybox_window_matcap();

	void init_imgui();
	EViewport* viewport;

public:
	bool is_disabled();
	void set_disabled(bool value);

	void render();
	void init_UI(GLFWwindow* window);
	void set_viewport(EViewport* viewport);


public:
	//void toggle_window_visibility(AllWindows window);
};

