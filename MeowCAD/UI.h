#pragma once
#include <vector>
#include "TextEditor.h"
#include "Command.h"

struct GLFWwindow;

enum class AllWindows {
	TEXT_EDITOR, TEST, DEMO
};

class UI{
	CommandManager CM;

	void MySaveFunction() {}
	TextEditor editor{};
	GLFWwindow* window{};
	bool is_text_editor_window_active = false;
	bool is_test_window_active = false;
	bool is_demo_window_active = false;
	bool is_log_window_active = true;
	bool is_credits_window_active = false;
	bool is_outliner_window_active = false;
	bool is_properties_window_active = false;
	bool is_material_window_active = false;
	bool is_viewport_window_active = true;
	
	

	void menu_bar();
	void text_editor_window();
	void test_window();
	void demo_window();
	void log_window();
	void credits_window();
	void outliner_window();
	void viewport_window();
	void properties_window();

	void material_window();

	void init_imgui();

public:

	unsigned int viewport_texID;
	bool viewport_dirty = true;
	ImVec2 viewport_resolution{ 0,0 };


	void render();
	void init_UI(GLFWwindow* window);
	void set_viewport_texture(unsigned int texID) {
		viewport_texID = texID;
	}

public:
	//void toggle_window_visibility(AllWindows window);
};

