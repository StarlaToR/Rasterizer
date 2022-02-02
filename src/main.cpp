#include "../utils/maths.hpp"
#include <stdio.h>

int main()
{
    printf("oskour\n");
  
    Vec4 v1 = {1,56,123.4,14};
    Vec4 v2 = {1,1,1,1};

    v1.Homogenize();

    printf("magnitude=%f\n",v1.GetMagnitude());

//    printf("v1={%f,%f,%f,%f}\n",v1.x,v1.y,v1.z,v1.w);
  //  printf("v2={%f,%f,%f,%f}\n",v2.x,v2.y,v2.z,v2.w);
    //printf("v3={%f,%f,%f,%f}\n",v3.x,v3.y,v3.z,v3.w);

}