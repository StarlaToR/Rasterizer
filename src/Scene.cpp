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
}

Scene::~Scene()
{
    // HERE: Unload the scene
}

void Scene::Update(float deltaTime, Renderer& renderer)
{
    // HERE: Update (if needed) and display the scene

    // Hard coded matrix
    // TODO: Remove this and use proper functions !


    
    Mat4 modelMatrix =Mat4(
        400,0,0,400,
        0,300,0,300,
        0,0,1,0,
        0,0,0,1
    );
    

    renderer.SetModel(modelMatrix);

    // Draw
    //renderer.DrawTriangles(vertices.data(), (int)vertices.size());
    renderer.DrawCube(5,modelMatrix);

    time += deltaTime;
}

void Scene::ShowImGuiControls()
{
    ImGui::SliderFloat("scale", &scale, 0.f, 10.f);
}
