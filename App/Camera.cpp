/*
 * File: Camera.cpp
 * Project: Carnival of Shadows
 * Course: CSC3081 - Computer Graphics Programming
 *
 * Purpose:
 * Implements camera movement and viewing direction.
 */

#include "Camera.h"

#include <GL/glut.h>
#include <cmath>

const float PI = 3.14159265f;

Camera::Camera()
{
    // Starting position can be changed later to place the player at the carnival entrance.
    x = 0.0f;
    y = 2.0f;
    z = 8.0f;

    // -90 degrees points the camera toward the negative Z direction.
    yaw = -90.0f;
    pitch = 0.0f;

    updateDirection();
}

void Camera::updateDirection()
{
    float yawRadians = yaw * PI / 180.0f;
    float pitchRadians = pitch * PI / 180.0f;

    // Convert yaw and pitch angles into a 3D direction vector.
    frontX = cosf(yawRadians) * cosf(pitchRadians);
    frontY = sinf(pitchRadians);
    frontZ = sinf(yawRadians) * cosf(pitchRadians);

    float length = sqrtf(frontX * frontX + frontY * frontY + frontZ * frontZ);

    if (length > 0.0f)
    {
        frontX /= length;
        frontY /= length;
        frontZ /= length;
    }
}

void Camera::moveForward(float distance)
{
    // Move along the horizontal viewing direction so normal movement stays on the ground.
    x += frontX * distance;
    z += frontZ * distance;
}

void Camera::moveRight(float distance)
{
    // Right direction is perpendicular to the camera's horizontal forward direction.
    float rightX = -frontZ;
    float rightZ = frontX;

    x += rightX * distance;
    z += rightZ * distance;
}

void Camera::rotateYaw(float angle)
{
    yaw += angle;
    updateDirection();
}

void Camera::rotatePitch(float angle)
{
    pitch += angle;

    // Prevent the camera from flipping upside down.
    if (pitch > 89.0f)
        pitch = 89.0f;

    if (pitch < -89.0f)
        pitch = -89.0f;

    updateDirection();
}

void Camera::applyView() const
{
    gluLookAt(x, y, z,
        x + frontX, y + frontY, z + frontZ,
        0.0f, 1.0f, 0.0f);
}