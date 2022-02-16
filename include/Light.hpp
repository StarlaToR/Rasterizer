#pragma once
#include <maths.hpp>

class Light
{
public:
    Light(Vec3 parPosition, float parAmbient, float parDiffuse, float parSpecular)
    {position=parPosition; ambient=parAmbient; diffuse=parDiffuse; specular=parSpecular;}

    Vec3 GetPosition();
    float GetAmbient();
    float GetDiffuse();
    float GetSpecular();

private:
    Vec3 position;
    float ambient, diffuse, specular;
};