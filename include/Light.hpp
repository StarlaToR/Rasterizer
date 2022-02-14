#include <maths.hpp>

class Light
{
public:
    Light(Vec4 parPosition, float parAmbient, float parDiffuse, float parSpecular)
    {position=parPosition; ambient=parAmbient; diffuse=parDiffuse; specular=parSpecular;}

private:
    Vec4 position;
    float ambient, diffuse, specular;
};