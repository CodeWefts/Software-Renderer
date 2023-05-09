#pragma once

#include "ToolBox/vector.hpp"
#include "ToolBox/Vector3.hpp"
#include "ToolBox/Vector4.hpp"


class Vertex
{
public:
    Vector3 m_Position;
    Vector3 m_Color;
    Vector3 m_Normal;
    Vector2 m_Uvs;

    Vertex(const Vector3& position);
    Vertex(const Vector3& position, const Vector3& color);
    Vertex(const Vector3& position, const Vector3& color, const Vector3& normal, const Vector2 uv);

    void SetPosition(const Vector3& position);
    void SetColor(const Vector3& color);
    void SetNormal(const Vector3& normal);
    void SetUv(const Vector2 uv);


    void SetPositionAndNormal(const Vector3& position);
};

