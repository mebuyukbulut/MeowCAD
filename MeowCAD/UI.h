#pragma once
#include <vector>
#include "TextEditor.h"
#include "Command.h"

struct GLFWwindow;


class UI{
	CommandManager CM;

	void MySaveFunction() {}
	TextEditor editor{};
	GLFWwindow* window{};
	bool is_text_editor_window_active = false;
	bool is_test_window_active = false;
	bool is_demo_window_active = false;

	void menu_bar();
	void text_editor_window();
	void test_window();
	void demo_window();
	void init_imgui();

public:
	void render();
	void init_UI(GLFWwindow* window);
};

