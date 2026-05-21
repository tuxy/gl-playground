#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

struct ProgramParams {
  float camX;
  float camY;
  float camZ;
  float camRotX;
  float camRotY;
  float camRotZ;
};

class TestController {
public:
  ProgramParams params;
  void init(GLFWwindow *window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
  };

  void create_frame() {
    ImGui_ImplGlfw_NewFrame();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();
    show_window();
  }
  void render() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }

  void show_window() {
    if (!ImGui::Begin("Controller")) {
      ImGui::End();
      return;
    }

    ImGui::DragFloat("camX", &this->params.camX, 0.005f);
    ImGui::DragFloat("camY", &this->params.camY, 0.005f);
    ImGui::DragFloat("camZ", &this->params.camZ, 0.005f);

    ImGui::SliderFloat("camRotX", &this->params.camRotX, -90.0f, 90.0f);
    ImGui::SliderFloat("camRotY", &this->params.camRotY, -90.0f, 90.0f);
    ImGui::SliderFloat("camRotZ", &this->params.camRotZ, -90.0f, 90.0f);

    ImGui::End();
  }
};
