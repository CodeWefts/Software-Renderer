#pragma once

#include <stdint.h>
#include "ToolBox/vector.hpp"
#include "ToolBox/Vector3.hpp"
#include "ToolBox/matrix.hpp"
#include "ToolBox/Matrix4x4.hpp"
#include "rdr/Vertex.h"

class Renderer
{
private:
    uint32_t m_Width;
    uint32_t m_Height;

    Vector3* m_ColorBuffer;
    float_t* m_DepthBuffer;

    //PROJECTION MATRIX
    Matrix4x4 m_Projection;

    float fNear = 0.1f;
    float fFar = 1000.f;
    float fFov = 90.0f;
    float fAspectRatio = (float)m_Height / (float)m_Width;
    float fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);
    static float DotProduct(const Vector3& a, const Vector3& b);

    //VIEW MATRIX
    Matrix4x4 m_View;



    //MODEL MATRIX
    Matrix4x4 m_Model;


    //VIEWPORT MATRIX
    Matrix4x4 m_Viewport;

    uint32_t m_TextureId;

    void CreateFrameBuffer();
    void UpdateFrameBuffer();
    void DestroyFrameBuffer();

public:

    Vector3 Eye;
    Vector3 Center;
    Vector3 Up;

    void ApplyClearColor();
    Renderer(uint32_t width, uint32_t height);
    ~Renderer();

    void ProjectionMatrix(const float fovY, const float aspectRatio, const float zNear, const float zFar, Matrix4x4& dst);
    void ViewMatrix(const Vector3& eye, const Vector3& center, const Vector3& up, Matrix4x4& dst);
    void SetModelMatrix(const Matrix4x4& model);

    Vector3 LocalToScreen(const Vertex& vertex);
    void DrawTriangle(Vector3 p1, Vector3 p2, Vector3 p3, const Vertex& v1, const Vertex& v2, const Vertex& v3);

    bool SetPixel(const uint32_t x, const uint32_t y);
    bool SetPixel(const uint32_t x, const uint32_t y, const Vector3& color);

    void DrawLine(const uint32_t x0, const uint32_t y0, const uint32_t x1, const uint32_t y1);
    void DrawLine(const uint32_t x0, const uint32_t y0, const uint32_t x1, const uint32_t y1, const Vector3& color);

    Vector3 m_ClearColor;

    void Render(const std::vector<Vertex>& vertices);

};

/*
// Texture setup
RDR_API void rdrSetTexture(rdrImpl* renderer, float* colors32Bits, int width, int height);

// Draw a list of triangles
RDR_API void rdrDrawTriangles(rdrImpl* renderer, rdrVertex* vertices, int vertexCount);

struct ImGuiContext;
RDR_API void rdrSetImGuiContext(rdrImpl* renderer, struct ImGuiContext* context);
RDR_API void rdrShowImGuiControls(rdrImpl* renderer);*/
