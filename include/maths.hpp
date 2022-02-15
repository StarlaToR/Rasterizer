#pragma once
#include <cmath>
#include <stdio.h>
#include <vector>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////                       Vec3                       /////////////////////////////////////////////////////

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
    bool IsInTriangle(Vec3 p0,Vec3 p1, Vec3 p2);
    Vec3 GetBarycentricCoords(Vec3 p0,Vec3 p1, Vec3 p2);

    void GetNewZForZBuffer();
};


///////////////////////////////////                       Vec3                       /////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////                       Mat4                       /////////////////////////////////////////////////////

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

    Mat4(
        float a, float b, float c, float d,
        float e, float f, float g, float h,
        float i, float j, float k, float l,
        float m, float n, float o, float p
        );


    void Translate(const Vec3& translation);
    void Rotate(const float& angle, const Vec3& rotationAxis);
    
    void PrintMatrix();
    Mat4 GetTransposeMat4();
    Mat4 GetAdjugateMat4();
    Mat4 GetInvertibleMat4();

    void operator*=(Mat4 a);
    void operator*=(float a);
    void operator=(Mat4 a);
};

///////////////////////////////////                       Mat4                       /////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////                       Vec4                       /////////////////////////////////////////////////////

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
    Vec4 GetHomogenizedVec();
    float GetMagnitude();
    void Normalize();
    bool IsInTriangle(Vec4 p0,Vec4 p1, Vec4 p2);
    Vec4 GetBarycentricCoords(Vec4 p0,Vec4 p1, Vec4 p2);
    void GetNewZForZBuffer();

    friend Vec4 operator+(const Vec4& a, const Vec4& b);
    friend Vec4 operator-(const Vec4& a, const Vec4& b);

    friend Vec4 operator*(const Vec4& a, const float& b);
    
    void operator*=(const float tab[4][4]);


};


///////////////////////////////////                       Vec4                       /////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////                Operator                /////////////////////////////////////////////////////

Mat4 operator*(Mat4 a, Mat4 b);
Mat4 operator*(const Mat4& a, const float& b);

Vec4 operator+(const Vec4& a, const Vec4& b);
Vec4 operator*(const Vec4& a, const float& b);

Vec3 operator+(const Vec3& a, const Vec3& b);
Vec3 operator*(const Vec3& a, const float b);
Vec3 operator*(const Vec3& a, const Vec3& b);
Vec3 operator-(const Vec3& a, const Vec3& b);

/////////////////////////////////////////////                Operator                /////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////           Inline functions            /////////////////////////////////////////////////////


inline Vec3 GetNormalVector(const Vec3& p0, const Vec3& p1, const Vec3& p2)
{
    Vec3 normal = (p1 - p0) * (p2 - p0);
    //printf("normal={%f, %f, %f, %f}\n",normal.x,normal.y,normal.z);
    return normal;
}

inline Vec4 GetMaximumXandY(const std::vector<Vec4>& vertices)
{
    float x=-1,y=-1;
    for(int i=0; i < (int) vertices.size(); i++)
    {
        if(vertices[i].x>=x)
            x=vertices[i].x;
        if(vertices[i].y>=y)
            y=vertices[i].y;
    }
    return {x,y,0,1};
}


inline Vec4 GetMinimumXandY(std::vector<Vec4> vertices)
{
    float x=9999,y=9999;
    for(int i=0; i < (int) vertices.size(); i++)
    {
        if(vertices[i].x<=x)
            x=vertices[i].x;
        if(vertices[i].y<=y)
            y=vertices[i].y;
    }
    return {x,y,0,1};
}

inline Vec3 getSphericalCoords(const float r, const float theta, const float phi)
{
    return { r * sinf(theta) * cosf(phi),
             r * cosf(theta),
             r * sinf(theta) * sinf(phi)
    };
}

inline Mat4 GetIdentityMat4()
{
    Mat4 matrix = Mat4();
    matrix.tab[0][0] = 1;
    matrix.tab[1][1] = 1;
    matrix.tab[2][2] = 1;
    matrix.tab[3][3] = 1;
    return matrix;
}

inline Mat4 CreateTranslationMatrix(const Vec3& translation)
{
    Mat4 matrix = GetIdentityMat4();
    matrix.tab[0][3] = translation.x;
    matrix.tab[1][3] = translation.y;
    matrix.tab[2][3] = translation.z;
    return matrix;
}

inline Mat4 CreateScaleMatrix(const Vec3& scale)
{
    Mat4 matrix = GetIdentityMat4();
    matrix.tab[0][0] = scale.x;
    matrix.tab[1][1] = scale.y;
    matrix.tab[2][2] = scale.z;
    return matrix;
}

inline Mat4 CreateXRotationMatrix(float angle) // ! radian !
{
    Mat4 matrix = GetIdentityMat4();
    matrix.tab[1][1] = cos(angle);
    matrix.tab[1][2] = -sin(angle);
    matrix.tab[2][1] = sin(angle);
    matrix.tab[2][2] = cos(angle);
    return matrix;
}

inline Mat4 CreateYRotationMatrix(float angle) // ! radian !
{
    Mat4 matrix = GetIdentityMat4();
    matrix.tab[0][0] = cos(angle);
    matrix.tab[0][2] = sin(angle);
    matrix.tab[2][0] = -sin(angle);
    matrix.tab[2][2] = cos(angle);
    return matrix;
}

inline Mat4 CreateZRotationMatrix(float angle) // ! radian !
{
    Mat4 matrix = GetIdentityMat4();
    matrix.tab[0][0] = cos(angle);
    matrix.tab[0][1] = -sin(angle);
    matrix.tab[1][0] = sin(angle);
    matrix.tab[1][1] = cos(angle);
    return matrix;
}

inline Mat4 CreateTransformMatrix(const Vec3& rotation, const Vec3& position, const Vec3& scale)
{
    Mat4 translation = CreateTranslationMatrix(position);
    Mat4 rotateX = CreateXRotationMatrix(rotation.x);
    Mat4 rotateY = CreateYRotationMatrix(rotation.y);
    Mat4 rotateZ  = CreateZRotationMatrix(rotation.z);
    Mat4 scaling = CreateScaleMatrix(scale);

    Mat4 transform = translation * rotateY * rotateX * rotateZ * scaling;

    return transform;
}
/////////////////////////////////////////////           Inline functions            /////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


float GetDeterminantMat2(float a, float b, float c, float d);
float GetDeterminantMat3(Vec3 a, Vec3 b, Vec3 c);
float GetDeterminantMat4(Mat4 a);

float GetMaximumDifference(const float a, const float b, const float c);