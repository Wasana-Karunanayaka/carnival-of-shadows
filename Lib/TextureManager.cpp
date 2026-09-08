/*
 * File: TextureManager.cpp
 * Project: Carnival of Shadows
 * Course: CSC3081 - Computer Graphics Programming
 *
 * Purpose:
 * Loads carnival textures using SOIL2.
 */

#include "pch.h"
#include "TextureManager.h"

#include <SOIL2/SOIL2.h>
#include <iostream>


GLuint TextureManager::groundTexture = 0;
GLuint TextureManager::pathTexture = 0;
GLuint TextureManager::woodTexture = 0;
GLuint TextureManager::stoneTexture = 0;
GLuint TextureManager::redClothTexture = 0;
GLuint TextureManager::dirtyClothTexture = 0;
GLuint TextureManager::rustyMetalTexture = 0;


// -----------------------------------------------------------------------------
// Texture loading
// -----------------------------------------------------------------------------

GLuint TextureManager::loadTexture(const char* filePath)
{
    GLuint texture = SOIL_load_OGL_texture(
        filePath,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
    );

    if (texture == 0)
    {
        std::cout << "Texture failed: " << filePath << std::endl;
        std::cout << SOIL_last_result() << std::endl;
        return 0;
    }

    glBindTexture(GL_TEXTURE_2D, texture);

    // Repeat the image across larger surfaces.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return texture;
}


// -----------------------------------------------------------------------------
// Carnival textures
// -----------------------------------------------------------------------------

bool TextureManager::initialize()
{
    groundTexture = loadTexture("textures/muddy_ground.jpg");
    pathTexture = loadTexture("textures/dirty_path.jpg");
    woodTexture = loadTexture("textures/rotten_wood.jpg");
    stoneTexture = loadTexture("textures/old_stone.jpg");
    redClothTexture = loadTexture("textures/red_torn_cloth.jpg");
    dirtyClothTexture = loadTexture("textures/dirty_cloth.jpg");
    rustyMetalTexture = loadTexture("textures/rusty_metal.jpg");

    return groundTexture != 0 &&
        pathTexture != 0 &&
        woodTexture != 0 &&
        stoneTexture != 0 &&
        redClothTexture != 0 &&
        dirtyClothTexture != 0 &&
        rustyMetalTexture != 0;

}