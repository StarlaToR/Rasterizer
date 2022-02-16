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

    std::vector<rdrVertex> triangleVertices;
    std::vector<rdrVertex> sphereVertices;
    std::vector<rdrVertex> cubeVertices;
    std::vector<Light> lights;

    float scale = 1.f;
    int currentScene=1;
    void ShowImGuiControls();
    
    // Scene functions
    void Scene1(Renderer& renderer);
    void Scene2(Renderer& renderer);
};


