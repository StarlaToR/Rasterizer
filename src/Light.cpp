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

void Light::SetWorldCoords(const Vec3& _position)
{
    worldCoords=_position;
}

void Light::SetScreenCoords(const Vec3& _position)
{
    screenCoords=_position;
}

void Light::SetWorldCoords(const Vec4& _position)
{
    SetWorldCoords({_position.x,_position.y,_position.z});
}

void Light::SetScreenCoords(const Vec4& _position)
{
    SetScreenCoords({_position.x,_position.y,_position.z});
}
