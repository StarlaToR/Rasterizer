#include "test.hpp"

bool testVec3()
{
    //DON'T TOUCH THESE VALUES OR THE TEST WON'T WORK   
    Vec3 v0 = Vec3();
    Vec3 v1 = {0.f,10.f,78.f};
    Vec3 v2 = {41.f,1.4f,1.f};
    Vec3 v3 = v1+v2;
    Vec3 v4 = v1*2;

    if(!(v0.x==0.f and v0.y==0.f and v0.z==0.f))
    {
        printf("ERROR in testVec4 : Vec3() not working\n");
        return false;
    }        


    if(!(v3.x==41.f and v3.y==11.4f and v3.z==79.f))
    {
        printf("ERROR in testVec3 : operator+() not working\n");
        return false;
    }        

    if(!(v4.x==0.f and v4.y==20.f and v4.z==156.f))
    {
        printf("ERROR in testVec3 : operator*() not working\n");
        return false;
    }

    if(!(v1.GetMagnitude()==78.63841301f))
    {
        printf("ERROR in testVec3 : GetMagnitude() not working\n");
        return false;
    }
 
    v1.Normalize();
    if(!(v1.GetMagnitude()>=1.f and v1.GetMagnitude()<1.009f))
    {
        printf("ERROR in testVec3 : Normalize() not working\n");
        return false;
    }

    return true;
}

bool testVec4()
{
    //DON'T TOUCH THESE VALUES OR THE TEST WON'T WORK
    Vec4 v0 = Vec4();
    Vec4 v1 = {40.1f,1.45f,780.f,1023.5f};
    Vec4 v2 = {12.f,63.11f,0.f,9876.f};
    Vec4 v3 = v1+v2;
    Vec4 v4 = v1*2;

    
    if(!(v0.x==0.f and v0.y==0.f and v0.z==0.f and v0.w==1.f))
    {
        printf("ERROR in testVec4 : Vec4() not working\n");
        return false;
    }        


    if(!(v3.x==52.1f and v3.y==64.56f and v3.z==780.f and v3.w==10899.5f))
    {
        printf("ERROR in testVec4 : operator+() not working\n");
        return false;
    }        

    if(!(v4.x==80.2f and v4.y==2.90f and v4.z==1560.f and v4.w==2047.f))
    {
        printf("ERROR in testVec4 : operator*() not working\n");
        return false;
    }

    if(!(v1.GetMagnitude()==781.0314414f))
    {
        printf("ERROR in testVec4 : GetMagnitude() not working\n");
        return false;
    }
 
    v1.Normalize();
    if(!(v1.GetMagnitude()>=1.f and v1.GetMagnitude()<1.009f))
    {
        printf("ERROR in testVec4 : Normalize() not working\n");
        return false;
    }

    v2.Homogenize();
    if(!(v2.x==12.f/9876.f and v2.y==63.11f/9876.f and v2.z==0.f/9876.f))
    {
        printf("ERROR in testVec4 : Homogenize() not working\n");
        return false;
    }

    return true;
}

bool testMat4()
{    
    Mat4 mat = Mat4();
    Mat4 mat2=mat;

    //first value of the first row set to 1
    mat2.tab[0][0]=1;
    //last value of the second row set to 4
    mat2.tab[1][3]=4;
    //last value of the matrix set to 8
    mat2.tab[0][15]=8;

    mat2*=2.f;
    //mat2=mat2*mat;


    Mat4 identityMat = getIdentityMat4();


    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(i==j)
            {
                if(!(identityMat.tab[i][j]==1))
                {
                    printf("ERROR in testMat4 : GetIdentityMatrix() not working\n");
                    return false;
                }   
            }
            else
            {
                if(!(identityMat.tab[i][j]==0))
                {
                    printf("ERROR in testMat4 : GetIdentityMatrix() not working\n");
                    return false;
                }            
            }
        }
    }
}