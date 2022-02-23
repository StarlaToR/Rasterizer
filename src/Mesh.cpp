#include <Mesh.hpp>

Mesh* Mesh::CreateCube()
{
    
}

Mesh* Mesh::CreateSphere(int latitudeCount, int longitudeCount)
{
    
}

static unsigned char* loadFile(const char* filename, size_t* fileSizeOut)
{
    unsigned char* data = nullptr;

    // Open file
    std::ifstream file(filename, std::ios_base::binary);
    if (!file.is_open())
    {
        printf("Error to open file '%s'\n", filename);
        return nullptr;
    }

    // Read filesize
    file.seekg(0, std::ios_base::end);
    *fileSizeOut = file.tellg();
    file.seekg(0, std::ios_base::beg);
    
    // Allocate memory
    data = new unsigned char[*fileSizeOut];
    file.read((char*)data, *fileSizeOut);

    file.close();

    return data;
};

unsigned char* loadBMP24(const char* filename, int* widthOut, int* heightOut)
{
    size_t fileSize ; 
    unsigned char* data = loadFile(filename,&fileSize);
    

    if(data==nullptr)
        return nullptr;

    BMPHeader* header = (BMPHeader*)(data);
    DIBHeader* dibHeader = (DIBHeader*)(data+sizeof(BMPHeader));


    if(dibHeader->bpp!=24)
        return nullptr;


    int width = dibHeader->width;
    int height = dibHeader->height;

    if(width<0)
        width*=-1; 
    if(height<0)
        height*=-1; 

    unsigned char* pixels = new unsigned char[width*height*3];
    unsigned char* pixelArray = data + header->fileOffsetToPixelArray;
    memcpy(pixels,pixelArray,width*height*3);

    if(widthOut)
        *widthOut=width;
    if(heightOut)
        *heightOut=height;

    delete data;

    return pixels;
}