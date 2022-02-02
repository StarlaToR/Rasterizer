#include "maths.hpp"

//Working
float Vec3::GetMagnitude()
{
    return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

//Working kinda.. Magnitude of the vector isnt always 1 but rather between 1.0 and 1.4 not sure about it
void Vec3::Normalize()
{
    x /= GetMagnitude();
    y /= GetMagnitude();
    z /= GetMagnitude();
}

//Working
Vec3 operator+(Vec3& a, Vec3& b)
{
    Vec3 c(
        a.x + b.x,
        a.y + b.y,
        a.z + b.z
    );
    return c;
}

//Working
Vec3 operator*(Vec3& a, float b)
{
    Vec3 c(
        a.x * b,
        a.y * b,
        a.z * b
    );
    return c;
}

//
void Vec4::Homogenize()
{
    if(w!=0)
    {
        x /= w;
        y /= w;
        z /= w;
    }
}

//Working
float Vec4::GetMagnitude()
{
    return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

//Working kinda.. Magnitude of the vector isnt always 1 but rather between 1.0 and 1.4 not sure about it
void Vec4::Normalize()
{
    x /= GetMagnitude();
    y /= GetMagnitude();
    z /= GetMagnitude();
  //  w /= GetMagnitude();
}

//Working
Vec4 operator+(Vec4& a, Vec4& b)
{
    Vec4 c(
        a.x + b.x,
        a.y + b.y,
        a.z + b.z,
        a.w + b.w
    );
    return c;
}

//Working
Vec4 operator*(Vec4& a, float b)
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
    Mat4 c = Mat4();

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                c.tab[i][j] += a.tab[i][k] * b.tab[k][j];
            }
        }
    }

    return c;
}

Mat4& operator*(Mat4& a, float& b)
{
    Mat4 c = Mat4();

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            c.tab[i][j] = a.tab[i][j] + b;
        }
    }

    return c;
}
*/