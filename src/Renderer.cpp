
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

void Renderer::DrawPixel(uint p_x, uint p_y, float p_z, const Vec4& p_color)
{
    if (p_x >= 0 && p_x < (u_int) fb->GetWidth()
        && p_y >= 0 && p_y < (u_int) fb->GetHeight()
        && CheckDepth(p_x, p_y, p_z))
    {
        float* colorBuffer = fb->GetColorBuffer();

        colorBuffer[(int)(p_x + p_y * fb->GetWidth()) * 4] = p_color.x; //p_color.x;
        colorBuffer[(int)(p_x + p_y * fb->GetWidth()) * 4 + 1] = p_color.y; //p_color.y;
        colorBuffer[(int)(p_x + p_y * fb->GetWidth()) * 4 + 2] = p_color.z; //p_color.z;
        colorBuffer[(int)(p_x + p_y * fb->GetWidth()) * 4 + 3] = p_color.w; //p_color.w;
    }
}


void Renderer::FillTriangle(const Vec4& p0, const Vec4& p1, const Vec4& p2)
{   
    std::vector<Vec4> vertices;
    vertices.push_back(p0);
    vertices.push_back(p1);
    vertices.push_back(p2);

    Vec4 maxPoint = GetMaximumXandY(vertices);
    Vec4 minPoint = GetMinimumXandY(vertices);

    for(float i=minPoint.x;i<maxPoint.x;i++)
    {
        for(float j=minPoint.y;j<maxPoint.y;j++)
        {
            Vec4 pointChecked = {i,j,0,1};

            Vec4 w = pointChecked.GetBarycentricCoords(p0,p1,p2);

            float depth =  w.x * p0.z + w.y * p1.z + w.z * p1.z;

            if(pointChecked.IsInTriangle(p0,p1,p2))
                DrawPixel(i,j,depth,w);
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
    Mat4 mat = Mat4(
        {
        400,0,0,fb->GetWidth()/2,
        0,400,0,fb->GetHeight()/2,
        0,0,1,0,
        0,0,0,1,
        }
    );
    coordinate *= mat.tab;

    return coordinate;
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
        DrawPixel(x0, y0, -1000, color);
        if (i-- == 0) break;
        x1 -= dx; if (x1 < 0) { x1 += dm; x0 += sx; } 
        y1 -= dy; if (y1 < 0) { y1 += dm; y0 += sy; } 
        z1 -= dz; if (z1 < 0) { z1 += dm; z0 += sz; } 
    }
}

void Renderer::DrawTriangleWireFrame(Vec4* vertices)
{
    Vec4 color2 = {1,1,0,1};

    DrawLine(vertices[0],vertices[1],color2);
    DrawLine(vertices[1],vertices[2],color2);
    DrawLine(vertices[2],vertices[0],color2);
}


void Renderer::DrawTriangle(rdrVertex* vertices)
{
    Vec4 screenCoords[3]= {
        VertexGraphicPipeline(vertices[0]),
        VertexGraphicPipeline(vertices[1]),
        VertexGraphicPipeline(vertices[2]),
    };
   // GetNormalVector(screenCoords[0],screenCoords[1],screenCoords[2]);

    if(wireFrameOn)
        DrawTriangleWireFrame(screenCoords);

    FillTriangle(screenCoords[0],screenCoords[1],screenCoords[2]);
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


bool Renderer::CheckDepth(int x, int y, float z)
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