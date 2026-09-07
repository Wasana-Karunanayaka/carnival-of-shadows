/*
 * File: Camera.h
 * Project: Carnival of Shadows
 * Course: CSC3081 - Computer Graphics Programming
 *
 * Purpose:
 * Defines the camera used to view and navigate the 3D carnival scene.
 */

#pragma once

class Camera
{
public:
    Camera();

    // Applies the current camera position and direction to OpenGL.
    void applyView() const;

    // Moves the camera forward or backward along its viewing direction.
    void moveForward(float distance);

    // Moves the camera sideways relative to its viewing direction.
    void moveRight(float distance);

    // Changes the horizontal viewing angle.
    void rotateYaw(float angle);

    // Changes the vertical viewing angle.
    void rotatePitch(float angle);

    float x;
    float y;
    float z;

    float yaw;
    float pitch;

private:
    float frontX;
    float frontY;
    float frontZ;

    // Recalculates the viewing direction from yaw and pitch.
    void updateDirection();
};