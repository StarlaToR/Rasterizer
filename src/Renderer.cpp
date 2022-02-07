
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

void Renderer::SetProjection(float* p_projectionMatrix)
{
    // TODO
}

void Renderer::SetView(float* p_viewMatrix)
{
    // TODO
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

void Renderer::DrawPixel(uint p_x, uint p_y, Vec4 p_color)
{
    float* colorBuffer = fb->GetColorBuffer();

    colorBuffer[p_x + p_y * fb->GetWidth() * 4] = p_color.x;
    colorBuffer[p_x + p_y * fb->GetWidth() * 4 + 1] = p_color.y;
    colorBuffer[p_x + p_y * fb->GetWidth() * 4 + 2] = p_color.z;
    colorBuffer[p_x + p_y * fb->GetWidth() * 4 + 3] = p_color.w;
}

void Renderer::DrawLine(const Vec3& p0, const Vec3& p1, const Vec4& color)
{

    int x0=p0.x, x1=p1.x, y0=p0.y, y1=p1.y;
    int dx =  abs(x1-x0), sx = x0<x1 ? 1 : -1;
    int dy = -abs(y1-y0), sy = y0<y1 ? 1 : -1; 
    int err = dx+dy, e2; 

    for(;;){  
        DrawPixel(x0,y0,color);
        if (x0==x1 && y0==y1) break;
        e2 = 2*err;
        if (e2 >= dy) { err += dy; x0 += sx; } 
        if (e2 <= dx) { err += dx; y0 += sy; } 
    }
}

Vec3 ndcToScreenCoords(Vec3 ndc, const Viewport& viewport)
{
    // TODO
    return ndc;
}

void Renderer::FillTriangle(const Vec3& p0, const Vec3& p1, const Vec3& p2)
{

}

void Renderer::DrawTriangle(rdrVertex* vertices)
{

    // Store triangle vertices positions
    Vec3 localCoords[3] = { 

        { vertices[0].x, vertices[0].y, vertices[0].z },
        { vertices[1].x, vertices[1].y, vertices[1].z },
        { vertices[2].x, vertices[2].y, vertices[2].z },
    };

    Vec4 worldCoords[3] = { 
        { localCoords[0].x, localCoords[0].y, localCoords[0].z, 1},
        { localCoords[1].x, localCoords[1].y, localCoords[1].z, 1},
        { localCoords[2].x, localCoords[2].y, localCoords[2].z, 1},
    };

/*
    for(int i=0;i<3;i++)
        worldCoords[i] *= modelMatrix;
*/


    // Local space (v3) -> Clip space (v4)
    // TODO
    Vec4 clipCoords[3] = {
        { worldCoords[0] },
        { worldCoords[1] },
        { worldCoords[2] },
    };


    // Clip space (v4) to NDC (v3)
    // TODO
    Vec3 ndcCoords[3] = {
        clipCoords[0].GetHomogenizedVec(),
        clipCoords[1].GetHomogenizedVec(),
        clipCoords[2].GetHomogenizedVec(),
    };
    

    // NDC (v3) to screen coords (v2)
    // TODO
    Vec3 screenCoords[3] = {
        { ndcToScreenCoords(ndcCoords[0], viewport) },
        { ndcToScreenCoords(ndcCoords[1], viewport) },
        { ndcToScreenCoords(ndcCoords[2], viewport) },
    };

    // Draw triangle wireframe
    DrawLine(screenCoords[0], screenCoords[1], lineColor);
    DrawLine(screenCoords[1], screenCoords[2], lineColor);
    DrawLine(screenCoords[2], screenCoords[0], lineColor);

}

void Renderer::DrawTriangles(rdrVertex* p_vertices, const uint p_count)
{
    // calculate mvp from matrices
    // Transform vertex list to triangles into colorBuffer
    for (int i = 0; i < p_count; i += 3)
    {
        DrawTriangle(&p_vertices[i]);
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
