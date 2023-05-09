#pragma once

#include <vector>

#include "rdr/Vertex.h"
#include "rdr/renderer.h"

class Scene
{
private:
    std::vector<Vertex> m_Vertices;

public:
    Scene();
    ~Scene();
    void Update(const float deltaTime, Renderer& renderer);

    void SetImGuiContext(struct ImGuiContext* context);
    void ShowImGuiControls(Renderer& renderer);
};
