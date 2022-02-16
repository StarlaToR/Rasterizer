#pragma once


#include <Framebuffer.hpp>
#include <Light.hpp>

// Vertex format (only one supported for now)
class rdrVertex
{
private:
    Vec3 position;   // Pos
    Vec3 normal; // Normal
    Vec4 color; // Color
    Vec2 texCoord;       // Texture coordinates

public:
    rdrVertex()
    {
        position = Vec3();
        normal = Vec3();
        color = Vec3();
        texCoord = Vec2();
    }

    rdrVertex(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k)
    {
        position = {a, b, c};
        normal = {d, e, f};
        color = Vec3(g, h, i);
        texCoord = {j, k};
    }

    rdrVertex(Vec3 pos, Vec3 norm, Vec3 col, Vec2 coord)
    {
        position = pos;
        normal = norm;
        color = col;
        texCoord = coord;
    }

    rdrVertex(Vec3 pos, Vec3 norm, Vec4 col, Vec2 coord)
    {
        position = pos;
        normal = norm;
        color = col;
        texCoord = coord;
    }

    Vec3 GetPosition();
    Vec3 GetNormal();
    Vec4 GetColor();
    Vec2 GetTexCoord();
    float GetDepth();
    void SetPosition(Vec3 pos);
    void SetPosition(Vec4 pos);
    void SetNormal(Vec3 norm);
    void SetColor(Vec3 col);
    void SetColor(Vec4 col);
    void SetTexCoord(Vec2 coord);
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
    void TransformVertices(Vec3& vertices);
    void FillTriangle(rdrVertex& p0, rdrVertex& p1, rdrVertex& p2, std::vector<Light> lights);
    bool CheckDepth(int x, int y, float z);
    bool wireFrameOn=true;
    void DrawTriangle(rdrVertex* p_vertices,std::vector<Light> lights);

private:
    
    float GetLightIntensity(rdrVertex& p ,std::vector<Light> lights);
    void ShowImGuiControls();
    Vec4 VertexGraphicPipeline(rdrVertex& vertex);
    void DrawLine(const Vec4& p_0, const Vec4& p_1, Vec4& p_color);
    void DrawTriangleWireFrame(Vec4* vertices);

};



