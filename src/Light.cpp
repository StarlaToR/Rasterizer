#include<Light.hpp>


Vec3 Light::GetWorldCoords()
{
    return worldCoords;
}

Vec3 Light::GetScreenCoords()
{
    return screenCoords;
}

float Light::GetAmbient()
{
    return ambient;
}

float Light::GetDiffuse()
{
    return diffuse;
}

float Light::GetSpecular()
{
    return specular;
}

void Light::SetPosition(Vec3 _position)
{
    worldCoords=_position;
}

void Light::SetPosition(Vec4 _position)
{
    SetPosition({_position.x,_position.y,_position.z});
}