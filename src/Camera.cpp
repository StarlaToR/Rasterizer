
#include <imgui.h>

#include <maths.hpp>

#include <Camera.hpp>

Camera::Camera(const uint width, const uint height)
{
    //TODO
    // width and height are useful to compute projection matrix with the right aspect ratio
    projectionMatrix = {
        -1, 0, 0, 0,
        0, -1, 0, 0,
        0, 0, -(-100 + -1)/(-100 - -1), -2*(-100)*(-1)/ (-100 - (- 1)),
        0, 0, -1, 0
    };
}

void Camera::Update(const float p_deltaTime, const CameraInputs& inputs)
{
    // Movements
    if(inputs.moveLeft==true)
        position.x+=0.05f;
    if(inputs.moveRight==true)
        position.x-=0.05f;

    if(inputs.moveUp==true)
        position.y+=0.05f;
    if(inputs.moveDown==true)
        position.y-=0.05f;

    if(inputs.moveForward==true)
        position.z-=0.05f;
    if(inputs.moveBackward==true)
        position.z+=0.05f;


    // Rotations
    if(inputs.rotateWorldRight==true)
        rotation.y-=0.1f;
    if(inputs.rotateWorldLeft==true)
        rotation.y+=0.1f;

    if(inputs.rotateWorldUp==true)
        rotation.x-=0.1f;
    if(inputs.rotateWorldDown==true)
        rotation.x+=0.1f;

    viewMatrix = CreateTransformMatrix(position,rotation,{1,1,1});

}

Mat4 Camera::GetViewMatrix()
{
    return viewMatrix;
}

Mat4 Camera::GetProjection()
{
    return projectionMatrix;
}

void Camera::ShowImGuiControls()
{
    ImGui::Text("Test");
}