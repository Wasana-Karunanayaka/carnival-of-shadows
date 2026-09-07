/*
 * File: Camera.cpp
 * Project: Carnival of Shadows
 * Course: CSC3081 - Computer Graphics Programming
 *
 * Purpose:
 * Implements the 3D camera and its viewing direction.
 */

#include "Camera.h"

#include <GL/glut.h>
#include <cmath>

const float PI = 3.14159265f;

Camera::Camera()
{
    // Start slightly above the ground and away from the scene centre.
    x = 0.0f;
    y = 2.0f;
    z = 8.0f;

    // -90 degrees makes the initial camera face toward negative Z.
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

    // Normalize the direction vector.
    float length = sqrtf(frontX * frontX + frontY * frontY + frontZ * frontZ);

    if (length > 0.0f)
    {
        frontX /= length;
        frontY /= length;
        frontZ /= length;
    }
}

void Camera::applyView() const
{
    gluLookAt(
        x, y, z,
        x + frontX, y + frontY, z + frontZ,
        0.0f, 1.0f, 0.0f
    );
}