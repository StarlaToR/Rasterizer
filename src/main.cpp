#include "../utils/maths.hpp"
#include <stdio.h>

int main()
{
  /*
    printf("oskour\n");
  
    Vec4 v1 = {0,10,0,2};
    Vec4 v2 = {1,1,1,1};
    Vec4 v3 = v1+v2;

    Vec3 v4 = {0,10,78};
    Vec3 v5 = {41,1.4,1};
    Vec3 v6 = v4+v5;


    printf("v4={%f,%f,%f}\n",v4.x,v4.y,v4.z);
    printf("v5={%f,%f,%f}\n",v5.x,v5.y,v5.z);
    printf("v4+v5={%f,%f,%f}\n\n\n",v6.x,v6.y,v6.z);
    

    printf("v1={%f,%f,%f,%f}\n",v1.x,v1.y,v1.z,v1.w);
    printf("v2={%f,%f,%f,%f}\n",v2.x,v2.y,v2.z,v2.w);
    printf("v1+v2={%f,%f,%f,%f}\n\n\n",v3.x,v3.y,v3.z,v3.w);

    printf("v1.magnitude=%f\nv1.Homogenize()\n",v1.GetMagnitude());
    v1.Homogenize();
    printf("v1.magnitude=%f\n\n\n",v1.GetMagnitude());
*/

   // Mat4 translationMatrix = Mat4::CreateTranslationMatrix({3,0,0});
    
    Mat4 mat = Mat4();

    //first value of the first row set to 1
    mat.tab[0][0]=1;

    //last value of the second row set to 4
    mat.tab[1][3]=4;

    //last value of the matrix set to 8
    mat.tab[0][15]=8;

    mat.PrintMatrix();

}