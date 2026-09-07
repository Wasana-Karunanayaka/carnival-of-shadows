/*
 * File: Camera.cpp
 * Project: Carnival of Shadows
 * Course: CSC3081 - Computer Graphics Programming
 *
 * Purpose:
 * Implements camera viewing, movement and rotation.
 */

#include "Camera.h"

#include <GL/glut.h>
#include <cmath>

const float PI = 3.14159265f;

Camera::Camera()
{
    // Starting position near the carnival entrance.
    x = 0.0f;
    y = 3.0f;
    z = 20.0f;

    // -90 degrees makes the initial camera face toward negative Z.
    yaw = -90.0f;
    pitch = 0.0f;

    updateDirection();
}

void Camera::updateDirection()
{
    float yawRadians = yaw * PI / 180.0f;
    float pitchRadians = pitch * PI / 180.0f;

    // Convert yaw and pitch angles into a 3D forward direction.
    frontX = cosf(yawRadians) * cosf(pitchRadians);
    frontY = sinf(pitchRadians);
    frontZ = sinf(yawRadians) * cosf(pitchRadians);

    // Keep movement speed consistent by normalizing the direction vector.
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
    // Use only X and Z so normal walking stays at the same height.
    x += frontX * distance;
    z += frontZ * distance;
}

void Camera::moveRight(float distance)
{
    // Horizontal vector perpendicular to the forward direction.
    float rightX = -frontZ;
    float rightZ = frontX;

    x += rightX * distance;
    z += rightZ * distance;
}

void Camera::rotateYaw(float angle)
{
    // Yaw turns the camera left and right.
    yaw += angle;
    updateDirection();
}

void Camera::rotatePitch(float angle)
{
    // Pitch looks upward and downward.
    pitch += angle;

    // Prevent the camera from rotating completely upside down.
    if (pitch > 89.0f)
        pitch = 89.0f;

    if (pitch < -89.0f)
        pitch = -89.0f;

    updateDirection();
}

void Camera::applyView() const
{
    // Eye position, target position and world-up direction.
    gluLookAt(x, y, z, x + frontX, y + frontY, z + frontZ, 0.0f, 1.0f, 0.0f);
}