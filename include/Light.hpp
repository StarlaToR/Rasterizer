#pragma once
#include <maths.hpp>

class Light
{
public:
    Light(Vec3 parPosition, float parAmbient, float parDiffuse, float parSpecular)
    {worldCoords=parPosition; ambient=parAmbient; diffuse=parDiffuse; specular=parSpecular;}

    Vec3 GetScreenCoords();
    Vec3 GetWorldCoords();
    float GetAmbient();
    float GetDiffuse();
    float GetSpecular();
    void SetWorldCoords(Vec3 _position);
    void SetScreenCoords(Vec3 _position);
    void SetWorldCoords(Vec4 _position);
    void SetScreenCoords(Vec4 _position);

private:
    Vec3 worldCoords;
    Vec3 screenCoords;

    float ambient, diffuse, specular;
};