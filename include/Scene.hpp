#pragma once
#include <vector>
#include <Renderer.hpp>
#include <Light.hpp>

class Scene
{
private:
    double time = 0.0;
    std::vector<rdrVertex> vertices;
    float scale = 1.f;
    int currentScene=1;
    void ShowImGuiControls();

    std::vector<Light> lights;

public:
    Scene();
    ~Scene();
    void Update(float p_deltaTime, Renderer& p_renderer);
    void SetCurrentScene(const int& sceneNumber);

};


