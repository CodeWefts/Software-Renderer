#pragma once

#include <stdint.h>
#include "ToolBox/matrix.hpp"
#include "ToolBox/Matrix4x4.hpp"
#include "rdr/Vertex.h"
#include "Texture.h"
#include "light.h"


class Renderer
{
private:

    std::vector<Light> m_Lights;

    uint32_t Width;
    uint32_t Height;

    float_t rWidth;
    float_t rHeight;

    Texture texture;

    Vector3* ColorBuffer;
    float_t* DepthBuffer;

    //PROJECTION MATRIX
    Matrix4x4 Projection;

    float fNear = 0.1f;
    float fFar = 1000.f;
    float fFov = 90.0f;
    float fAspectRatio = (float)Height / (float)Width;
    float fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);
    //static float DotProduct(const Vector3& a, const Vector3& b);

    //VIEW
    Matrix4x4 View;

    //MODEL
    Matrix4x4 Model;

    //VIEWPORT
    Matrix4x4 Viewport;

    uint32_t TextureId;

    

    void CreateFrameBuffer();
    void UpdateFrameBuffer();
    void DestroyFrameBuffer();

public:

    Vector3 Eye;
    Vector3 Center;
    Vector3 Up;

    //3D MODEL LOADING
    const uint32_t WIDTH = 800;
    const uint32_t HEIGHT = 600;

    static void loadModel(std::vector<Vertex>& vertices);

    const std::string MODEL_PATH = "assets/vikingRoom.obj";
    const std::string TEXTURE_PATH = "assets/viking_room.jpeg";

    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    void ApplyClearColor();
    Renderer(uint32_t width, uint32_t height);
    ~Renderer();

    void ViewMatrix(const Vector3& eye, const Vector3& center, const Vector3& up, Matrix4x4& dst);
    void ProjectionMatrix(const float fovY, const float aspectRatio, const float zNear, const float zFar, Matrix4x4& matrix);
    void ModelMatrix(const Vector3& translation, const Vector3& rotation, const Vector3& scale);
    Vector3 ViewportTrans(Vector3 ndc);

    Vector3 ApplyLights(Vector3 color, const Vertex& v1, Vector3 ViewPos, Vector3 LightDir, Vector3 FragPos);

    Vector3 LocalToScreen(const Vertex& vertex);
    void DrawTriangle(Vector3 p1, Vector3 p2, Vector3 p3, const Vertex& v1, const Vertex& v2, const Vertex& v3);

    bool SetPixel(const uint32_t x, const uint32_t y);
    bool SetPixel(const uint32_t x, const uint32_t y, const Vector3& color);

    void DrawLine(const uint32_t x0, const uint32_t y0, const uint32_t x1, const uint32_t y1);
    void DrawLine(const uint32_t x0, const uint32_t y0, const uint32_t x1, const uint32_t y1, const Vector3& color);

    Vector3 ClearColor;

    void Render(const std::vector<Vertex>& vertices);

};