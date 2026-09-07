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

    // Applies the camera position and viewing direction to OpenGL.
    void applyView() const;

    float x;
    float y;
    float z;

    float yaw;
    float pitch;

private:
    // Direction the camera is currently facing.
    float frontX;
    float frontY;
    float frontZ;

    // Recalculates the front direction from yaw and pitch.
    void updateDirection();
};