#include<Light.hpp>


Vec3 Light::GetPosition()
{
    return position;
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
    position=_position;
}

void Light::SetPosition(Vec4 _position)
{
    SetPosition({_position.x,_position.y,_position.z});
}