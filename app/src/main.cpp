#include <vector>
#include <iostream>

#include <rdr/renderer.h>
#include <scn/scene.h>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"


int32_t SetupGlfw()
{
    //Check versionning
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    glfwSetErrorCallback(
        [](int error, const char* description)
        {
            std::cerr << "GLFW error " << error << ": " << description << std::endl;
        }
    );

    if (!glfwInit())
        return false;

    return true;
}

GLFWwindow* CreateWindow()
{
    //Creation of glfw window
    return glfwCreateWindow(800, 600, "Rasterizer", nullptr, nullptr);
}

void SetupWindow(GLFWwindow* window)
{
    glfwMakeContextCurrent(window);

    gladLoadGL();
    glEnable(GL_MULTISAMPLE);
    glfwSwapInterval(1); // Enable vsync
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void SetupImGui(GLFWwindow* window)
{
    // Setup ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable viewports

    io.Fonts->AddFontDefault();

    // GL 3.0 + GLSL 130
    const char* const glslVersion = "#version 130";

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glslVersion);
}

void StartImGuiFrame() 
{
    // Start ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void UpdateGlFrameBuffer(GLFWwindow* window)
{
    int displayW, displayH;
    glfwGetFramebufferSize(window, &displayW, &displayH);
    glViewport(0, 0, displayW, displayH);

    glClear(GL_COLOR_BUFFER_BIT);
}

void Render(GLFWwindow* window)
{
    ImGui::Render();
    UpdateGlFrameBuffer(window);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    GLFWwindow* ctxBackup = glfwGetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(ctxBackup);
}

int main(int argc, char** argv)
{
    if (!SetupGlfw())
        return 1;

    GLFWwindow* window = CreateWindow();
    if (window == nullptr)
        return 1;

    SetupWindow(window);

    SetupImGui(window);

    const uint32_t width = 800;
    const uint32_t height = 600;

    Renderer* renderer = new Renderer(width, height);
    Scene* scene = new Scene();

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        StartImGuiFrame();

        scene->Update(ImGui::GetIO().DeltaTime, *renderer);

        Render(window);
        glfwSwapBuffers(window);
    }

    delete scene;
    delete renderer;

    return 0;
}
