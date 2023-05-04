
#include "scene_impl.hpp"

scnImpl* scnCreate()
{
    return new scnImpl();
}

void scnDestroy(scnImpl* scene)
{
    delete scene;
}

void scnUpdate(scnImpl* scene, float deltaTime, rdrImpl* renderer)
{
    scene->update(deltaTime, renderer);
}

void scnSetImGuiContext(scnImpl* scene, struct ImGuiContext* context)
{
    //ImGui::SetCurrentContext(context);
}

void scnShowImGuiControls(scnImpl* scene)
{
    scene->showImGuiControls();
}

scnImpl::scnImpl()
{
    // HERE: Load the scene
    // Setup some vertices to test
    vertices = {
        //       pos                  normal                  color              uv
        {-0.5f,-0.5f, 0.0f,      0.0f, 0.0f, 0.0f,      1.0f, 0.0f, 0.0f,     0.0f, 0.0f },
        { 0.5f,-0.5f, 0.0f,      0.0f, 0.0f, 0.0f,      0.0f, 1.0f, 0.0f,     0.0f, 0.0f },
        { 0.0f, 0.5f, 0.0f,      0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 1.0f,     0.0f, 0.0f },
    };
}

scnImpl::~scnImpl()
{
    // HERE: Unload the scene
}

void scnImpl::update(float deltaTime, rdrImpl* renderer)
{
    // Draw

    rdrDrawTriangles(renderer, vertices.data(), (int)vertices.size());
}

void scnImpl::showImGuiControls()
{
}
