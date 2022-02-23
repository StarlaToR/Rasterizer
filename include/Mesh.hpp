
#include<vector>
#include<maths.hpp>
#include<Renderer.hpp>

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>

struct BMPHeader
{
    char signature[2];
    unsigned int fileSize;
    char reserved1[2];
    char reserved2[2];
    unsigned int fileOffsetToPixelArray;
};

struct DIBHeader
{
    unsigned int unused_00;
    unsigned int width;
    unsigned int height;
    unsigned short unused_01;
    unsigned short bpp; // bits per pixel (24,32)
};


class Texture
{
  private:
    unsigned int width;
    unsigned int height;
    Vec3* color;

};

class Mesh
{
    public:

        std::vector<rdrVertex> vertices;
        std::vector<int> index;
        Texture* pTexture=nullptr;

        static Mesh* CreateCube();
        static Mesh* CreateSphere(int latitudeCount, int longitudeCount);        
    
        unsigned char* loadBMP24(const char* filename, int* widthOut, int* heightOut);
        static unsigned char* loadFile(const char* filename, size_t* fileSizeOut);
};


