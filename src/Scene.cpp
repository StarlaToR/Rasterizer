#include <imgui.h>
#include <maths.hpp>
#include <Scene.hpp>

static std::vector<rdrVertex> GetCubeFace()
{
   //Back face
    return {
        { -0.5f, 0.5f, 0.5f,      0.0f, 0.0f, 0.0f,      1.0f, 0.0f, 1.0f,     0.0f, 0.0f },
        {  0.5f, 0.5f, 0.5f,      0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 1.0f,     0.0f, 0.0f },
        {  0.5f,-0.5f, 0.5f,      0.0f, 0.0f, 0.0f,      0.0f, 1.0f, 1.0f,     0.0f, 0.0f },
        { -0.5f,-0.5f, 0.5f,      0.0f, 0.0f, 0.0f,      1.0f, 1.0f, 0.0f,     0.0f, 0.0f },
    };
}

static void TransformVertices(std::vector<rdrVertex>& dest, const std::vector<rdrVertex>& vert, const Mat4& transform)
{
    // multiply all verts by transform and return them
    for(int i=0; i< (int) vert.size(); i++)
    {
        dest.push_back(vert[i]*transform);
    }
}

static std::vector<rdrVertex> GetCubeVertices()
{
    std::vector<rdrVertex> square = GetCubeFace();

    std::vector<rdrVertex> cube;
    TransformVertices(cube, square, CreateTransformMatrix( {0, 0, 0}, { 0,      0,      0}, {1, 1, 1 }));
    TransformVertices(cube, square, CreateTransformMatrix( {0, 0, 0}, { 0,      M_PI,   0}, {1, 1, 1 }));
    TransformVertices(cube, square, CreateTransformMatrix( {0, 0, 0}, { 0,      M_PI/2, 0}, {1, 1, 1 }));
    TransformVertices(cube, square, CreateTransformMatrix( {0, 0, 0}, { 0,     -M_PI/2, 0}, {1, 1, 1 }));
    TransformVertices(cube, square, CreateTransformMatrix( {0, 0, 0}, { M_PI/2, 0,      0}, {1, 1, 1 })); 
    TransformVertices(cube, square, CreateTransformMatrix( {0, 0, 0}, {-M_PI/2, 0,      0}, {1, 1, 1 }));

    printf("\nsize = %d\n",(int)cube.size());

    return cube;
}

Scene::Scene()
{
    // HERE: Load the scene
    // Setup some vertices to test

    lights.push_back(Light({0,0,0},0.2f,0.4f,0.4f));

    cubeVertices = GetCubeVertices();
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

            vertices[0].SetPosition({c0.x,c0.y,c0.z});
            vertices[1].SetPosition({c1.x,c1.y,c1.z});
            vertices[2].SetPosition({c2.x,c2.y,c2.z});
            vertices[3].SetPosition({c3.x,c3.y,c3.z});

            vertices[0].SetColor({0.5f,0,0,1});
            vertices[1].SetColor({1.0f,0.2f,0,1});
            vertices[2].SetColor({1.0f,0,1.0f,1});
            vertices[3].SetColor({0,0,0,1});

            DrawQuad(vertices,renderer);

        }
    }
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

    renderer.DrawTriangles(triangleVertices.data(),triangleVertices.size());
}


/////////////////////////////////////////////            Draw functions              /////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////














//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////            Scene functions             /////////////////////////////////////////////////////

void Scene::Scene1(Renderer& renderer)
{
    renderer.SetLights(lights);

    vertices = {
        //       pos                  normal                  color              uv
        {-0.5f,-0.5f, 0.0f,      0.0f, 0.0f, 0.0f,      1.0f, 0.0f, 0.0f,     0.0f, 0.0f },
        { 0.5f,-0.5f, 0.0f,      0.0f, 0.0f, 0.0f,      0.0f, 1.0f, 0.0f,     0.0f, 0.0f },
        { 0.0f, 0.5f, 0.0f,      0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 1.0f,     0.0f, 0.0f },
    };

    //renderer.SetModel(CreateTransformMatrix({0,(float)time,0},{0.2,0,1}, {1,1,1}));
   // DrawTriangles(vertices.data(), vertices.size(),renderer);
    renderer.SetModel(CreateTransformMatrix({0,0,1},{0,0,0}, {1,1,1}));
    renderer.DrawTriangles(vertices.data(), vertices.size());
}

void Scene::Scene2(Renderer& renderer)
{

    renderer.SetLights(lights);

    renderer.SetModel(CreateTransformMatrix({0.5f,0,0}, {(float)time,(float)time/2,0}, {1,1,1}));
    renderer.DrawTriangles(cubeVertices.data(), cubeVertices.size());

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
