#pragma once

#include <types.hpp>

struct CameraInputs
{
    float deltaX;
    float deltaY;
    bool moveForward;
    bool moveBackward;
    bool moveLeft;
    bool moveRight;
    bool moveUp;
    bool moveDown;

    bool rotateWorldLeft;
    bool rotateWorldRight;

    // ... and more if needed
};

class Camera
{
public:
    Camera(const uint p_width, const uint p_height);

    void Update(const float p_deltaTime, const CameraInputs& p_inputs);
    Mat4 GetViewMatrix();
    Mat4 GetProjection();

    void ShowImGuiControls();

private:
    Mat4 viewMatrix=GetIdentityMat4();
    Mat4 projectionMatrix=GetIdentityMat4();

};