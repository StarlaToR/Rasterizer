#pragma once


#include <Framebuffer.hpp>

// Vertex format (only one supported for now)
struct rdrVertex
{
    float x, y, z;    // Pos
    float nx, ny, nz; // Normal
    float r, g, b, a; // Color
    float u, v;       // Texture coordinates
};

struct color
{
    float red;
    float green;
    float blue;
    float alpha;
};

struct Viewport
{

    Viewport(const int p_x, const int p_y, uint p_width, uint p_height):
    x(p_x),y(p_y),width(p_width),height(p_height){}

    const int x;
    const int y;
    uint width; 
    uint height;
};


class Renderer
{
private:
    Framebuffer* fb;
    Viewport viewport;

    Mat4 modelMatrix;
    Mat4 projectionMatrix;
    Mat4 viewMatrix;

    Vec4 lineColor = { 0.f, 1.f, 1.f, 1.f };

public:
// Color and depth buffer have to be valid until the shutdown of the renderer
// Color buffer is RGBA, each component is a 32 bits float
// Depth buffer is a buffer of 32bits floats
    Renderer(float* p_colorBuffer32Bits, float* p_depthBuffer, uint p_width, uint p_height);
    Renderer(Framebuffer* f, const uint p_width, const uint p_height);
    ~Renderer();

    void SetProjection(Mat4 p_projectionMatrix);
    void SetView(Mat4 p_viewMatrix);
    void SetModel(Mat4 p_modelMatrix);
    Mat4 GetProjection();
    Mat4 GetView();
    Mat4 GetModel();
    void SetViewport(const int p_x, const int p_y, const uint p_width, const uint p_height);
    void SetTexture(float* p_colors32Bits, const uint p_width, const uint p_height);

    void DrawPixel(uint p_x, uint p_y, float p_z, const Vec4& p_color);

    void transformVertices(Vec3& vertices);

    void FillTriangle(const Vec4& p0, const Vec4& p1, const Vec4& p2, Vec4& color);
    void FillTriangle(const Vec4& p0, const Vec4& p1, const Vec4& p2);

    bool CheckDepth(int x, int y, float z);

    bool wireFrameOn=true;

    void DrawTriangle(rdrVertex* p_vertices);

private:
    
    void ShowImGuiControls();
    Vec4 VertexGraphicPipeline(rdrVertex& vertex);
    void DrawLine(const Vec4& p_0, const Vec4& p_1, Vec4& p_color);
    void DrawTriangleWireFrame(Vec4* vertices);

};



