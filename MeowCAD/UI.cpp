#include "UI.h"
#include "Command.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"

#include "TextEditor.h"
#include <tchar.h>

#include "LogUtils.h"
#include "Engine.h"

#include "Shape3D.h"
#include "Transform.h"

void UI::menu_bar() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Exit")) CM.exec(CommandID::ExitProgram);
            
            if (ImGui::MenuItem("Create")) {}
            if (ImGui::MenuItem("Open", "Ctrl+O")) {}
            if (ImGui::MenuItem("Save", "Ctrl+S")) {}
            if (ImGui::MenuItem("Save as..")) {}
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Edit")) {
            if (ImGui::MenuItem("Add Cube")) {
                Mesh* new_mesh = new Mesh();
                new_mesh->set_ID(111); // Every mesh need a unique ID 
                new_mesh->set_name("New cube");

                Shape3D* shape = new Cube();
                new_mesh->set_data(shape->get_data());


                auto material = MaterialManager::get().get_default_material();
                new_mesh->set_material(material);
                //new_mesh->set_texture(&texture);
                Transform transform;
                transform.make_dirty();
                transform.set_position(glm::vec3(0,0,0));
                new_mesh->set_transform(transform);
                Engine::get().scene.add_mesh(new_mesh);
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("View")) {
            // we can implement this things with commands 
            if (ImGui::MenuItem("Text Editor", "", &is_text_editor_window_active)) {}
            if (ImGui::MenuItem("Show Test", "", &is_test_window_active)) {}
            if (ImGui::MenuItem("Show Demo", "", &is_demo_window_active)) {}
            if (ImGui::MenuItem("Show LOG", "", &is_log_window_active)) {}
            if (ImGui::MenuItem("Show Credits", "", &is_credits_window_active)) {}
            if (ImGui::MenuItem("Show Outliner", "", &is_outliner_window_active)) {}
            if (ImGui::MenuItem("Show Viewport", "", &viewport->get_active())) {}

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("OGL")) {
            if(ImGui::BeginMenu("Polygon Mode")){
                if (ImGui::MenuItem("Fill")) CM.exec(CommandID::PolygonModeFill);                
                if (ImGui::MenuItem("Line")) CM.exec(CommandID::PolygonModeLine);                
                if (ImGui::MenuItem("Point")) CM.exec(CommandID::PolygonModePoint);                
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
    ImGui::Begin("Text Editor Demo", &is_text_editor_window_active, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_MenuBar);
    ImGui::SetWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);
    if (ImGui::BeginMenuBar()){
        if (ImGui::BeginMenu("File")){
            if (ImGui::MenuItem("Save")){
                auto textToSave = editor.GetText();
                /// save text....
            }
            if (ImGui::MenuItem("Quit", "Alt-F4"))
                return;
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit")){
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

        if (ImGui::BeginMenu("View")){
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
void UI::log_window(){
    // Create a window called "My First Tool", with a menu bar.
    ImGui::Begin("LOG", &is_log_window_active, ImGuiWindowFlags_MenuBar);
    if (ImGui::BeginMenuBar()){
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
            if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */ }
            if (ImGui::MenuItem("Close", "Ctrl+W")) { is_log_window_active = false; }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    //ImGui::BeginChild("Log");
    auto logs = LogUtils::get().get_log();
    for(auto& log :logs)        
        ImGui::TextColored(log.first, log.second.c_str());
    //ImGui::EndChild();

    ImGui::End();
}

void UI::credits_window(){
    ImGui::Begin("Credits",&is_credits_window_active);
    ImGui::Text("MeowCad @2024");
    ImGui::Text("Barkin KOYUNCU");
    ImGui::Text("Muhammet Esat BUYUKBULUT");

    ImGui::End();
}



void UI::viewport_window(){
    ImGui::Begin("Viewport", &viewport->get_active());	

    auto t_size = ImGui::GetWindowSize();
    glm::ivec2 window_size{ t_size.x, t_size.y};

    if (window_size != viewport->get_resolution()) {
        viewport->set_resolution(window_size);
        viewport->set_dirty(true);
    }
    ImGui::Image(
        (ImTextureID)viewport->texID(),
        ImGui::GetContentRegionAvail(),
        ImVec2(0, 1),
        ImVec2(1, 0)
    );
    ImGui::End();
}

void UI::outliner_window() {
    ImGui::Begin("Outliner", &is_outliner_window_active, disabled ? ImGuiWindowFlags_NoInputs : ImGuiWindowFlags_None);

    ImGuiTreeNodeFlags flag = ImGuiTreeNodeFlags_DefaultOpen;



    if (ImGui::TreeNodeEx("root", flag)){
        if (ImGui::IsItemClicked())
            std::cout << "root" << std::endl;

        for (auto& i : Engine::get().scene.get_names()) {
            if(ImGui::TreeNodeEx(i.first.c_str(), ImGuiTreeNodeFlags_Leaf)) {
                if (ImGui::IsItemClicked()) {
                    std::cout << i.first << std::endl;
                    Engine::get().scene.select_mesh(i.second);
                    is_properties_window_active = true;
                }
                ImGui::TreePop(); 
            }
        }

        
        // Call ImGui::TreeNodeEx() recursively to populate each level of children
        ImGui::TreePop();  // This is required at the end of the if block
    }

    ImGui::End();

}


void UI::properties_window(){
    ImGui::Begin("Properties", &is_properties_window_active);
    Mesh* mesh = Engine::get().scene.get_selected_mesh();

    if (!mesh) {
        ImGui::End();
        return;
    }

    properties_window_transform(mesh);
    properties_window_material(mesh);



    ImGui::End();
}

void UI::properties_window_transform(Mesh* mesh){
    ImGui::Text("Transform");
    ImGui::Separator();

    Transform t = mesh->get_transform();

    glm::vec3 t_pos = t.get_position();
    glm::vec3 t_rot = t.get_euler_rotation();
    glm::vec3 t_old_rot = t_rot;
    glm::vec3 t_scl = t.get_scale();


    if (ImGui::DragFloat3("Position:", &t_pos[0], 0.1))  t.set_position(t_pos);
    if (ImGui::DragFloat3("Rotation:", &t_rot[0])) {
        //std::cout << t_old_rot.x << "\t" << t_old_rot.y << "\t" << t_old_rot.z << " \told\n";
        //std::cout << t_rot.x << "\t" << t_rot.y << "\t" << t_rot.z << " \tnew\n";
        t.set_euler_delta_rotation(t_rot - t_old_rot);
    }
    if (ImGui::DragFloat3("Scale:", &t_scl[0], 0.1)) t.set_scale(t_scl);


    //std::cout << t_rot.x << " \tnew\n";

    mesh->set_transform(t);
}

void UI::properties_window_material(Mesh* mesh){
    ImGui::NewLine();
    ImGui::Text("Material");
    ImGui::Separator(); // ------------------------------------------------------


    // this is not a good approach for showing materials. 
    static int material_selected_item = 0; // it should show material of selected mesh 

    // create material
    if (ImGui::Button("Create New Material")) {
        mesh->set_material(MaterialManager::get().create_material());
        material_selected_item = MaterialManager::get().get_all_materials().size() - 1;
    }
    // delete material 
    if (ImGui::Button("Delete Material")) {
        MaterialManager::get().destroy_material(mesh->get_material()->get_ID().ID);
        mesh->set_material(MaterialManager::get().get_default_material());
        material_selected_item = 0;
    }

    // list materials
    auto material_names = MaterialManager::get().get_names_cchar();
    if (ImGui::Combo("All materials", &material_selected_item, material_names.data(), material_names.size())) {
        Material* selected_material = MaterialManager::get().get_material_by_nameIndex(material_selected_item);
        mesh->set_material(selected_material);
        std::cout << material_selected_item;
    }

    // -----------------


    auto material = mesh->get_material();
    auto material_info = material->get();
    auto old_material_info = material_info;

    ImGui::Text(material->get_ID().name.c_str());

    bool mat_info_control = false;
    mat_info_control |= ImGui::ColorPicker3("albedo", &material_info.albedo[0]);
    mat_info_control |= ImGui::DragFloat("metallic", &material_info.metallic, 0.02, 0, 1);
    mat_info_control |= ImGui::DragFloat("roughness", &material_info.roughness, 0.02, 0, 1);
    mat_info_control |= ImGui::DragFloat("ao", &material_info.ao, 0.02, 0, 1);

    if (mat_info_control)
        material->set(material_info);
}

void UI::material_window(){
    ImGui::Begin("Materials", &is_properties_window_active);

    ImGui::End();
}



void UI::init_imgui() {
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 440");


    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.Fonts->AddFontFromFileTTF("fonts/Roboto-Regular.ttf", 18, NULL, io.Fonts->GetGlyphRangesCyrillic());
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
    
    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;
    
    io.ConfigWindowsResizeFromEdges = true;
    io.ConfigWindowsMoveFromTitleBarOnly = true;

    //io. = false;

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

    // dock directly to main window
    ImGuiID dockspace_id = ImGui::DockSpaceOverViewport();


    menu_bar();


    if (is_text_editor_window_active) text_editor_window();
    if (is_test_window_active) test_window();
    if (is_demo_window_active) demo_window();
    if (is_log_window_active) log_window();
    if (is_credits_window_active) credits_window();
    if (is_outliner_window_active) outliner_window();
    if (is_properties_window_active) properties_window();
    if (is_material_window_active) material_window();
    if (viewport->is_active()) viewport_window();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

void UI::init_UI(GLFWwindow* window) {
    this->window = window;
    init_imgui();

}