#include "scn/scene.h"
#include "ImGui/imgui.h"

Scene::Scene()
{
    vertices.clear();


    // Uncomment this vertices to display triangle
    /*
    vertices.push_back(Vertex(
        Vector3({-0.5f, -0.5f, 0.0f}), 
        Vector3({1.0f, 0.0f, 0.0f}),
        Vector3({ 0.0f, 0.0f, 0.0f }), 
        Vector2(0.0f, 0.0f))
    );
    vertices.push_back(Vertex(
        Vector3({ 0.5f, -0.5f, 0.0f }), 
        Vector3({ 0.0f, 1.0f, 0.0f}),
        Vector3({ 0.0f, 0.0f, 0.0f }), 
        Vector2(1.0f, 0.0f))
    );
    vertices.push_back(Vertex(
        Vector3({ 0.0f, 0.5f, 0.0f }), 
        Vector3({ 0.0f, 0.0f, 1.0f}),
        Vector3({ 0.0f, 0.0f, 0.0f }), 
        Vector2({ 0.5f, 1.0f }))
    );
    */


    // Load 3D object
    Renderer::loadModel(vertices);

}

Scene::~Scene()
{
    
}

void Scene::Update(const float deltaTime, Renderer& renderer)
{

    ShowImGuiControls(renderer);
    renderer.ApplyClearColor();
    renderer.Render(vertices);
    
}

void Scene::ShowImGuiControls(Renderer& renderer)
{
    //ImGUI 
    ImGuiIO io = ImGui::GetIO();

    if (ImGui::Begin("Controls"))
    {

        ImGui::Text("%f \n", io.Framerate);

        ImGui::ColorPicker3("Clear color", &renderer.ClearColor.x);
        ImGui::SliderFloat("eyeX %f", &renderer.Eye.x, -10, 10);
        ImGui::SliderFloat("eyeY %f", &renderer.Eye.y, -10, 10);
        ImGui::SliderFloat("eyeZ %f", &renderer.Eye.z, -10, 10);
        ImGui::SliderFloat("centerX %f", &renderer.Center.x, -10, 10);
        ImGui::SliderFloat("centerY %f", &renderer.Center.y, -10, 10);
        ImGui::SliderFloat("centerZ %f", &renderer.Center.z, -10, 10);
        ImGui::SliderFloat("upX %f", &renderer.Up.x, -10, 10);
        ImGui::SliderFloat("upY %f", &renderer.Up.y, -10, 10);
        ImGui::SliderFloat("upZ %f", &renderer.Up.z, -10, 10);
        ImGui::End();
    }
}
