#include "UI.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"

#include "TextEditor.h"
#include <tchar.h>

void UI::menu_bar() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Create")) {
            }
            if (ImGui::MenuItem("Open", "Ctrl+O")) {
            }
            if (ImGui::MenuItem("Save", "Ctrl+S")) {
            }
            if (ImGui::MenuItem("Save as..")) {
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit")) {
            if (ImGui::MenuItem("Add Cube")) {
                //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }
            //if (ImGui::MenuItem("Line")) {
            //    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            //}
            //if (ImGui::MenuItem("Point")) {
            //    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            //}
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("View")) {
            if (ImGui::MenuItem("Text Editor", "", &is_text_editor_window_active)) {
            }
            if (ImGui::MenuItem("Show Test", "", &is_test_window_active)) {
            }
            if (ImGui::MenuItem("Show Demo", "", &is_demo_window_active)) {
            }


            ImGui::EndMenu();
        }


        if (ImGui::BeginMenu("OGL")) {
            if(ImGui::BeginMenu("Polygon Mode")){
                if (ImGui::MenuItem("Fill")) {
                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                }
                if (ImGui::MenuItem("Line")) {
                    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                }
                if (ImGui::MenuItem("Point")) {
                    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
                }
                ImGui::EndMenu();
            }



            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

}

void UI::text_editor_window() {
    editor.SetColorizerEnable(false);
    auto cpos = editor.GetCursorPosition();
    ImGui::Begin("Text Editor Demo", nullptr, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_MenuBar);
    ImGui::SetWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Save"))
            {
                auto textToSave = editor.GetText();
                /// save text....
            }
            if (ImGui::MenuItem("Quit", "Alt-F4"))
                return;
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            bool ro = editor.IsReadOnly();
            if (ImGui::MenuItem("Read-only mode", nullptr, &ro))
                editor.SetReadOnly(ro);
            ImGui::Separator();

            if (ImGui::MenuItem("Undo", "ALT-Backspace", nullptr, !ro && editor.CanUndo()))
                editor.Undo();
            if (ImGui::MenuItem("Redo", "Ctrl-Y", nullptr, !ro && editor.CanRedo()))
                editor.Redo();

            ImGui::Separator();

            if (ImGui::MenuItem("Copy", "Ctrl-C", nullptr, editor.HasSelection()))
                editor.Copy();
            if (ImGui::MenuItem("Cut", "Ctrl-X", nullptr, !ro && editor.HasSelection()))
                editor.Cut();
            if (ImGui::MenuItem("Delete", "Del", nullptr, !ro && editor.HasSelection()))
                editor.Delete();
            if (ImGui::MenuItem("Paste", "Ctrl-V", nullptr, !ro && ImGui::GetClipboardText() != nullptr))
                editor.Paste();

            ImGui::Separator();

            if (ImGui::MenuItem("Select all", nullptr, nullptr))
                editor.SetSelection(TextEditor::Coordinates(), TextEditor::Coordinates(editor.GetTotalLines(), 0));

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("View"))
        {
            if (ImGui::MenuItem("Dark palette"))
                editor.SetPalette(TextEditor::GetDarkPalette());
            if (ImGui::MenuItem("Light palette"))
                editor.SetPalette(TextEditor::GetLightPalette());
            if (ImGui::MenuItem("Retro blue palette"))
                editor.SetPalette(TextEditor::GetRetroBluePalette());
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    //ImGui::Text(reinterpret_cast<const char*>(u8"Glyph test '\ue000'"));
    //ImGui::Text("%6d/%-6d %6d lines  | %s | %s | %s | %s", cpos.mLine + 1, cpos.mColumn + 1, editor.GetTotalLines(),
    //    editor.IsOverwrite() ? "Ovr" : "Ins",
    //    editor.CanUndo() ? "*" : " ",
    //    editor.GetLanguageDefinition().mName.c_str(), fileToEdit);

    editor.Render("TextEditor");
    ImGui::End();
}
void UI::test_window() {
    ImGui::Begin("demo");
    ImGui::Text("Hello, world %d", 123);
    if (ImGui::Button("Save"))
        MySaveFunction();
    //ImGui::InputText("string", buf, IM_ARRAYSIZE(buf));
    static float f{};
    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);

    ImGui::End();
}

void UI::demo_window() {
    ImGui::ShowDemoWindow();
}

void UI::init_imgui() {
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 440");
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("fonts/Roboto-Regular.ttf", 18, NULL, io.Fonts->GetGlyphRangesCyrillic());

    //ImGuiIO& io = ImGui::GetIO();
    //io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Verdana.ttf"e, DefaultFontSize, NULL io.Fonts->GetGlyphRangesCyrillic());
    //ImGui variables: 
    //bool show_demo_window = true;
    //bool show_another_window = false;

}

void UI::render() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();


    menu_bar();

    if (is_text_editor_window_active)
        text_editor_window();
    if (is_test_window_active)
        test_window();
    if (is_demo_window_active)
        demo_window();


    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

void UI::init_UI(GLFWwindow* window) {
    this->window = window;
    init_imgui();
}