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
    Vec4 newNormal = vertex.normal * transformMat;

    newVertex.position.x=newPosition.x;
    newVertex.position.y=newPosition.y;
    newVertex.position.z=newPosition.z;

    newVertex.normal.x=newNormal.x;
    newVertex.normal.y=newNormal.y;
    newVertex.normal.z=newNormal.z;

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
viewport(0,0,p_width, p_height)
{
}

void Renderer::ToggleWireFrame()
{
    wireFrameOn = !wireFrameOn;
}

void Renderer::ToggleLights()
{
    lightsOn = !lightsOn;
}

void Renderer::TogglePerspective()
{
    perspectiveOn = !perspectiveOn;
}

void Renderer::ToggleNormals()
{
    normalsOn = !normalsOn;
}

void Renderer::ToggleTextures()
{
    texturesOn = !texturesOn;
}

void Renderer::ToggleLightRay()
{
    lightRayOn = !lightRayOn;
}

Renderer::Renderer(Framebuffer* f, const uint p_width, const uint p_height):viewport(0,0,p_width, p_height)
{
    fb = f;
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

void Renderer::SetLights(const std::vector<Light>& p_lights)
{
    lights = p_lights; 
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

void Renderer::DrawPixel(uint p_x, uint p_y, float p_z, const Vec4& p_color)
{
    if (p_x >= 0 && p_x < (u_int) fb->GetWidth()
        && p_y >= 0 && p_y < (u_int) fb->GetHeight()
        && CheckDepth(p_x, p_y, p_z))
    {
        float* colorBuffer = fb->GetColorBuffer();

        colorBuffer[(int)(p_x + p_y * fb->GetWidth()) * 4] = p_color.x; 
        colorBuffer[(int)(p_x + p_y * fb->GetWidth()) * 4 + 1] = p_color.y; 
        colorBuffer[(int)(p_x + p_y * fb->GetWidth()) * 4 + 2] = p_color.z; 
        colorBuffer[(int)(p_x + p_y * fb->GetWidth()) * 4 + 3] = p_color.w; 
    }
}

void Renderer::DrawLightRay(const Vec3& vertexPos)
{
    Vec4 color={1,1,1,1};
    DrawLine(vertexPos,lights[0].GetScreenCoords(),color);
}

float Renderer::GetLightIntensity(const Vec3& worldPosition, const Vec3& normal, const Vec3& screenCoords)
{
    float ambientLight = lights[0].GetAmbient();  
    float intensity = 0;

    Vec3 viewRay = Vec3(viewMatrix.tab[0][3], viewMatrix.tab[1][3], viewMatrix.tab[2][3]) - worldPosition;
    Vec3 lightRay = lights[0].GetWorldCoords() - worldPosition;
    Vec3 reflectionRay = 2 * (normal * lightRay) * normal - lightRay;

    float dividende = lights[0].GetDiffuse() * abs(GetDotProduct(lightRay, normal));
    float diviseur =(lightRay.GetMagnitude());
    float diffuseLight = dividende/diviseur;


    float specularLight = lights[0].GetSpecular() * GetDotProduct(reflectionRay, viewRay)/(reflectionRay.GetMagnitude() * viewRay.GetMagnitude());

    intensity = ambientLight + diffuseLight + specularLight;
    
    if (lightRayOn)
        DrawLightRay(screenCoords);

    return intensity;
}

void Renderer::FillTriangle(Vec3 screenCoords[3], Vec4 color[3], Vec3 normal, Vec4 worldCoords[3])
{   
    std::vector<Vec3> vertices;
    vertices.push_back(screenCoords[0]);
    vertices.push_back(screenCoords[1]);
    vertices.push_back(screenCoords[2]);

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
                float depth =  w.x * screenCoords[0].z + w.y * screenCoords[1].z + w.z * screenCoords[2].z;

                Vec4 col = {
                    w.x * color[0].x + w.y * color[1].x + w.z * color[2].x,
                    w.x * color[0].y + w.y * color[1].y + w.z * color[2].y,
                    w.x * color[0].z + w.y * color[1].z + w.z * color[2].z,
                    1.0f,
                };
                

                if(lightsOn)
                {
                    normal.Normalize();
                    Vec3 pos = {
                        w.x * worldCoords[0].x + w.y * worldCoords[1].x + w.z * worldCoords[2].x,
                        w.x * worldCoords[0].y + w.y * worldCoords[1].y + w.z * worldCoords[2].y,
                        w.x * worldCoords[0].z + w.y * worldCoords[1].z + w.z * worldCoords[2].z,
                    };
                    float lightIntensity = GetLightIntensity(pos,normal,{screenCoords[0].x,screenCoords[0].y,screenCoords[0].z});
                    col=col*lightIntensity;
                }
                DrawPixel(i,j,depth,col);
            }
        }
    }
}

void Renderer::DrawLine(const Vec4& p0, const Vec4& p1, Vec4& color)
{
    int x0=p0.x, x1=p1.x, y0=p0.y, y1=p1.y, z0 = p0.z, z1 = p1.z;

    int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
    int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
    int dz = abs(z1-z0), sz = z0<z1 ? 1 : -1; 
    int dm = GetMaximumDifference(dx,dy,dz), i = dm; 
    x1 = y1 = z1 = dm/2; 
    
    for(;;) {  
        DrawPixel(x0, y0, z0, color);
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

void Renderer::TransformLights(std::vector<Light>& _lights)
{
    for(int i=0;i<(int)_lights.size();i++)
    {
        Vec4 newPosition = _lights[i].GetWorldCoords();
        _lights[i].SetWorldCoords(newPosition);
        newPosition*=viewMatrix.tab;


        Mat4 screenMatrix = Mat4(
        {
        400,0,0,(float)fb->GetWidth()/2,
        0,400,0,(float)fb->GetHeight()/2,
        0,0,1,0,
        0,0,0,1,
        });
        newPosition *= screenMatrix.tab;
        _lights[i].SetScreenCoords(newPosition);

    }
    
}

void Renderer::UpdateLight()
{
    
    Vec4 worldLight;
    Vec4 viewLight ;
    Vec4 clipLight ;
    Vec4 ndcLight  ;
    Vec4 screenLight  ;
    Vec3 usableScreenLight;

    Mat4 screenMatrix = Mat4(
    {
        400,0,0,(float)fb->GetWidth()/2,
        0,400,0,(float)fb->GetHeight()/2,
        0,0,1,0,
        0,0,0,1,
    });

    worldLight = Vec4(lights[0].GetWorldCoords(), 1.f) * modelMatrix;
        
    viewLight = worldLight * viewMatrix;
        
    if(perspectiveOn)
        clipLight = viewLight * projectionMatrix;
    else
        clipLight = viewLight;


    ndcLight = clipLight.GetHomogenizedVec();
    
    screenLight = ndcLight * screenMatrix;
    screenLight.z = ndcLight.z;


    usableScreenLight={screenLight.x,screenLight.y,screenLight.z};
    DrawLightRay(usableScreenLight);

}

void Renderer::DrawTriangle(rdrVertex* vertices)
{

    Vec4 worldCoords[3];
    Vec4 worldNormals[3];
    
    Vec4 viewCoords[3] ;
    Vec4 viewNormals[3] ;

    Vec4 clipCoords[3] ;
    Vec4 clipNormals[3] ;

    Vec4 ndcCoords[3]  ;
    Vec4 ndcNormals[3]  ;

    Vec4 colors[3];
    
    Vec4 screenCoords[3]  ;
    Vec4 screenNormals[3]  ;

    Vec3 usableScreenCoords[3];
    Vec3 usableScreenNormals[3];

    Mat4 screenMatrix = Mat4(
    {
        400,0,0,(float)fb->GetWidth()/2,
        0,400,0,(float)fb->GetHeight()/2,
        0,0,1,0,
        0,0,0,1,
    });

    for(int i=0;i<3;i++)
    {
        colors[i]=vertices[i].GetColor();
        
        worldCoords[i] = Vec4(vertices[i].GetPosition(), 1.f) * modelMatrix;
        worldNormals[i] = Vec4(vertices[i].GetNormal(), 0.f) * modelMatrix;
        
        viewCoords[i] = worldCoords[i] * viewMatrix;
        viewNormals[i] = worldNormals[i] * viewMatrix;
        
        if(perspectiveOn)
        {
            clipNormals[i] = viewNormals[i] * projectionMatrix ;
            clipCoords[i] = viewCoords[i] * projectionMatrix;
        }
        else
        {
            clipCoords[i] = viewCoords[i];
            clipNormals[i] = viewNormals[i] ;
        }


        ndcCoords[i] = clipCoords[i].GetHomogenizedVec();
        
        screenCoords[i] = ndcCoords[i] * screenMatrix;
        screenCoords[i].z = ndcCoords[i].z;

        screenNormals[i] = clipNormals[i] * screenMatrix;
        screenNormals[i].z = clipNormals[i].z;

        usableScreenCoords[i]={screenCoords[i].x,screenCoords[i].y,screenCoords[i].z};
        usableScreenNormals[i]={screenNormals[i].x,screenNormals[i].y,screenNormals[i].z};

    }

    Vec3 screenTest[3] = {usableScreenCoords[2],usableScreenCoords[1],usableScreenCoords[0]};
    Vec4 worldTest[3] = {worldCoords[2],worldCoords[1],worldCoords[0]};

    if(wireFrameOn)
    {
        DrawTriangleWireFrame(screenCoords);
    }
    else
    {   
        if(blacksmithPatch)    
            FillTriangle(screenTest,colors,{viewNormals[0].x,viewNormals[0].y,viewNormals[0].z},worldTest);
        else
            FillTriangle(usableScreenCoords,colors,{viewNormals[0].x,viewNormals[0].y,viewNormals[0].z},worldCoords);

        Vec4 color= {1,1,1,1};
        if(normalsOn)
        {
            for(int i=0;i<3;i++)
                DrawLine(screenCoords[i],screenCoords[i] + screenNormals[i],color);
        }
    }
}

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
    for (uint i = 0; i < p_count; i += 3)
    {
        DrawTriangle(&p_vertices[i]);
    }
}

void Renderer::DrawGizmo()
{
    Vec4 worldCoords[4] = {
        {0,0,0,1}, {0.5f,0,0,1},
        {0,0.5f,0,1}, {0,0,0.5f,1},
    };
    Vec4 viewCoords[4]  ;
    Vec4 clipCoords[4]  ;
    Vec4 ndcCoords[4]   ;
    Vec4 screenCoords[4];

    Mat4 screenMatrix = Mat4(
    {
        400,0,0,(float)fb->GetWidth()/2,
        0,400,0,(float)fb->GetHeight()/2,
        0,0,1,0,
        0,0,0,1,
    });

    for(int i=0;i<4;i++)
    {   
        viewCoords[i] = worldCoords[i] * viewMatrix;

        if(perspectiveOn)
        {
            clipCoords[i] = viewCoords[i] * projectionMatrix;
        }
        else
        {
            clipCoords[i] = viewCoords[i];
        }

        ndcCoords[i] = clipCoords[i].GetHomogenizedVec();
        
        screenCoords[i] = ndcCoords[i] * screenMatrix;
        screenCoords[i].z = ndcCoords[i].z;
    }
    Vec4 col1 = {1,0,0,1};
    Vec4 col2 = {0,1,0,1};
    Vec4 col3 = {0,0,1,1};

    DrawLine(screenCoords[0], screenCoords[1], col1);
    DrawLine(screenCoords[0], screenCoords[2], col2);
    DrawLine(screenCoords[0], screenCoords[3], col3);
}


/////////////////////////////////////////////                 Renderer               /////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////