#include "../utils/maths.hpp"
#include <stdio.h>
#include "test.hpp"
int main()
{
    if(!testVec3() or !testVec4())
      return -1;

    /*

    Mat4 mat = Mat4();

    Mat4 mat2=mat;

    //first value of the first row set to 1
    mat2.tab[0][0]=1;

    //last value of the second row set to 4
    mat2.tab[1][3]=4;

    //last value of the matrix set to 8
    mat2.tab[0][15]=8;

    mat2.PrintMatrix();
    mat2*=2.f;
    //mat2=mat2*mat;
    mat2.PrintMatrix();
*/
    

    Mat4 matrix = Mat4();
    //matrix.getIdentityMat4();
    matrix.CreateTransformMatrix({6, 7, 9}, {1, 0, 0}, {1, 1, 1});
    matrix.PrintMatrix();
}