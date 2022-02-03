#include "../utils/maths.hpp"
#include <stdio.h>
#include "test.hpp"

int main()
{
    if(!testVec3() or !testVec4())
      return -1;    
}