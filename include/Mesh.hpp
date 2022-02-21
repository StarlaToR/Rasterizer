
#include<vector>
#include<maths.hpp>
#include<Renderer.hpp>


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
};


