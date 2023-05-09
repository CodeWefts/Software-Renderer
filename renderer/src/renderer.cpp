#include "rdr/renderer.h"
#include <cassert>
#include <cmath>
#include "glad/glad.h"
#include "ImGui/imgui.h"
#define _USE_MATH_DEFINES
#include <math.h>


#define COLOR_BUFFER_POS(x, y) (m_Width * (y) + (x))

Renderer::Renderer(uint32_t width, uint32_t height)
    : m_Width(width), m_Height(height)
{
    m_ColorBuffer = new Vector3[width * height];
    m_DepthBuffer = new float_t[width * height];

    Eye.x = 0;
    Eye.y = 0;
    Eye.z = 2;

    Center.x = 0;
    Center.y = 0;
    Center.z = 0;

    Up.x = 0;
    Up.y = 1;
    Up.z = 0;

    m_ClearColor = Vector3(0);

    CreateFrameBuffer();
}

Renderer::~Renderer()
{
    DestroyFrameBuffer();
    delete[] m_ColorBuffer;
    delete[] m_DepthBuffer;
}

void Renderer::ProjectionMatrix(const float fovY, const float aspectRatio, const float zNear, const float zFar, Matrix4x4& dst)
{
    assert(zFar > zNear && "Z depth far must be greather that Z depth near");
    __assume(zFar > zNear);

    // cot(fovY / 2.0f)
    const float f = 1.0f / std::tan(fovY / 2.0f);
    const float zDiff = zFar - zNear;

    const float r00 = f / aspectRatio;
    const float r22 = -(zFar + zNear) / zDiff;
    const float r23 = -(2 * zFar * zNear) / zDiff;

    dst.Row0 = Vector4(r00, 0.0f, 0.0f, 0.0f);
    dst.Row1 = Vector4(0.0f, f, 0.0f, 0.0f);
    dst.Row2 = Vector4(0.0f, 0.0f, r22, r23);
    dst.Row3 = Vector4(0.0f, 0.0f, -1.0f, 0.0f);
}

float Renderer::DotProduct(const Vector3& a, const Vector3& b)
{
    float result = a.x * b.x + a.y * b.y + a.z * b.z;
    return result;
}

Vector3 Renderer::LocalToScreen(const Vertex& vertex)
{
    const Vector3& position = vertex.m_Position;

    // Convert to homogenous coords
    Vector4 coords = Vector4(position.x, position.y, position.z, 1.0f);

    // Calculate MVP
    Matrix4x4 mvp = m_Projection;

    mvp.Multiply(m_View);

    mvp.Multiply(m_Model);

    // Apply MVP on coords
    coords = mvp.Multiply(coords);
    
    // Calculate NDC
    Vector4 ndc = Vector4(coords.x / coords.w, coords.y / coords.w, coords.z / coords.w, coords.w / coords.w);

    // Apply viewport
    Vector3 screenCoords = Vector3(
        (m_Width / 2.0f) * (ndc.x + 1),
        (m_Height / 2.0f) * (ndc.y + 1),
        0.5f * ndc.z + 0.5f
    );

    return screenCoords;
}

void Renderer::ViewMatrix(const Vector3 & eye, const Vector3 & center, const Vector3 & up, Matrix4x4 & dst)
{
    const Vector3 _up = up.Normalize();

    const Vector3 z = (eye - center).Normalize();
    const Vector3 x = Vector3::CrossProduct(_up, z).Normalize();
    const Vector3 y = Vector3::CrossProduct(z, x).Normalize();

    const float r03 = -Vector3::DotProduct(x, eye);
    const float r13 = -Vector3::DotProduct(y, eye);
    const float r23 = -Vector3::DotProduct(z, eye);

    dst.Row0 = Vector4(x.x, x.y, x.z, r03);
    dst.Row1 = Vector4(y.x, y.y, y.z, r13);
    dst.Row2 = Vector4(z.x, z.y, z.z, r23);
    dst.Row3 = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
}

void Renderer::SetModelMatrix(const Matrix4x4& model)
{
    m_Model.Row0 = Vector4(1, 0, 0, 0);
    m_Model.Row1 = Vector4(0, 1, 0, 0);
    m_Model.Row2 = Vector4(0, 0, 1, 0);
    m_Model.Row3 = Vector4(0, 0, 0, 1);
    //TRS
}

bool Renderer::SetPixel(const uint32_t x, const uint32_t y)
{
    if (x < 0 || x >= m_Width)
        return false;

    if (y < 0 || y >= m_Height)
        return false;

    m_ColorBuffer[COLOR_BUFFER_POS(x, y)] = Vector3(1);
    return true;
}

bool Renderer::SetPixel(const uint32_t x, const uint32_t y, const Vector3& color)
{
    if (x < 0 || x >= m_Width)
        return false;

    if (y < 0 || y >= m_Height)
        return false;

    m_ColorBuffer[COLOR_BUFFER_POS(x, y)] = color;
    return true;
}

void Renderer::DrawLine(uint32_t x0, uint32_t y0, const uint32_t x1, const uint32_t y1)
{
    int32_t dx = std::abs((int32_t)(x1 - x0));
    int32_t sx = x0 < x1 ? 1 : -1;
    int32_t dy = std::abs((int32_t)(y1 - y0));
    int32_t sy = y0 < y1 ? 1 : -1;
    int32_t err = (dx > dy ? dx : -dy) / 2;
    int32_t e2;

    for (;;)
    {
        if (!SetPixel(x0, y0))
        {
            break;
        }

        if (x0 == x1 && y0 == y1)
            break;

        e2 = err;
        if (e2 > -dx)
        {
            err -= dy;
            x0 += sx;
        }

        if (e2 < dy)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void Renderer::DrawLine(uint32_t x0, uint32_t y0, const uint32_t x1, const uint32_t y1, const Vector3& color)
{
    int32_t dx = std::abs((int32_t)(x1 - x0));
    int32_t sx = x0 < x1 ? 1 : -1;
    int32_t dy = std::abs((int32_t)(y1 - y0));
    int32_t sy = y0 < y1 ? 1 : -1;
    int32_t err = (dx > dy ? dx : -dy) / 2;
    int32_t e2;

    for (;;)
    {
        if (!SetPixel(x0, y0, color))
        {
            break;
        }

        if (x0 == x1 && y0 == y1)
            break;

        e2 = err;
        if (e2 > -dx)
        {
            err -= dy;
            x0 += sx;
        }

        if (e2 < dy)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void Renderer::Render(const std::vector<Vertex>& vertices)
{
    ViewMatrix(Eye, Center, Up, m_View);
    ProjectionMatrix(M_PI / 2, (float)m_Width / m_Height, 0.1f, 100.f, m_Projection);
    SetModelMatrix(m_Model);
    //std::cout << m_Model << "\n\n" << m_View << "\n\n" << m_Projection << endl;

    std::vector<Vector3> NewVertices = std::vector<Vector3>(vertices.size());

    for (size_t i = 0; i < vertices.size(); i++)
    {
        const Vertex& index = vertices[i];

        Vector3 coords = index.m_Position;
        NewVertices[i] = LocalToScreen(coords);
    }

    for (size_t i = 0; i < vertices.size(); i++)
    {
        Vector3 p1 = NewVertices[i];
        Vector3 p2 = NewVertices[(i + 1) % vertices.size()];
        Vector3 p3 = NewVertices[(i + 2) % vertices.size()];

        DrawTriangle(p1, p2, p3, vertices[i], vertices[(i + 1) % vertices.size()], vertices[(i + 2) % vertices.size()]);
    }

    UpdateFrameBuffer();
    if (ImGui::Begin("FrameBuffer"))
    {
        ImVec2 size = ImVec2(m_Width, m_Height);

        ImGui::Image((ImTextureID)m_TextureId, size);

        ImGui::End();
    }
}

void Renderer::CreateFrameBuffer()
{
    glGenTextures(1, &m_TextureId);
    glBindTexture(GL_TEXTURE_2D, m_TextureId);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_FLOAT, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::UpdateFrameBuffer()
{
    /*DrawLine(60, 180, 240, 180, IM_COL32_BLACK);
    DrawLine(240, 180, 150, 90, IM_COL32_BLACK);
    DrawLine(150, 90, 60, 180, IM_COL32_BLACK);*/
    glBindTexture(GL_TEXTURE_2D, m_TextureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_FLOAT, m_ColorBuffer);
}

void Renderer::DestroyFrameBuffer()
{
    glDeleteTextures(1, &m_TextureId);
}

void Renderer::ApplyClearColor()
{
    for (uint32_t y = 0; y < m_Height; y++)
    {
        for (uint32_t x = 0; x < m_Width; x++)
        {
            m_ColorBuffer[y * m_Width + x] = m_ClearColor;
        }
    }
}

void Renderer::DrawTriangle(Vector3 p1, Vector3 p2, Vector3 p3, const Vertex& v1, const Vertex& v2, const Vertex& v3)
{
    for (unsigned int x = 0; x < m_Width; x++)
    {
        for (unsigned int y = 0; y < m_Height; y++)
        {
            const float denominator = (p2.y - p3.y) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.y - p3.y);

            const float w1 = ((p2.y - p3.y) * (x - p3.x) + (p3.x - p2.x) * (y - p3.y)) / denominator;
            if (w1 < 0)
                continue;

            const float w2 = ((p3.y - p1.y) * (x - p3.x) + (p1.x - p3.x) * (y - p3.y)) / denominator;
            if (w2 < 0)
                continue;

            const float w3 = 1 - w1 - w2;
            if (w3 < 0)
                continue;

            const Vector3 color = v1.m_Color * w1 + v2.m_Color * w2 + v3.m_Color * w3;

            SetPixel(x, y , color);
        }
    }
}

/*
void rdrSetTexture(rdrImpl* renderer, float* colors32Bits, int width, int height)
{
    assert(renderer != nullptr);
    // TODO(later): Store
}

void Renderer::rdrDrawTriangles(rdrImpl* renderer, rdrVertex* vertices, int count)
{
    assert(renderer != nullptr);

    // For each triangles
    // TODO: Convert vertex local coords to screen coords
    // TODO: Draw triangle with lines (using drawLine)
    // Transform vertex list to triangle into colorBuffer
}*/

