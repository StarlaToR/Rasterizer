#include "../utils/maths.hpp"
#include <stdio.h>
#include "test.hpp"

int main()
{
    if(!testVec3() or !testVec4() or !testMat4())
      return -1;    

    printf("TOUT FONCTIONNE !\n");
}