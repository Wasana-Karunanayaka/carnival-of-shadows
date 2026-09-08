/*
 * File: TextureManager.h
 * Project: Carnival of Shadows
 * Course: CSC3081 - Computer Graphics Programming
 *
 * Purpose:
 * Loads and stores image textures used around the carnival.
 */

#pragma once

#include <GL/glut.h>

class TextureManager
{
public:
    static bool initialize();

    static GLuint groundTexture;
    static GLuint pathTexture;
    static GLuint woodTexture;
    static GLuint stoneTexture;
    static GLuint redClothTexture;
    static GLuint dirtyClothTexture;
    static GLuint rustyMetalTexture;

private:
    static GLuint loadTexture(const char* filePath);
};