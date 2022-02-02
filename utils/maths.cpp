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

//Working
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
    Homogenize();
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

void Mat4::getIdentityMat4()
{
    this->tab[1][1] = 1;
    this->tab[2][2] = 1;
    this->tab[3][3] = 1;
    this->tab[4][4] = 1;
}

Mat4 Mat4::CreateTransformMatrix(const Vec3& rotation, const Vec3& position, const Vec3& scale)
{
    Mat4 translation = CreateTranslationMatrix(position);
    Mat4 rotateX = CreateXRotationMatrix(rotation.x);
    Mat4 rotateY = CreateYRotationMatrix(rotation.y);
    Mat4 rotateZ  = CreateZRotationMatrix(rotation.z);
    Mat4 scaling = CreateScaleMatrix(scale);

    Mat4 transform = translation * rotateX;
    transform *= rotateY;
    transform *= rotateZ;
    transform *= scaling;

    return transform;
}

//Working
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

Mat4 Mat4::CreateTranslationMatrix(const Vec3& translation)
{
    Mat4 matrix = Mat4();
    matrix.getIdentityMat4();
    matrix.tab[0][3] = translation.x;
    matrix.tab[1][3] = translation.y;
    matrix.tab[2][3] = translation.z;
    return matrix;
}

Mat4 Mat4::CreateScaleMatrix(const Vec3& scale)
{
    Mat4 matrix = Mat4();
    matrix.getIdentityMat4();
    matrix.tab[0][0] = scale.x;
    matrix.tab[1][1] = scale.y;
    matrix.tab[2][2] = scale.z;
    return matrix;
}

Mat4 Mat4::CreateXRotationMatrix(float angle)
{
    Mat4 matrix = Mat4();
    matrix.getIdentityMat4();
    matrix.tab[1][1] = cos(angle);
    matrix.tab[1][2] = -sin(angle);
    matrix.tab[2][1] = sin(angle);
    matrix.tab[2][2] = cos(angle);
    return matrix;
}

Mat4 Mat4::CreateYRotationMatrix(float angle)
{
    Mat4 matrix = Mat4();
    matrix.getIdentityMat4();
    matrix.tab[0][0] = cos(angle);
    matrix.tab[0][2] = sin(angle);
    matrix.tab[2][0] = -sin(angle);
    matrix.tab[2][2] = cos(angle);
    return matrix;
}

Mat4 Mat4::CreateZRotationMatrix(float angle)
{
    Mat4 matrix = Mat4();
    matrix.getIdentityMat4();
    matrix.tab[0][0] = cos(angle);
    matrix.tab[0][1] = -sin(angle);
    matrix.tab[1][0] = sin(angle);
    matrix.tab[1][1] = cos(angle);
    return matrix;
}


//Working
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
            c.tab[i][j] = a.tab[i][j] + b;
        }
    }

    return c;
}
