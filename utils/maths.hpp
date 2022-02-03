#pragma once
#include <cmath>
#include <stdio.h>

class Vec3
{
public:
    float x;
    float y;
    float z;

    Vec3(float a, float b, float c)
    {
        x = a;
        y = b;
        z = c;
    }

    Vec3()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    float GetMagnitude();
    void Normalize();

    friend Vec3 operator+(Vec3& a, Vec3& b);
    friend Vec3 operator*(Vec3& a, float& b);
};

Vec3 operator+(Vec3& a, Vec3& b);
Vec3 operator*(Vec3& a, float b);

class Vec4
{
public:
    float x;
    float y;
    float z;
    float w;

    Vec4(const Vec3& vec3, float _w = 1.0f)
    {
        x = vec3.x;
        y = vec3.y;
        z = vec3.z;
        w = _w;
    }

    Vec4(float a, float b, float c, float d)
    {
        x = a;
        y = b;
        z = c;
        w = d;
    }

    Vec4()
    {
        x = 0;
        y = 0;
        z = 0;
        w = 1;
    }

    void Homogenize();
    float GetMagnitude();
    void Normalize();

    friend Vec4 operator+(Vec4& a, Vec4& b);
    friend Vec4 operator*(Vec4& a, float b);
};

Vec4 operator+(Vec4& a, Vec4& b);
Vec4 operator*(Vec4& a, float& b);

class Mat4
{
public:
    float tab[4][4];

    Mat4()
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                tab[i][j] = 0.f;
            }
        }
    }

    Mat4(float a[4][4]);
    
    void PrintMatrix();
    static Mat4 CreateTransformMatrix(const Vec3& rotation, const Vec3& position, const Vec3& scale);

    friend Mat4 operator*(Mat4& a, Mat4& b);
    friend Mat4 operator*(Mat4& a, float& b);
    void operator*=(Mat4& a);
    void operator*=(float a);
    void operator=(Mat4& a);
};

static Mat4 getIdentityMat4();
static Mat4 CreateTranslationMatrix(const Vec3& translation);
static Mat4 CreateScaleMatrix(const Vec3& scale);
static Mat4 CreateXRotationMatrix(float angle);
static Mat4 CreateYRotationMatrix(float angle);
static Mat4 CreateZRotationMatrix(float angle); 

Mat4 operator*(Mat4& a, Mat4& b);
Mat4 operator*(Mat4& a, float& b);