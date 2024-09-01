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
	bool is_material_winodw_active = false; 

	void menu_bar();
	void text_editor_window();
	void test_window();
	void demo_window();
	void log_window();
	void credits_window();
	void outliner_window();
	void properties_window();
	void material_window();

	void init_imgui();

public:
	void render();
	void init_UI(GLFWwindow* window);

public:
	//void toggle_window_visibility(AllWindows window);
};

