#include "rdr/renderer.h"
#include <cassert>
#include <cmath>
#include "glad/glad.h"
#include "ImGui/imgui.h"
#include <../include/TinyObj/tiny_obj_loader.h>
#define TINYOBJLOADER_IMPLEMENTATION
#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>


#define COLOR_BUFFER_POS(x, y) (Width * (y) + (x))

Renderer::Renderer(uint32_t width, uint32_t height)
    :texture("assets/viking_room.jpeg")
{
    Width = width;
    Height = height;

    rWidth = (float_t)Width;
    rHeight = (float_t)Height;

    ColorBuffer = new Vector3[width * height];
    DepthBuffer = new float_t[width * height];

    Eye.x = 0;
    Eye.y = 0;
    Eye.z = 2;

    Center.x = 0;
    Center.y = 0;
    Center.z = 0;

    Up.x = 0;
    Up.y = 1;
    Up.z = 0;

    ClearColor = Vector3(0);

    CreateFrameBuffer();
}

Renderer::~Renderer()
{
    DestroyFrameBuffer();
    delete[] ColorBuffer;
    delete[] DepthBuffer;
}

Vector3 Renderer::LocalToScreen(const Vertex& vertex)
{
    const Vector3& position = vertex.vPosition;

    // Convert to homogenous coords
    Vector4 coords = Vector4(position.x, position.y, position.z, 1.0f);

    // Calculate MVP
    Matrix4x4 mvp = (Projection * View) * Model;

    // Apply MVP on coords
    Vector4 crds;
    crds = mvp * coords;

    // Calculate NDC
    Vector4 ndc = Vector4(crds.x / crds.w, crds.y / crds.w, crds.z / crds.w, crds.w / crds.w);

    // Apply viewport
    Vector3 screenCoords = Vector3(
        (Width / 2.0f) * (ndc.x + 1),
        (Height / 2.0f) * (ndc.y + 1),
        0.5f * ndc.z + 0.5f
    );

    return screenCoords;
}

void Renderer::ViewMatrix(const Vector3& eye, const Vector3& center, const Vector3& up, Matrix4x4& matrix)
{
    const Vector3 _up = up.Normalize();

    const Vector3 z = (eye - center).Normalize();
    const Vector3 x = Vector3::CrossProduct(_up, z).Normalize();
    const Vector3 y = Vector3::CrossProduct(z, x).Normalize();

    const float r03 = -Vector3::DotProduct(x, eye);
    const float r13 = -Vector3::DotProduct(y, eye);
    const float r23 = -Vector3::DotProduct(z, eye);

    matrix.value = { 
        { x.x, x.y, x.z, r03 },
        { y.x, y.y, y.z, r13 },
        { z.x, z.y, z.z, r23 },
        { 0.0f, 0.0f, 0.0f, 1.0f }
    };
}

void Renderer::ProjectionMatrix(const float fovY, const float aspectRatio, const float zNear, const float zFar, Matrix4x4& matrix)
{
    __assume(zFar > zNear);

    const float f = 1.0f / std::tan(fovY / 2.0f);
    const float zDiff = zFar - zNear;

    const float r00 = f / aspectRatio;
    const float r22 = -(zFar + zNear) / zDiff;
    const float r23 = -(2 * zFar * zNear) / zDiff;

    matrix.value = {
        { r00, 0.0f, 0.0f, 0.0f },
        { 0.0f, f, 0.0f, 0.0f },
        { 0.0f, 0.0f, r22, r23 },
        { 0.0f, 0.0f, -1.0f, 0.0f }
    };
}



bool Renderer::SetPixel(const uint32_t x, const uint32_t y)
{
    if (x < 0 || x >= Width)
        return false;

    if (y < 0 || y >= Height)
        return false;

    ColorBuffer[COLOR_BUFFER_POS(x, y)] = Vector3(1);
    return true;
}

bool Renderer::SetPixel(const uint32_t x, const uint32_t y, const Vector3& color)
{
    if (x < 0 || x >= Width)
        return false;

    if (y < 0 || y >= Height)
        return false;

    ColorBuffer[COLOR_BUFFER_POS(x, y)] = color;
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

void Renderer::DrawTriangle(Vector3 p1, Vector3 p2, Vector3 p3, const Vertex& v1, const Vertex& v2, const Vertex& v3)
{


    // SET CLAMP   
    float miniX;
    float miniY;
    float maxiX;
    float maxiY;

    miniX = std::min(p1.x, std::min(p2.x, p3.x));
    miniY = std::min(p1.y, std::min(p2.y, p3.y));

    maxiX = std::max(p1.x, std::max(p2.x, p3.x));
    maxiY = std::max(p1.y, std::max(p2.y, p3.y));

    miniX = std::clamp(miniX, 0.f, (float)rWidth);
    miniY = std::clamp(miniY, 0.f, (float)rHeight);
    maxiX = std::clamp(maxiX, 0.f, (float)rWidth);
    maxiY = std::clamp(maxiY, 0.f, (float)rHeight);

    
    // Color Interpolation
    for (unsigned int x = miniX; x < maxiX; x++)
    {
        for (unsigned int y = miniY; y < maxiY; y++)
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

            float posZ = p1.z * w1 + p2.z * w2 + p3.z * w3;

            if (DepthBuffer[y * Width + x] > posZ)
            {
                DepthBuffer[y * Width + x] = posZ;
            }

            else
            {
                continue;
            }
            Vector3 color = v1.vColor * w1 + v2.vColor * w2 + v3.vColor * w3;

            const Vector2 uv = v1.vUvs * w1 + v2.vUvs * w2 + v3.vUvs * w3;

            //Load texture
            color = texture.Sample(uv.x, uv.y);

            SetPixel(x, y , color);
        }
    }
}

void Renderer::loadModel(std::vector<Vertex>& vertices)
{
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, "assets/viking_room.obj"))
    {
        throw std::runtime_error(warn + err);
    }

    for (const auto& shape : shapes)
    {
        for (const auto& index : shape.mesh.indices)
        {
            Vertex vertex{};

            vertex.vPosition = {
                attrib.vertices[3 * index.vertex_index + 0],
                attrib.vertices[3 * index.vertex_index + 1],
                attrib.vertices[3 * index.vertex_index + 2]
            };

            vertex.vNormal = {
                attrib.normals[3 * index.normal_index + 0],
                attrib.normals[3 * index.normal_index + 1],
                attrib.normals[3 * index.normal_index + 2]
            };

            vertex.vColor = { 1.0f, 1.0f, 1.0f };

            vertex.vUvs = {
                attrib.texcoords[2 * index.texcoord_index + 0],
                1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
            };

            vertices.push_back(vertex);
        }
    }
}

void Renderer::Render(const std::vector<Vertex>& vertices)
{
    //Matrix
    ViewMatrix(Eye, Center, Up, View);
    ProjectionMatrix(M_PI / 2, (float)Width / Height, 0.1f, 100.f, Projection);
    Model.IdentityMatrix();


    std::vector<Vector3> NewVertices = std::vector<Vector3>(vertices.size());

    for (size_t i = 0; i < vertices.size(); i++)
    {
        const Vertex& index = vertices[i];

        Vector3 coords = index.vPosition;
        NewVertices[i] = LocalToScreen(vertices[i].vPosition);
    }

    for (size_t i = 0; i < vertices.size() / 3; i++)
    {
        Vector3 p1 = NewVertices[3 * i];
        Vector3 p2 = NewVertices[(3 * i + 1)];
        Vector3 p3 = NewVertices[(3 * i + 2)];

        DrawTriangle(p1, p2, p3, vertices[3 * i], vertices[(3 * i + 1)], vertices[(3 * i + 2)]);
    }

    UpdateFrameBuffer();
    if (ImGui::Begin("FrameBuffer"))
    {
        ImVec2 size = ImVec2(Width, Height);

        ImGui::Image((ImTextureID)TextureId, size);

        ImGui::End();
    }
}

void Renderer::CreateFrameBuffer()
{
    glGenTextures(1, &TextureId);
    glBindTexture(GL_TEXTURE_2D, TextureId);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_FLOAT, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::UpdateFrameBuffer()
{
    glBindTexture(GL_TEXTURE_2D, TextureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_FLOAT, ColorBuffer);
}

void Renderer::DestroyFrameBuffer()
{
    glDeleteTextures(1, &TextureId);
}

void Renderer::ApplyClearColor()
{
    // Range of pixels
    for (uint32_t y = 0; y < Height; y++)
    {
        for (uint32_t x = 0; x < Width; x++)
        {
            //Clear the pixel w/ empty vector3 ClearColor
            ColorBuffer[y * Width + x] = ClearColor;
            DepthBuffer[y * Width + x] = INFINITY;

        }
    }
}
