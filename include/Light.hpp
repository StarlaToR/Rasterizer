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
    void SetPosition(Vec3 _position);
    void SetPosition(Vec4 _position);
  
private:
    Vec3 position;
    float ambient, diffuse, specular;
};