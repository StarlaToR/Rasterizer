
#include <cstdio>
#include <cstring>
#include <cassert>

#include <imgui.h>

#include <maths.hpp>

#include <Renderer.hpp>



Renderer::Renderer(float* p_colorBuffer32Bits, float* p_depthBuffer, const uint p_width, const uint p_height):
/*fb(p_width, p_height),*/viewport(0,0,p_width, p_height)
{
    //fb.colorBuffer = reinterpret_cast<Vec4*>(p_colorBuffer32Bits);
    //fb.depthBuffer = p_depthBuffer;

}

Renderer::Renderer(Framebuffer* f, const uint p_width, const uint p_height):viewport(0,0,p_width, p_height)
{
    fb = f;
}

Renderer::~Renderer()
{

}

void Renderer::SetProjection(Mat4 p_projectionMatrix)
{
    projectionMatrix = p_projectionMatrix;
}

void Renderer::SetView(Mat4 p_viewMatrix)
{
    viewMatrix = p_viewMatrix;
}

void Renderer::SetModel(Mat4 p_modelMatrix)
{
    modelMatrix = p_modelMatrix;
}

void Renderer::SetViewport(const int p_x, const int p_y, const uint p_width, const uint p_height)
{
    // TODO
}

void Renderer::SetTexture(float* p_colors32Bits, const uint p_width, const uint p_height)
{
    // TODO
}

void Renderer::DrawPixel(const float p_x, const float p_y, const float p_z, Vec4& p_color)
{
    if (p_x >= 0 && p_x < fb->GetWidth()
        && p_y >= 0 && p_y < fb->GetHeight()
        && CheckDepth(p_x, p_y, p_z))
    {
        float* colorBuffer = fb->GetColorBuffer();

        colorBuffer[(int)(p_x + p_y * fb->GetWidth()) * 4] = p_color.x; //p_color.x;
        colorBuffer[(int)(p_x + p_y * fb->GetWidth()) * 4 + 1] = p_color.y; //p_color.y;
        colorBuffer[(int)(p_x + p_y * fb->GetWidth()) * 4 + 2] = p_color.z; //p_color.z;
        colorBuffer[(int)(p_x + p_y * fb->GetWidth()) * 4 + 3] = p_color.w; //p_color.w;
    }
}

void Renderer::DrawLine(const Vec4& p0, const Vec4& p1, Vec4& color)
{
    int x0=p0.x, x1=p1.x, y0=p0.y, y1=p1.y, z0 = p0.z, z1 = p1.z;
    int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
    int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
    int dz = abs(z1-z0), sz = z0<z1 ? 1 : -1; 
    int dm = GetMaximumDifference(dx,dy,dz), i = dm; /* maximum difference */
    x1 = y1 = z1 = dm/2; /* error offset */
    
    for(;;) {  /* loop */
        DrawPixel(x0, y0, p0.z, color);
        if (i-- == 0) break;
        x1 -= dx; if (x1 < 0) { x1 += dm; x0 += sx; } 
        y1 -= dy; if (y1 < 0) { y1 += dm; y0 += sy; } 
        z1 -= dz; if (z1 < 0) { z1 += dm; z0 += sz; } 
    }
}



void Renderer::FillTriangle(const Vec4& p0, const Vec4& p1, const Vec4& p2, Vec4& color)
{
    for(int i=0;i<fb->GetWidth();i++)
    {
        for(int j=0;j<fb->GetHeight();j++)
        {
            Vec4 pointChecked = {i,j,0,1};

            float depth;
            if (p0.z == p1.z & p0.z == p2.z)
                depth = p0.z;

            if(pointChecked.IsInTriangle(p0,p1,p2))
                DrawPixel(i,j,depth,color);
        }
    }    
}


void Renderer::FillTriangle(const Vec4& p0, const Vec4& p1, const Vec4& p2)
{   

    for(int i=0;i<fb->GetWidth();i++)
    {
        for(int j=0;j<fb->GetHeight();j++)
        {
            Vec4 pointChecked = {i,j,0,1};
            
    
            float depth=p1.z;
            Vec4 color = pointChecked.GetBarycentricCoords(p0,p1,p2);
            if(pointChecked.IsInTriangle(p0,p1,p2))
                DrawPixel(i, j, depth, color);
        }
    }
}

void Renderer::ApplyViewMatrix(Mat4& matrix)
{
    matrix*=viewMatrix;
}

void Renderer::DrawCube(const float& size, Mat4& transformMat, Vec4& color)
{
    ApplyViewMatrix(transformMat);

/* 
    //Front and back faces
    transformMat *= CreateTransformMatrix({0,0,0},{0,0,size/2},{1,1,1}); 
    DrawQuad(1,transformMat,color);
    transformMat *= CreateTransformMatrix({0,0,0},{0,0,-size/2},{1,1,1}); 
    transformMat *= CreateTransformMatrix({0,0,0},{0,0,-size/2},{1,1,1}); 
    DrawQuad(1,transformMat,color);
    transformMat *= CreateTransformMatrix({0,0,0},{0,0,size/2},{1,1,1}); 


    //Left and right faces
    transformMat *= CreateTransformMatrix({0,M_PI/2,0},{0,0,size/2},{1,1,1}); 
    DrawQuad(1,transformMat,color);
    transformMat *= CreateTransformMatrix({0,0,0},{0,0,-size/2},{1,1,1}); 
    transformMat *= CreateTransformMatrix({0,0,0},{0,0,-size/2},{1,1,1}); 
    DrawQuad(1,transformMat,color);
    transformMat *= CreateTransformMatrix({0,-M_PI/2,0},{0,0,size/2},{1,1,1}); 

    //Up and down faces
    transformMat *= CreateTransformMatrix({M_PI/2,0,0},{0,0,size/2},{1,1,1}); 
    DrawQuad(1,transformMat,color);
    transformMat *= CreateTransformMatrix({0,0,0},{0,0,-size/2},{1,1,1}); 
    transformMat *= CreateTransformMatrix({0,0,0},{0,0,-size/2},{1,1,1}); 
    DrawQuad(1,transformMat,color);
    transformMat *= CreateTransformMatrix({-M_PI/2,0,0},{0,0,size/2},{1,1,1}); 
    */
    transformMat = CreateTransformMatrix({0,0,0},{0,0,-size/2},{1,1,1}); 
    DrawQuad(1,transformMat, color);
    transformMat = CreateTransformMatrix({0,0,0},{0,0.5f,-size},{1,1,1});
    color = {0,0,1,1}; 
    DrawQuad(1,transformMat, color);

}



void Renderer::DrawQuad(const float& size, const Mat4& transformMat, Vec4& color)
{
    rdrVertex vertices[4] = {
        //       pos                  normal                  color              uv
        { -size/2,size/2, 0.0f,      0.0f, 0.0f, 0.0f,      1.0f, 0.0f, 0.0f,     0.0f, 0.0f },
        { size/2,size/2, 0.0f,      0.0f, 0.0f, 0.0f,      0.0f, 1.0f, 0.0f,     0.0f, 0.0f },
        { size/2, -size/2, 0.0f,      0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 1.0f,     0.0f, 0.0f },
        { -size/2, -size/2, 0.0f,      0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 1.0f,     0.0f, 0.0f },
    };

    Vec4 transformedPos[4] = {
        { vertices[0].x,vertices[0].y,vertices[0].z, 1 },
        { vertices[1].x,vertices[1].y,vertices[1].z, 1 },
        { vertices[2].x,vertices[2].y,vertices[2].z, 1 },
        { vertices[3].x,vertices[3].y,vertices[3].z, 1 },
    };

    for (int i = 0; i < 4; i++)
    {
        transformedPos[i]*=transformMat.tab;
    }

    for (int i = 0; i < 4; i++)
    {
        vertices[i].x=transformedPos[i].x;
        vertices[i].y=transformedPos[i].y;
        vertices[i].z=transformedPos[i].z;
    }

    rdrVertex firstHalf[3] = { vertices[0],vertices[2],vertices[1]};
    rdrVertex secondHalf[3] = { vertices[0],vertices[3],vertices[2]};
    
    DrawTriangle(firstHalf,color);
    DrawTriangle(secondHalf,color);
}

void Renderer::DrawSphere(const int lon, const int lat)
{
    float r = 0.5f;

    rdrVertex vertices[4];

    for (int j = 0; j < lat; ++j)
    {
        float theta0 = ((j+0) / (float)lat) * M_PI;
        float theta1 = ((j+1) / (float)lat) * M_PI;

        for (int i = 0; i < lon; ++i)
        {
            float phi0 = ((i+0) / (float)lon) * 2.f * M_PI;
            float phi1 = ((i+1) / (float)lon) * 2.f * M_PI;

            Vec3 c0 = getSphericalCoords(r, theta0, phi0);
            Vec3 c1 = getSphericalCoords(r, theta0, phi1);
            Vec3 c2 = getSphericalCoords(r, theta1, phi1);
            Vec3 c3 = getSphericalCoords(r, theta1, phi0);

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


            DrawTriangle(vertices);

            DrawTriangle(vertices+1);

        }
    }
}

Vec4 Renderer::VertexGraphicPipeline(rdrVertex& vertex)
{
    Vec4 coordinate = {-vertex.x,-vertex.y,-vertex.z,1};

    // Local space to World space
    Mat4 transformMat = modelMatrix*viewMatrix;
    coordinate*=transformMat.tab;

    // World space to Eye space


    // Eye space to Clip space
    // TODO

    // Clip space NDC space
    coordinate.GetHomogenizedVec();

    // NDC space Screen space
    // TODO

    return coordinate;
}

void Renderer::DrawTriangleWireFrame(Vec4* vertices)
{
    Vec4 color2 = {1,1,0,1};

    DrawLine(vertices[0],vertices[1],color2);
    DrawLine(vertices[1],vertices[2],color2);
    DrawLine(vertices[2],vertices[0],color2);
}


void Renderer::DrawTriangle(rdrVertex* vertices, Vec4& color)
{
    Vec4 screenCoords[3]= {
        VertexGraphicPipeline(vertices[0]),
        VertexGraphicPipeline(vertices[1]),
        VertexGraphicPipeline(vertices[2]),
    };

    if(wireFrameOn)
        DrawTriangleWireFrame(screenCoords);

    FillTriangle(screenCoords[0],screenCoords[1],screenCoords[2],color);
}

void Renderer::DrawTriangle(rdrVertex* vertices)
{
    Vec4 screenCoords[3]= {
        VertexGraphicPipeline(vertices[0]),
        VertexGraphicPipeline(vertices[1]),
        VertexGraphicPipeline(vertices[2]),
    };

    if(wireFrameOn)
        DrawTriangleWireFrame(screenCoords);

    FillTriangle(screenCoords[0],screenCoords[1],screenCoords[2]);
}

void Renderer::DrawTriangles(rdrVertex* p_vertices, const uint p_count)
{
    // calculate mvp from matrices
    // Transform vertex list to triangles into colorBuffer
    Vec4 color(1,0,0,1);
    for (int i = 0; i < p_count; i += 3)
    {
        DrawTriangle(&p_vertices[i], color);
    }
}
/*
void rdrSetImGuiContext(rdrImpl* renderer, struct ImGuiContext* context)
{
    ImGui::SetCurrentContext(context);
}*/

void Renderer::ShowImGuiControls()
{
    float tab[] = {lineColor.x, lineColor.y, lineColor.z, lineColor.w};
    ImGui::ColorEdit4("lineColor", tab);
}

void Renderer::Scene1()
{
    std::vector<rdrVertex> vertices = {
        //       pos                  normal                  color              uv
        {  0.5f, -0.5f, 0.0f,      0.0f, 0.0f, 0.0f,      0.0f, 1.0f, 0.0f,     0.0f, 0.0f },
        {  0.f, 0.5f, 0.0f,        0.0f, 0.0f, 0.0f,      1.0f, 0.0f, 0.0f,     0.0f, 0.0f },
        { -0.5f, -0.5f, 0.0f,      0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 1.0f,     0.0f, 0.0f },
    };

    DrawTriangle(&vertices[0]);
}

void Renderer::Scene2()
{
    Mat4 transformMat = GetIdentityMat4();
    Vec4 color = {1,0,0,1};
    DrawCube(1,transformMat,color);
}

bool Renderer::CheckDepth(const float& x, const float& y, const float& z)
{
     
    float depthValue = fb->GetDepthBuffer((int)(y * fb->GetWidth() + x));
    if (depthValue < z)
    {
        fb->SetDepthBuffer((int)(y * fb->GetWidth() + x), z);
        return true;
    }
    else
    {
        return false;
    }
}