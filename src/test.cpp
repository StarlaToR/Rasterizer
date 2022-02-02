#include "test.hpp"

bool testVec3()
{
    Vec3 v1 = {0.f,10.f,78.f};
    Vec3 v2 = {41.f,1.4f,1.f};
    Vec3 v3 = v1+v2;
    Vec3 v4 = v1*2;

    if(!(v3.x==41.f and v3.y==11.4f and v3.z==79.f))
    {
        printf("ERROR in testVec3 : ADDITION NOT WORKING\n");
        return false;
    }        

    if(!(v4.x==0.f and v4.y==20.f and v4.z==156.f))
    {
        printf("ERROR in testVec3 : MULTIPLICATION NOT WORKING\n");
        return false;
    }

    if(!(v1.GetMagnitude()==78.63841301f))
    {
        printf("ERROR in testVec3 : MAGNITUDE NOT WORKING\n");
        return false;
    }
 
    v1.Normalize();
    if(!(v1.GetMagnitude()>=1.f and v1.GetMagnitude()<1.009f))
    {
        printf("ERROR in testVec3 : NORMALIZE NOT WORKING\n");
        return false;
    }

    return true;
}

bool testVec4()
{
    Vec4 v1 = {40.1f,1.45f,780.f,1023.5f};
    Vec4 v2 = {12.f,63.11f,0.f,9876.f};
    Vec4 v3 = v1+v2;
    Vec4 v4 = v1*2;

    if(!(v3.x==52.1f and v3.y==64.56f and v3.z==780.f and v3.w==10899.5f))
    {
        printf("ERROR in testVec4 : ADDITION NOT WORKING\n");
        return false;
    }        

    if(!(v4.x==80.2f and v4.y==2.90f and v4.z==1560.f and v4.w==2047.f))
    {
        printf("ERROR in testVec4 : MULTIPLICATION NOT WORKING\n");
        return false;
    }

    if(!(v1.GetMagnitude()==781.0314414f))
    {
        printf("ERROR in testVec4 : MAGNITUDE NOT WORKING\n");
        return false;
    }
 
    v1.Normalize();
    if(!(v1.GetMagnitude()>=1.f and v1.GetMagnitude()<1.009f))
    {
        printf("ERROR in testVec4 : NORMALIZE NOT WORKING\n");
        return false;
    }

    v2.Homogenize();
    if(!(v2.x==0.0012150668f and v2.y==0.006390239f and v2.z==0.f))
    {
        printf("ERROR in testVec4 : HOMOGENIZE NOT WORKING\n");
        return false;
    }

    return true;
}