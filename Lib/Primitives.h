/*
 * File: Primitives.h
 * Project: Carnival of Shadows
 * Course: CSC3081 - Computer Graphics Programming
 *
 * Purpose:
 * Reusable basic 3D shapes used around the carnival scene.
 */

#pragma once

class Primitives
{
public:
    static void drawCube(float size);
    static void drawTexturedCube(float size);

    static void drawSphere(float radius, int slices = 20, int stacks = 20);
    static void drawCylinder(float radius, float height, int slices = 20);
    static void drawCone(float radius, float height, int slices = 20);
};