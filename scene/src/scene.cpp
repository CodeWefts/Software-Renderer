#include "scn/scene.h"
#include "ImGui/imgui.h"

Scene::Scene()
{
    m_Vertices.clear();

    m_Vertices.push_back(Vertex(Vector3({-0.5f, -0.5f, 0.0f}), Vector3({1.0f, 0.0f, 0.0f}),
        Vector3({ 0.0f, 0.0f, 0.0f }), Vector2(0.0f, 0.0f)));
    m_Vertices.push_back(Vertex(Vector3({ 0.5f, -0.5f, 0.0f }), Vector3({ 0.0f, 1.0f, 0.0f}),
        Vector3({ 0.0f, 0.0f, 0.0f }), Vector2(0.0f, 0.0f)));
    m_Vertices.push_back(Vertex(Vector3({ 0.0f, 0.5f, 0.0f }), Vector3({ 0.0f, 0.0f, 1.0f}),
        Vector3({ 0.0f, 0.0f, 0.0f }), Vector2({ 0.0f, 0.0f })));
}

Scene::~Scene()
{
    
}

void Scene::Update(const float deltaTime, Renderer& renderer)
{
    ShowImGuiControls(renderer);
    renderer.ApplyClearColor();
    renderer.Render(m_Vertices);
    
}

void Scene::SetImGuiContext(struct ImGuiContext* context)
{

}

void Scene::ShowImGuiControls(Renderer& renderer)
{
    if (ImGui::Begin("Controls"))
    {
        ImGui::ColorPicker3("Clear color", &renderer.m_ClearColor.x);
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
