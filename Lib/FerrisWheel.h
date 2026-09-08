/*
 * File: FerrisWheel.h
 * Project: Carnival of Shadows
 * Course: CSC3081 - Computer Graphics Programming
 *
 * Purpose:
 * Defines the broken horror Ferris wheel.
 */

#pragma once

class FerrisWheel
{
public:
    FerrisWheel();

    void draw();
    void update();

    void toggleRotation();
    void increaseSpeed();
    void decreaseSpeed();

private:
    // Animation values.
    float wheelAngle;
    float wheelSpeed;
    bool isRotating;

    // Main Ferris wheel measurements.
    float wheelRadius;
    float wheelHeight;
    float wheelDepth;

    void drawBase();
    void drawSupports();
    void drawAxle();

    void drawWheel();
    void drawRim(float z);
    void drawInnerRing(float z);
    void drawSpokes(float z);
    void drawCrossBars();

    void drawCabins();
    void drawCabin(bool damaged);

    // Draws a beam between two points in the X/Y plane.
    void drawBeam(float x1, float y1,
        float x2, float y2,
        float z,
        float thickness,
        float depth);
};