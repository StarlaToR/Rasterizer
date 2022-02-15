#pragma once
#include <vector>
#include <Renderer.hpp>
#include <Light.hpp>

class Scene
{
public:
    Scene();
    ~Scene();
    void Update(float p_deltaTime, Renderer& p_renderer);
    void SetCurrentScene(const int& sceneNumber);


private:
    double time = 0.0;

    std::vector<rdrVertex> vertices;
    std::vector<Light> lights;

    float scale = 1.f;
    int currentScene=1;
    void ShowImGuiControls();
    
    // Scene functions
    void Scene1(Renderer& renderer);
    void Scene2(Renderer& renderer);


    // Draw functions
    void DrawTriangles(rdrVertex* p_vertices, const uint p_count, Renderer& renderer);
    void DrawSphere(const int lon, const int lat, const float& radius, const Mat4& transformMat, Renderer& renderer);
    void DrawSquare(const float& size, const Mat4& transformMat ,Renderer& renderer);
    void DrawQuad(rdrVertex* vertices, Renderer& renderer);
    void DrawCube(const float& size,Renderer& renderer);



};


