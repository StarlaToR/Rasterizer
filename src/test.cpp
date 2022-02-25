#include <test.hpp>

bool testVec3()
{
    bool working=true;

    //DON'T TOUCH THESE VALUES OR THE TEST WON'T WORK   
    Vec3 v0 = Vec3();
    Vec3 v1 = {0.f,10.f,78.f};
    Vec3 v2 = {41.f,1.4f,1.f};
    Vec3 v3 = v1+v2;
    Vec3 v4 = v1*2;

    if(!(v0.x==0.f and v0.y==0.f and v0.z==0.f))
    {
        printf("ERROR in testVec4 : Vec3() not working\n");
        working=false;
    }        


    if(!(v3.x==41.f and v3.y==11.4f and v3.z==79.f))
    {
        printf("ERROR in testVec3 : operator+() not working\n");
        working=false;
    }        

    if(!(v4.x==0.f and v4.y==20.f and v4.z==156.f))
    {
        printf("ERROR in testVec3 : operator*() not working\n");
        working=false;
    }

    if(!(v1.GetMagnitude()==78.63841301f))
    {
        printf("ERROR in testVec3 : GetMagnitude() not working\n");
        working=false;
    }
 
    v1.Normalize();
    if(!(v1.GetMagnitude()>=1.f and v1.GetMagnitude()<1.009f))
    {
        printf("ERROR in testVec3 : Normalize() not working\n");
        working=false;
    }

    return working;
}

bool testVec4()
{
    bool working=true;

    //DON'T TOUCH THESE VALUES OR THE TEST WON'T WORK
    Vec4 v0 = Vec4();
    Vec4 v1 = {40.1f,1.45f,780.f,1023.5f};
    Vec4 v2 = {12.f,63.11f,0.f,9876.f};
    Vec4 v3 = v1+v2;
    Vec4 v4 = v1 * 2.f;

    
    if(!(v0.x==0.f and v0.y==0.f and v0.z==0.f and v0.w==1.f))
    {
        printf("ERROR in testVec4 : Vec4() not working\n");
        working=false;
    }        


    if(!(v3.x==52.1f and v3.y==64.56f and v3.z==780.f and v3.w==10899.5f))
    {
        printf("ERROR in testVec4 : operator+() not working\n");
        working=false;
    }        

    if(!(v4.x==80.2f and v4.y==2.90f and v4.z==1560.f and v4.w==2047.f))
    {
        printf("ERROR in testVec4 : operator*() not working\n");
        working=false;
    }

    if(!(v1.GetMagnitude()==781.0314414f))
    {
        printf("ERROR in testVec4 : GetMagnitude() not working\n");
        working=false;
    }
 
    v1.Normalize();
    if(!(v1.GetMagnitude()>=1.f and v1.GetMagnitude()<1.009f))
    {
        printf("ERROR in testVec4 : Normalize() not working\n");
        working=false;
    }

    v2.Homogenize();
    if(!(v2.x==12.f/9876.f and v2.y==63.11f/9876.f and v2.z==0.f/9876.f))
    {
        printf("ERROR in testVec4 : Homogenize() not working\n");
        working=false;
    }

    return working;
}

bool testMat4()
{   
    bool working=true;
    Mat4 identityMat = GetIdentityMat4();

    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(i==j)
            {
                if(!(identityMat.tab[i][j]==1))
                {
                    printf("ERROR in testMat4 : GetIdentityMatrix() not working\n");
                    working=false;
                }   
            }
            else
            {
                if(!(identityMat.tab[i][j]==0))
                {
                    printf("ERROR in testMat4 : GetIdentityMatrix() not working\n");
                    working=false;
                }            
            }
        }
    }

    float data1[4][4]=
    {
        {1,2,3,4},
        {1,2,3,4},
        {1,2,3,4},
        {1,2,3,4}
    };
    float data2[4][4]=
    {
        {1,1,1,1},
        {2,2,2,2},
        {3,3,3,3},
        {4,4,4,4}
    };

    Mat4 mat1 = Mat4(data1);
    Mat4 mat2 = Mat4(data2);

    Mat4 mat3 = mat2*mat1;

    if(
        mat3.tab[0][0]!=4.f or mat3.tab[0][1]!=8.f or mat3.tab[0][2]!=12.f or mat3.tab[0][3]!=16.f or
        mat3.tab[1][0]!=8.f or mat3.tab[1][1]!=16.f or mat3.tab[1][2]!=24.f or mat3.tab[1][3]!=32.f or
        mat3.tab[2][0]!=12.f or mat3.tab[2][1]!=24.f or mat3.tab[2][2]!=36.f or mat3.tab[2][3]!=48.f or
        mat3.tab[3][0]!=16.f or mat3.tab[3][1]!=32.f or mat3.tab[3][2]!=48.f or mat3.tab[3][3]!=64.f     
        )
    {
        printf("ERROR in testMat4 : operator*() not working\n");
        working=false;
    } 

    float data3[4][4]=
    {
        {3,3,3,3},
        {3,3,3,3},
        {3,3,3,3},
        {3,3,3,3}
    };
 
    Mat4 translationMat = CreateTranslationMatrix({5,35.4f,8});
    if(
        translationMat.tab[0][0]!=1.f or translationMat.tab[0][1]!=0.f or translationMat.tab[0][2]!=0.f or translationMat.tab[0][3]!=5.f or
        translationMat.tab[1][0]!=0.f or translationMat.tab[1][1]!=1.f or translationMat.tab[1][2]!=0.f or translationMat.tab[1][3]!=35.4f or
        translationMat.tab[2][0]!=0.f or translationMat.tab[2][1]!=0.f or translationMat.tab[2][2]!=1.f or translationMat.tab[2][3]!=8.f or
        translationMat.tab[3][0]!=0.f or translationMat.tab[3][1]!=0.f or translationMat.tab[3][2]!=0.f or translationMat.tab[3][3]!=1.f     
        )
    {
        printf("ERROR in testMat4 : CreateTranslationMatrix() not working\n");
        working=false;            
    }


    Mat4 scaleMat = CreateScaleMatrix({2,879,0.1f});
    if(
        scaleMat.tab[0][0]!=2.f or scaleMat.tab[0][1]!=0.f or scaleMat.tab[0][2]!=0.f or scaleMat.tab[0][3]!=0.f or
        scaleMat.tab[1][0]!=0.f or scaleMat.tab[1][1]!=879.f or scaleMat.tab[1][2]!=0.f or scaleMat.tab[1][3]!=0.f or
        scaleMat.tab[2][0]!=0.f or scaleMat.tab[2][1]!=0.f or scaleMat.tab[2][2]!=0.1f or scaleMat.tab[2][3]!=0.f or
        scaleMat.tab[3][0]!=0.f or scaleMat.tab[3][1]!=0.f or scaleMat.tab[3][2]!=0.f or scaleMat.tab[3][3]!=1.f     
        )
    {
        printf("ERROR in testMat4 : CreateScaleMatrix() not working\n");
        working=false;            
    }


    Mat4 rotateXMat = CreateXRotationMatrix(M_PI/16);
    if(
        rotateXMat.tab[0][0]!=1.f or rotateXMat.tab[0][1]!=0.f or rotateXMat.tab[0][2]!=0.f or rotateXMat.tab[0][3]!=0.f or
        rotateXMat.tab[1][0]!=0.f or rotateXMat.tab[1][1]!=(float)cos(M_PI/16) or rotateXMat.tab[1][2]!=(float)-sin(M_PI/16) or rotateXMat.tab[1][3]!=0.f or
        rotateXMat.tab[2][0]!=0.f or rotateXMat.tab[2][1]!=(float)sin(M_PI/16) or rotateXMat.tab[2][2]!=(float)cos(M_PI/16) or rotateXMat.tab[2][3]!=0.f or
        rotateXMat.tab[3][0]!=0.f or rotateXMat.tab[3][1]!=0.f or rotateXMat.tab[3][2]!=0.f or rotateXMat.tab[3][3]!=1.f 
    )
    {
        printf("ERROR in testMat4 : CreateXRotationMatrix() not working\n");
        working=false;
    }

    Mat4 rotateYMat = CreateYRotationMatrix(M_PI/16);
    if(
        rotateYMat.tab[0][0]!=(float)cos(M_PI/16) or rotateYMat.tab[0][1]!=0.f or rotateYMat.tab[0][2]!=(float)sin(M_PI/16) or rotateYMat.tab[0][3]!=0.f or
        rotateYMat.tab[1][0]!=0.f or rotateYMat.tab[1][1]!=1.f or rotateYMat.tab[1][2]!=0.f or rotateYMat.tab[1][3]!=0.f or
        rotateYMat.tab[2][0]!=(float)-sin(M_PI/16) or rotateYMat.tab[2][1]!=0.f or rotateYMat.tab[2][2]!=(float)cos(M_PI/16) or rotateYMat.tab[2][3]!=0.f or
        rotateYMat.tab[3][0]!=0.f or rotateYMat.tab[3][1]!=0.f or rotateYMat.tab[3][2]!=0.f or rotateYMat.tab[3][3]!=1.f 
    )
    {
        printf("ERROR in testMat4 : CreateYRotationMatrix() not working\n");
        working=false;
    }


    Mat4 rotateZMat = CreateZRotationMatrix(M_PI/16);
    if(
        rotateZMat.tab[0][0]!=(float)cos(M_PI/16) or rotateZMat.tab[0][1]!=(float)-sin(M_PI/16) or rotateZMat.tab[0][2]!=0.f or rotateZMat.tab[0][3]!=0.f or
        rotateZMat.tab[1][0]!=(float)sin(M_PI/16) or rotateZMat.tab[1][1]!=(float)cos(M_PI/16) or rotateZMat.tab[1][2]!=0.f or rotateZMat.tab[1][3]!=0.f or
        rotateZMat.tab[2][0]!=0.f or rotateZMat.tab[2][1]!=0.f or rotateZMat.tab[2][2]!=1.f or rotateZMat.tab[2][3]!=0.f or
        rotateZMat.tab[3][0]!=0.f or rotateZMat.tab[3][1]!=0.f or rotateZMat.tab[3][2]!=0.f or rotateZMat.tab[3][3]!=1.f 
    )
    {
        printf("ERROR in testMat4 : CreateZRotationMatrix() not working\n");
        working=false;
    }


    return working;
}