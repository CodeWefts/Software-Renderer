#pragma once

#include <vector>

#include "rdr/Vertex.h"
#include "rdr/renderer.h"

class Scene
{
private:
    std::vector<Vertex> vertices;

public:
    Scene();
    ~Scene();
    void Update(const float deltaTime, Renderer& renderer);

    void ShowImGuiControls(Renderer& renderer);
};
