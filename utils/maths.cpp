#include "maths.hpp"

float Vec3::GetMagnitude()
{
    return sqrt(pow(x, 2) + pow(y, 2) + pow(y, 2));
}

void Vec3::Normalize()
{
    x /= GetMagnitude();
    y /= GetMagnitude();
    z /= GetMagnitude();
}

Vec3& operator+(Vec3& a, Vec3& b)
{
    Vec3 c(
        a.x + b.x,
        a.y + b.y,
        a.z + b.z
    );
    return c;
}

Vec3& operator*(Vec3& a, float& b)
{
    Vec3 c(
        a.x * b,
        a.y * b,
        a.z * b
    );
    return c;
}

void Vec4::Homogenize()
{
    if(w!=0)
    {
        x /= w;
        y /= w;
        z /= w;
    }
}

float Vec4::GetMagnitude()
{
    return sqrt(pow(x, 2) + pow(y, 2) + pow(y, 2));
}

void Vec4::Normalize()
{
    x /= GetMagnitude();
    y /= GetMagnitude();
    z /= GetMagnitude();
}

Vec4& operator+(Vec4& a, Vec4& b)
{
    Vec4 c(
        a.x + b.x,
        a.y + b.y,
        a.z + b.z,
        a.w + b.w
    );
    return c;
}

Vec4& operator*(Vec4& a, float& b)
{
    Vec4 c(
        a.x * b,
        a.y * b,
        a.z * b,
        a.w * b
    );
    return c;
}
/*
static Mat4 Mat4::CreateTransformMatrix(const Vec3& rotation, const Vec3& position, const Vec3& scale)
{
    Mat4 transformMat;

    Mat4 translation = CreateTranslationMatrix(position);
    Mat4 scale = CreateScaleMatrix(scale);
    rotation;



    return transformMat;

}

static Mat4 CreateTranslationMatrix(const Vec3& translation)
{

}
static Mat4 CreateScaleMatrix(const Vec3& scale)
{

}

static Mat4 CreateXRotationMatrix(float angle)
{

}

static Mat4 CreateYRotationMatrix(float angle)
{

}

static Mat4 CreateZRotationMatrix(float angle)
{

}

Mat4& operator*(Mat4& a, Mat4& b)
{
    Vec4 c1(
        a.tab[0][0] * b.tab[0][0] + a.tab[0][1] * b.tab[1][0] + a.tab[0][2] * b.tab[2][0] + a.tab[0][3] * b.tab[3][0],
    );

    Mat4 c();

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                
            }
        }
    }
}

Mat4& operator*(Mat4& a, float& b)
{

}
*/