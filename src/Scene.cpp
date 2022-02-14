#include <imgui.h>
#include <maths.hpp>
#include <Scene.hpp>


Scene::Scene()
{
    // HERE: Load the scene
    // Setup some vertices to test
    vertices = {
        //       pos                  normal                  color              uv
        {-0.5f,-0.5f, 0.0f,      0.0f, 0.0f, 0.0f,      1.0f, 0.0f, 0.0f,     0.0f, 0.0f },
        { 0.5f,-0.5f, 0.0f,      0.0f, 0.0f, 0.0f,      0.0f, 1.0f, 0.0f,     0.0f, 0.0f },
        { 0.5f, 0.5f, 0.0f,      0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 1.0f,     0.0f, 0.0f },
    };

    lights.push_back(Light({0,0,0,0},0.2f,0.4f,0.4f));
}

Scene::~Scene()
{
    // HERE: Unload the scene
}

void Scene::SetCurrentScene(const int& sceneNumber)
{
    currentScene=sceneNumber;
}

void Scene::Update(float deltaTime, Renderer& renderer)
{
    // HERE: Update (if needed) and display the scene

    // Hard coded matrix
    // TODO: Remove this and use proper functions !

    //Mat4 modelMatrix = CreateTransformMatrix({0,0,0},{0,0,0}, {1,1,1});
    renderer.SetView(CreateTransformMatrix({0,0,0},{0,0.2,0.2}, {1,1,1}));

    renderer.SetModel(CreateTransformMatrix({0,sin(time),0},{0.2,0,1}, {1,1,1}));
    renderer.DrawTriangles(vertices.data(), vertices.size());
    renderer.SetModel(CreateTransformMatrix({0,0,0},{0,0,1}, {1,1,1}));
    renderer.DrawTriangles(vertices.data(), vertices.size());

/*
    // Draw
    if(currentScene==1)
        renderer.Scene1();
    else if(currentScene==2)
        renderer.Scene2();
*/
    time += deltaTime;
}

void Scene::ShowImGuiControls()
{
    ImGui::SliderFloat("scale", &scale, 0.f, 10.f);
}
