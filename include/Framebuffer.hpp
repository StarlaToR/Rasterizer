#pragma once

#include <vector>
#include <glad/gl.h>
#include <types.hpp>

#include <maths.hpp>

class Framebuffer
{
private:
    int width = 0;
    int height = 0;

    // In-RAM buffers
    std::vector<float4> colorBuffer;
   // std::vector<float> depthBuffer;
    float* depthBuffer;

    // OpenGL texture (in VRAM)
    GLuint colorTexture = 0;

public:
    float4 clearColor = { 0.f, 0.f, 0.f, 1.f };

    Framebuffer(int width, int height);
    Framebuffer()
    {

    };
    ~Framebuffer();

    void Clear();
    void UpdateTexture();

    float4* GetColorBuffer4f() { return colorBuffer.data(); }

    float* GetColorBuffer() { return reinterpret_cast<float*>(colorBuffer.data()); }
    void SetDepthBuffer(int index, float value){ depthBuffer[index]=value; }
    float& GetDepthBuffer(int index) { return depthBuffer[index]; }
    
    int GetWidth()  const   { return width; }
    int GetHeight() const   { return height; }

    GLuint GetColorTexture() const { return colorTexture; }



};