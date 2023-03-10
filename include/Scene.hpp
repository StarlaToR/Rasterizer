#pragma once
#include <vector>
#include <Renderer.hpp>
#include <Light.hpp>
#include <Mesh.hpp>
#include <Data_TheNobleCraftsman.hpp>

class Scene
{
public:
    Scene();
    ~Scene();
    void Update(float p_deltaTime, Renderer& p_renderer);
    void SetCurrentScene(const int& sceneNumber, Renderer& renderer);


private:
    double time = 0.0;

    std::vector<rdrVertex> triangleVertices;
    std::vector<rdrVertex> sphereVertices;
    std::vector<rdrVertex> cubeVertices;
    std::vector<Light> lights;
    Mesh cubeMesh;

    float scale = 1.f;
    int currentScene=3;
    void ShowImGuiControls();
    
    // Scene functions
    void Scene1(Renderer& renderer);
    void Scene2(Renderer& renderer);
    void Scene3(Renderer& renderer);
    void Scene4(Renderer& renderer);
    void Scene5(Renderer& renderer);
};


