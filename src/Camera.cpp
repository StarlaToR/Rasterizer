
#include <imgui.h>

#include <maths.hpp>

#include <Camera.hpp>

Camera::Camera(const uint width, const uint height)
{
    //TODO
    // width and height are useful to compute projection matrix with the right aspect ratio
}

void Camera::Update(const float p_deltaTime, const CameraInputs& inputs)
{

    if(inputs.moveLeft==true)
        viewMatrix.tab[0][3]-=0.05f;

    if(inputs.moveRight==true)
        viewMatrix.tab[0][3]+=0.05f;

    if(inputs.moveUp==true)
        viewMatrix.tab[1][3]-=0.05f;

    if(inputs.moveDown==true)
        viewMatrix.tab[1][3]+=0.05f;

}

Mat4 Camera::GetViewMatrix()
{
    //TODO
    return viewMatrix;
}

Mat4 Camera::GetProjection()
{
    //TODO
    return projectionMatrix;
}

void Camera::ShowImGuiControls()
{
    //TODO
}