/*
 * File: Camera.h
 * Project: Carnival of Shadows
 * Course: CSC3081 - Computer Graphics Programming
 *
 * Purpose:
 * Defines the camera position, viewing direction and movement
 * used to navigate the 3D carnival scene.
 */

#pragma once

class Camera
{
public:
    Camera();

    // Applies the camera position and direction to the current OpenGL view.
    void applyView() const;

    // Positive distance moves forward; negative distance moves backward.
    void moveForward(float distance);

    // Positive distance moves right; negative distance moves left.
    void moveRight(float distance);

    // Changes the horizontal viewing direction.
    void rotateYaw(float angle);

    // Changes the vertical viewing direction.
    void rotatePitch(float angle);

    // Public so the position can be inspected during testing or review.
    float x;
    float y;
    float z;

    float yaw;
    float pitch;

private:
    float frontX;
    float frontY;
    float frontZ;

    // Converts yaw and pitch angles into a normalized direction vector.
    void updateDirection();
};