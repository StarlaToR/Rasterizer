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