#pragma once


#include <Framebuffer.hpp>
#include <Light.hpp>
#include <stb_image.hpp>

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

    rdrVertex(double a, double b, double c, double d, double e, double f, double g, double h, double i, double j, double k, double l)
    {
        position = {(float)a, (float)b, (float)c};
        normal = {(float)d, (float)e, (float)f};
        color = {(float)g, (float)h, (float)i, (float)j};
        texCoord = {(float)k,(float)l};
    }

    rdrVertex(const Vec3& pos, const Vec3& norm, const Vec3& col, const Vec2& coord)
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

    friend rdrVertex operator*(const rdrVertex& vertex, const Mat4& transformMat);

};

rdrVertex operator*(const rdrVertex& vertex, const Mat4& transformMat);


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


    std::vector<Light> lights;

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
    void SetLights(const std::vector<Light>& p_lights);
    Mat4 GetProjection();
    Mat4 GetView();
    Mat4 GetModel();
    void SetViewport(const int p_x, const int p_y, const uint p_width, const uint p_height);
    void SetTexture(float* p_colors32Bits, const uint p_width, const uint p_height);
    void DrawTriangles(rdrVertex* p_vertices, const uint p_count);
    void DrawGizmo();
    void TransformLights(std::vector<Light>& _lights);
    void UpdateLight();

    void ToggleWireFrame();
    void ToggleLights();
    void TogglePerspective();
    void ToggleNormals();
    void ToggleTextures();
    void ToggleLightRay();

    bool wireFrameOn=false;
    bool lightsOn = false;
    bool perspectiveOn = false;
    bool normalsOn = false;
    bool texturesOn = false;
    bool lightRayOn = false;

private:

    void DrawLightRay(const Vec3& vertexPos);
    void DrawPixel(uint p_x, uint p_y, float p_z, const Vec4& p_color);
    void TransformVertices(Vec3& vertices);
    void FillTriangle(Vec3 screenCoords[3], Vec4 color[3], Vec3 normal, Vec4 worldCoords[3]);
    bool CheckDepth(int x, int y, float z);
    void DrawTriangle(rdrVertex* p_vertices);

    float GetLightIntensity(const Vec3& worldPosition, const Vec3& normal, const Vec3& screenCoords);
    void ShowImGuiControls();
    void DrawLine(const Vec4& p_0, const Vec4& p_1, Vec4& p_color);
    void DrawTriangleWireFrame(Vec4* vertices);

};



