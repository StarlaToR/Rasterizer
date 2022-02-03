#include "maths.hpp"

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


Mat4::Mat4(float a[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            tab[i][j] = a[i][j];
        }
    }
}

void Mat4::PrintMatrix()
{
    for(int i=0;i<4;i++)
    {
        printf("{ ");
        for(int j=0;j<3;j++)
            printf("%f, ",this->tab[i][j]);
        printf("%f }\n",this->tab[i][3]);
    }
    printf("\n\n");
}

Mat4 Mat4::GetTransposeMat4()
{
    Mat4 matrix = Mat4();
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            matrix.tab[i][j] = this->tab[j][i];
        }
    }
    return matrix;
}

Mat4 Mat4::GetAdjugateMat4()
{
    Mat4 matrix = Mat4();

    matrix.tab[0][0] = GetDeterminantMat3({this->tab[1][1], this->tab[1][2], this->tab[1][3]},{this->tab[2][1], this->tab[2][2], this->tab[2][3]},{this->tab[3][1], this->tab[3][2], this->tab[3][3]});
    matrix.tab[0][1] = GetDeterminantMat3({this->tab[1][0], this->tab[1][2], this->tab[1][3]},{this->tab[2][0], this->tab[2][2], this->tab[2][3]},{this->tab[3][0], this->tab[3][2], this->tab[3][3]});
    matrix.tab[0][2] = GetDeterminantMat3({this->tab[1][0], this->tab[1][1], this->tab[1][3]},{this->tab[2][0], this->tab[2][1], this->tab[2][3]},{this->tab[3][0], this->tab[3][1], this->tab[3][3]});
    matrix.tab[0][3] = GetDeterminantMat3({this->tab[1][0], this->tab[1][1], this->tab[1][2]},{this->tab[2][0], this->tab[2][1], this->tab[2][2]},{this->tab[3][0], this->tab[3][1], this->tab[3][2]});

    matrix.tab[1][0] = GetDeterminantMat3({this->tab[0][1], this->tab[0][2], this->tab[0][3]},{this->tab[2][1], this->tab[2][2], this->tab[2][3]},{this->tab[3][1], this->tab[3][2], this->tab[3][3]});
    matrix.tab[1][1] = GetDeterminantMat3({this->tab[0][0], this->tab[0][2], this->tab[0][3]},{this->tab[2][0], this->tab[2][2], this->tab[2][3]},{this->tab[3][0], this->tab[3][2], this->tab[3][3]});
    matrix.tab[1][2] = GetDeterminantMat3({this->tab[0][0], this->tab[0][1], this->tab[0][3]},{this->tab[2][0], this->tab[2][1], this->tab[2][3]},{this->tab[3][0], this->tab[3][1], this->tab[3][3]});
    matrix.tab[1][3] = GetDeterminantMat3({this->tab[0][0], this->tab[0][1], this->tab[0][2]},{this->tab[2][0], this->tab[2][1], this->tab[2][2]},{this->tab[3][0], this->tab[3][1], this->tab[3][2]});

    matrix.tab[2][0] = GetDeterminantMat3({this->tab[0][1], this->tab[0][2], this->tab[0][3]},{this->tab[1][1], this->tab[1][2], this->tab[1][3]},{this->tab[3][1], this->tab[3][2], this->tab[3][3]});
    matrix.tab[2][1] = GetDeterminantMat3({this->tab[0][0], this->tab[0][2], this->tab[0][3]},{this->tab[1][0], this->tab[1][2], this->tab[1][3]},{this->tab[3][0], this->tab[3][2], this->tab[3][3]});
    matrix.tab[2][2] = GetDeterminantMat3({this->tab[0][0], this->tab[0][1], this->tab[0][3]},{this->tab[1][0], this->tab[1][1], this->tab[1][3]},{this->tab[3][0], this->tab[3][1], this->tab[3][3]});
    matrix.tab[2][3] = GetDeterminantMat3({this->tab[0][0], this->tab[0][1], this->tab[0][2]},{this->tab[1][0], this->tab[1][1], this->tab[1][2]},{this->tab[3][0], this->tab[3][1], this->tab[3][2]});

    matrix.tab[3][0] = GetDeterminantMat3({this->tab[0][1], this->tab[0][2], this->tab[0][3]},{this->tab[1][1], this->tab[1][2], this->tab[1][3]},{this->tab[2][1], this->tab[2][2], this->tab[2][3]});
    matrix.tab[3][1] = GetDeterminantMat3({this->tab[0][0], this->tab[0][2], this->tab[0][3]},{this->tab[1][0], this->tab[1][2], this->tab[1][3]},{this->tab[2][0], this->tab[2][2], this->tab[2][3]});
    matrix.tab[3][2] = GetDeterminantMat3({this->tab[0][0], this->tab[0][1], this->tab[0][3]},{this->tab[1][0], this->tab[1][1], this->tab[1][3]},{this->tab[2][0], this->tab[2][1], this->tab[2][3]});
    matrix.tab[3][3] = GetDeterminantMat3({this->tab[0][0], this->tab[0][1], this->tab[0][2]},{this->tab[1][0], this->tab[1][1], this->tab[1][2]},{this->tab[2][0], this->tab[2][1], this->tab[2][2]});

    return matrix;
}


Mat4 Mat4::GetInvertibleMat4()
{
    return (this->GetAdjugateMat4() * (1 / GetDeterminantMat4(*this)));
}







float GetDeterminantMat2(float a, float b, float c, float d)
{
    return (a * d - b * c);
}

float GetDeterminantMat3(Vec3 a, Vec3 b, Vec3 c)
{
    return (
        a.x * GetDeterminantMat2(b.y, b.z, c.y, c.z)
        - a.y * GetDeterminantMat2(b.x, b.z, c.x, c.z)
        + a.z * GetDeterminantMat2(b.x, b.y, c.x, c.y)
    );
}

float GetDeterminantMat4(Mat4 a)
{
    return(
        a.tab[0][0] * GetDeterminantMat3({a.tab[1][1], a.tab[1][2], a.tab[1][3]}, {a.tab[2][1], a.tab[2][2], a.tab[2][3]}, {a.tab[3][1], a.tab[3][2], a.tab[3][3]})
        - a.tab[0][1] * GetDeterminantMat3({a.tab[1][0], a.tab[1][2], a.tab[1][3]}, {a.tab[2][0], a.tab[2][2], a.tab[2][3]}, {a.tab[3][0], a.tab[3][2], a.tab[3][3]})
        + a.tab[0][2] * GetDeterminantMat3({a.tab[1][0], a.tab[1][1], a.tab[1][3]}, {a.tab[2][0], a.tab[2][1], a.tab[2][3]}, {a.tab[3][0], a.tab[3][1], a.tab[3][3]})
        - a.tab[0][3] * GetDeterminantMat3({a.tab[1][0], a.tab[1][1], a.tab[1][2]}, {a.tab[2][0], a.tab[2][1], a.tab[2][2]}, {a.tab[3][0], a.tab[3][1], a.tab[3][2]})
    );
}

void Mat4::operator=(Mat4& a)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            this->tab[i][j] = a.tab[i][j];
        }
    }
}


void Mat4::operator*=(Mat4& a)
{
    Mat4 c = Mat4();

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                c.tab[i][j] += this->tab[i][k] * a.tab[k][j];
            }
        }
    }

    *this = c;
}

//Working
void Mat4::operator*=(float a)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            this->tab[i][j] *= a;
        }
    }
}

Mat4 operator*(Mat4& a, Mat4& b)
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

Mat4 operator*(Mat4& a, float& b)
{
    Mat4 c = Mat4();

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            c.tab[i][j] = a.tab[i][j] * b;
        }
    }

    return c;
}