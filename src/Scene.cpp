#include <imgui.h>
#include <maths.hpp>
#include <Scene.hpp>


Scene::Scene()
{
    // HERE: Load the scene
    // Setup some vertices to test

    lights.push_back(Light({0,0,0,0},0.2f,0.4f,0.4f));
}

Scene::~Scene()
{
    // HERE: Unload the scene
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////            Draw functions              /////////////////////////////////////////////////////


void Scene::DrawSphere(const int lon, const int lat, const float& radius, const Mat4& transformMat, Renderer& renderer)
{
    rdrVertex vertices[4];

    for (int j = 0; j < lat; ++j)
    {
        float theta0 = ((j+0) / (float)lat) * M_PI;
        float theta1 = ((j+1) / (float)lat) * M_PI;

        for (int i = 0; i < lon; ++i)
        {
            float phi0 = ((i+0) / (float)lon) * 2.f * M_PI;
            float phi1 = ((i+1) / (float)lon) * 2.f * M_PI;

            Vec4 c0 = getSphericalCoords(radius, theta0, phi0);
            Vec4 c1 = getSphericalCoords(radius, theta0, phi1);
            Vec4 c2 = getSphericalCoords(radius, theta1, phi1);
            Vec4 c3 = getSphericalCoords(radius, theta1, phi0);

            c0 *= transformMat.tab;
            c1 *= transformMat.tab;
            c2 *= transformMat.tab;
            c3 *= transformMat.tab;

            vertices[0].x = c0.x;
            vertices[0].y = c0.y;
            vertices[0].z = c0.z;

            vertices[1].x = c1.x;
            vertices[1].y = c1.y;
            vertices[1].z = c1.z;

            vertices[2].x = c2.x;
            vertices[2].y = c2.y;
            vertices[2].z = c2.z;

            vertices[3].x = c3.x;
            vertices[3].y = c3.y;
            vertices[3].z = c3.z;

            DrawQuad(vertices,renderer);

        }
    }
}

void Scene::DrawSquare(const float& size, const Mat4& transformMat ,Renderer& renderer)
{

    renderer.SetModel(renderer.GetModel()*transformMat);

   //Back face
    vertices = {
        { -size/2, size/2, 0.f,      0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 1.0f,     0.0f, 0.0f },
        { size/2, size/2, 0.f,      0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 1.0f,     0.0f, 0.0f },
        { size/2,-size/2, 0.f,      0.0f, 0.0f, 0.0f,      1.0f, 0.0f, 0.0f,     0.0f, 0.0f },
        { -size/2,-size/2, 0.f,      0.0f, 0.0f, 0.0f,      0.0f, 1.0f, 0.0f,     0.0f, 0.0f },
    };
    DrawQuad(vertices.data(),renderer);
}


void Scene::DrawCube(const float& size, const Mat4& transformMat, Renderer& renderer)
{

    //ATTENTION : NO UPPER AND LOWER FACE

    Mat4 center = renderer.GetModel()*transformMat;

    renderer.SetModel(center);

    renderer.SetModel(renderer.GetModel()*CreateTransformMatrix({0,0,0},{0,0,-size/2},{1,1,1}));
    DrawSquare(size,GetIdentityMat4(),renderer);

    renderer.SetModel(center);
    
    renderer.SetModel(renderer.GetModel()*CreateTransformMatrix({0,M_PI,0},{0,0,size/2},{1,1,1}));
    DrawSquare(size,GetIdentityMat4(),renderer);

    renderer.SetModel(center);
    
    renderer.SetModel(renderer.GetModel()*CreateTransformMatrix({0,M_PI/2,0},{-size/2,0,0},{1,1,1}));
    DrawSquare(size,GetIdentityMat4(),renderer);
 
    renderer.SetModel(center);
    
    renderer.SetModel(renderer.GetModel()*CreateTransformMatrix({0,-M_PI/2,0},{size/2,0,0},{1,1,1}));
    DrawSquare(size,GetIdentityMat4(),renderer);
 
}

void Scene::DrawQuad(rdrVertex* vertices, Renderer& renderer)
{
    std::vector<rdrVertex> triangleVertices;
    
    triangleVertices.push_back(vertices[2]);
    triangleVertices.push_back(vertices[1]);
    triangleVertices.push_back(vertices[0]);

    triangleVertices.push_back(vertices[3]);
    triangleVertices.push_back(vertices[2]);
    triangleVertices.push_back(vertices[0]);

    DrawTriangles(triangleVertices.data(),triangleVertices.size(),renderer);
}

void Scene::DrawTriangles(rdrVertex* p_vertices, const uint p_count, Renderer& renderer)
{
    // calculate mvp from matrices
    // Transform vertex list to triangles into colorBuffer
    for (uint i = 0; i < p_count; i += 3)
    {
        renderer.DrawTriangle(&p_vertices[i]);
    }
}


/////////////////////////////////////////////            Draw functions              /////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////














//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////            Scene functions             /////////////////////////////////////////////////////

void Scene::Scene1(Renderer& renderer)
{
    vertices = {
        //       pos                  normal                  color              uv
        {-0.5f,-0.5f, 0.0f,      0.0f, 0.0f, 0.0f,      1.0f, 0.0f, 0.0f,     0.0f, 0.0f },
        { 0.5f,-0.5f, 0.0f,      0.0f, 0.0f, 0.0f,      0.0f, 1.0f, 0.0f,     0.0f, 0.0f },
        { 0.0f, 0.5f, 0.0f,      0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 1.0f,     0.0f, 0.0f },
    };

    renderer.SetView(CreateTransformMatrix({0,0,0},{0,0,0}, {1,1,1}));
    //renderer.SetModel(CreateTransformMatrix({0,(float)time,0},{0.2,0,1}, {1,1,1}));
    DrawTriangles(vertices.data(), vertices.size(),renderer);
    renderer.SetModel(CreateTransformMatrix({0,0,0},{0,0,1}, {1,1,1}));
    DrawTriangles(vertices.data(), vertices.size(),renderer);
}

void Scene::Scene2(Renderer& renderer)
{

    vertices = {
        //       pos                  normal                  color              uv
        { -0.5f, 0.5f, 0.0f,      0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 1.0f,     0.0f, 0.0f },
        { 0.5f, 0.5f, 0.0f,      0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 1.0f,     0.0f, 0.0f },
        {0.5f,-0.5f, 0.0f,      0.0f, 0.0f, 0.0f,      1.0f, 0.0f, 0.0f,     0.0f, 0.0f },
        { -0.5f,-0.5f, 0.0f,      0.0f, 0.0f, 0.0f,      0.0f, 1.0f, 0.0f,     0.0f, 0.0f },
    };

    renderer.SetView(CreateTransformMatrix({0,0,0},{0,0,0}, {1,1,1}));
    renderer.SetModel(CreateTransformMatrix({0,0,0},{0,0,0}, {1,1,1}));

 //   DrawQuad(vertices.data(),renderer);

//    DrawSquare(0.5f,CreateTransformMatrix({0,0,0},{0,0,0},{1,1,1}),renderer);
    DrawCube(0.5f,CreateTransformMatrix({0,time,0},{0,0,0},{1,1,1}),renderer);
}

/////////////////////////////////////////////            Scene functions             /////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////














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

    // Draw
    if(currentScene==1)
        Scene1(renderer);
    else if(currentScene==2)
        Scene2(renderer);

    time += deltaTime;
}

void Scene::ShowImGuiControls()
{
    ImGui::SliderFloat("scale", &scale, 0.f, 10.f);
}
