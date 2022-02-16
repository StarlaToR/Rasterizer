#include <cstdio>
#include <cstring>
#include <cassert>

#include <imgui.h>
#include <maths.hpp>
#include <Renderer.hpp>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////              rdrVertex                 /////////////////////////////////////////////////////

rdrVertex operator*(const rdrVertex& vertex, const Mat4& transformMat)
{

    rdrVertex newVertex = vertex;
    Vec4 newPosition = vertex.position * transformMat;

    newVertex.position.x=newPosition.x;
    newVertex.position.y=newPosition.y;
    newVertex.position.z=newPosition.z;

    return newVertex;
}



Vec3 rdrVertex::GetPosition()
{
    return position;
}

Vec3 rdrVertex::GetNormal()
{
    return normal;
}

Vec4 rdrVertex::GetColor()
{
    return color;
}

float rdrVertex::GetDepth()
{
    return position.z;
}

Vec2 rdrVertex::GetTexCoord()
{
    return texCoord;
}

void rdrVertex::SetPosition(Vec3 pos)
{
    position = pos;
}

void rdrVertex::SetPosition(Vec4 pos)
{
    position = {pos.x, pos.y, pos.z};
}

void rdrVertex::SetNormal(Vec3 norm)
{
    normal = norm;
}

void rdrVertex::SetColor(Vec3 col)
{
    color = col;
}

void rdrVertex::SetColor(Vec4 col)
{
    color = col;
}

void rdrVertex::SetTexCoord(Vec2 coord)
{
    texCoord = coord;
}

/////////////////////////////////////////////              rdrVertex                 /////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////                 Renderer               /////////////////////////////////////////////////////

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

Mat4 Renderer::GetProjection()
{
    return projectionMatrix;
}

Mat4 Renderer::GetView()
{
    return viewMatrix;
}

Mat4 Renderer::GetModel()
{
    return modelMatrix;
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

float Renderer::GetLightIntensity(rdrVertex& p)
{
    float ambientLight = lights[0].GetAmbient();  
    float intensity = 0;
    Vec3 normal = p.GetNormal();
    Vec3 viewRay = Vec3(viewMatrix.tab[0][3], viewMatrix.tab[0][3], viewMatrix.tab[0][3]) - p.GetPosition();

    for (int i = 0; i < lights.size(); i++)
    {
        if (lights[i].GetAmbient() > ambientLight)
        {
            ambientLight = lights[i].GetAmbient();
        }

        Vec3 lightRay = p.GetPosition() - lights[i].GetPosition();
        Vec3 reflectionRay = 2 * (normal * lightRay) * normal - lightRay;
        

        float diffuseLight = lights[i].GetDiffuse() * GetCrossProduct(lightRay, normal);
        float specularLight = lights[i].GetSpecular() * GetCrossProduct(viewRay, p.GetPosition());

        intensity += diffuseLight + specularLight;
    }
    intensity += ambientLight;
    return intensity;
}

void Renderer::FillTriangle(rdrVertex& p0, rdrVertex& p1, rdrVertex& p2, std::vector<Light> lights)
{   
    std::vector<Vec3> vertices;
    vertices.push_back(p0.GetPosition());
    vertices.push_back(p1.GetPosition());
    vertices.push_back(p2.GetPosition());

    Vec4 maxPoint = GetMaximumXandY(vertices);
    Vec4 minPoint = GetMinimumXandY(vertices);

    for(float i=minPoint.x;i<maxPoint.x;i++)
    {
        for(float j=minPoint.y;j<maxPoint.y;j++)
        {
            Vec4 pointChecked = {i,j,0,1};

            if(pointChecked.IsInTriangle(vertices[0],vertices[1],vertices[2]))
            {
                
                Vec4 w = pointChecked.GetBarycentricCoords(vertices[0],vertices[1],vertices[2]);
                float depth =  w.x * p0.GetDepth() + w.y * p1.GetDepth() + w.z * p2.GetDepth();
                Vec4 color = {
                    w.x * p0.GetColor().x + w.y * p1.GetColor().x + w.z * p2.GetColor().x,
                    w.x * p0.GetColor().y + w.y * p1.GetColor().y + w.z * p2.GetColor().y,
                    w.x * p0.GetColor().z + w.y * p1.GetColor().z + w.z * p2.GetColor().z,
                    w.x * p0.GetColor().w + w.y * p1.GetColor().w + w.z * p2.GetColor().w,
                    };
                DrawPixel(i,j,depth,color);
            }
        }
    }
}

Vec4 Renderer::VertexGraphicPipeline(rdrVertex& vertex)
{
    Vec4 coordinate = {vertex.GetPosition() * -1};

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
        400,0,0,(float)fb->GetWidth()/2,
        0,400,0,(float)fb->GetHeight()/2,
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

    if(wireFrameOn)
        DrawTriangleWireFrame(screenCoords);

    vertices[0].SetNormal(GetNormalVector(vertices[0].GetPosition(),vertices[1].GetPosition(),vertices[2].GetPosition()));
    vertices[1].SetNormal(GetNormalVector(vertices[0].GetPosition(),vertices[1].GetPosition(),vertices[2].GetPosition()));
    vertices[2].SetNormal(GetNormalVector(vertices[0].GetPosition(),vertices[1].GetPosition(),vertices[2].GetPosition()));

    rdrVertex vertex[3] = {
        {{screenCoords[0].x, screenCoords[0].y, screenCoords[0].z}, vertices[0].GetNormal(), vertices[0].GetColor(), vertices[0].GetTexCoord()},
        {{screenCoords[1].x, screenCoords[1].y, screenCoords[1].z}, vertices[1].GetNormal(), vertices[1].GetColor(), vertices[1].GetTexCoord()},
        {{screenCoords[2].x, screenCoords[2].y, screenCoords[2].z}, vertices[2].GetNormal(), vertices[2].GetColor(), vertices[2].GetTexCoord()}
    };

    FillTriangle(vertex[0],vertex[1],vertex[2],lights);
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

void Renderer::DrawTriangles(rdrVertex* p_vertices, const uint p_count)
{
    // calculate mvp from matrices
    // Transform vertex list to triangles into colorBuffer
    for (uint i = 0; i < p_count; i += 3)
    {
        DrawTriangle(&p_vertices[i]);
    }
}



/////////////////////////////////////////////                 Renderer               /////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////