/*
 * File: Main.cpp
 * Project: Carnival of Shadows
 * Course: CSC3081 - Computer Graphics Programming
 *
 * Purpose:
 * Entry point for the Carnival of Shadows application.
 *
 * Responsible for:
 * - creating the GLUT window
 * - configuring camera and projection
 * - handling keyboard input
 * - drawing the carnival environment
 */

#include <GL/glut.h>

#include "../Lib/Primitives.h"
#include "../Lib/HauntedTree.h"
#include "../Lib/TextureManager.h"
#include "Camera.h"

#include <cmath>



 // -----------------------------------------------------------------------------
 // Application state
 // -----------------------------------------------------------------------------

Camera camera;

// true = perspective projection, false = orthographic projection.
bool usePerspective = true;

// Initial application window size.
int windowWidth = 800;
int windowHeight = 600;


// -----------------------------------------------------------------------------
// Ground and carnival paths
// -----------------------------------------------------------------------------

void drawGround()
{
    const float groundSize = 40.0f;
    const float pathY = 0.015f;


    // -------------------------------------------------------------------------
    // Muddy ground
    // -------------------------------------------------------------------------

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, TextureManager::groundTexture);

    // White keeps the original texture colour.
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_QUADS);

    // Repeat the texture instead of stretching it across the whole carnival.
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-groundSize, 0.0f, -groundSize);

    glTexCoord2f(16.0f, 0.0f);
    glVertex3f(groundSize, 0.0f, -groundSize);

    glTexCoord2f(16.0f, 16.0f);
    glVertex3f(groundSize, 0.0f, groundSize);

    glTexCoord2f(0.0f, 16.0f);
    glVertex3f(-groundSize, 0.0f, groundSize);

    glEnd();


    // -------------------------------------------------------------------------
    // Dirty carnival paths
    // -------------------------------------------------------------------------

    glBindTexture(GL_TEXTURE_2D, TextureManager::pathTexture);


    // Main entrance path.
    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-2.5f, pathY, 12.0f);

    glTexCoord2f(2.0f, 0.0f);
    glVertex3f(2.5f, pathY, 12.0f);

    glTexCoord2f(2.0f, 6.0f);
    glVertex3f(2.5f, pathY, -5.0f);

    glTexCoord2f(0.0f, 6.0f);
    glVertex3f(-2.5f, pathY, -5.0f);

    glEnd();


    // Central plaza.
    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-12.0f, pathY, -5.0f);

    glTexCoord2f(8.0f, 0.0f);
    glVertex3f(12.0f, pathY, -5.0f);

    glTexCoord2f(8.0f, 5.0f);
    glVertex3f(12.0f, pathY, -20.0f);

    glTexCoord2f(0.0f, 5.0f);
    glVertex3f(-12.0f, pathY, -20.0f);

    glEnd();


    // Left branch.
    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-22.0f, pathY, -10.0f);

    glTexCoord2f(3.0f, 0.0f);
    glVertex3f(-12.0f, pathY, -10.0f);

    glTexCoord2f(3.0f, 2.0f);
    glVertex3f(-12.0f, pathY, -15.0f);

    glTexCoord2f(0.0f, 2.0f);
    glVertex3f(-22.0f, pathY, -15.0f);

    glEnd();


    // Right branch.
    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(12.0f, pathY, -10.0f);

    glTexCoord2f(3.0f, 0.0f);
    glVertex3f(22.0f, pathY, -10.0f);

    glTexCoord2f(3.0f, 2.0f);
    glVertex3f(22.0f, pathY, -15.0f);

    glTexCoord2f(0.0f, 2.0f);
    glVertex3f(12.0f, pathY, -15.0f);

    glEnd();


    // Rear path.
    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-3.0f, pathY, -20.0f);

    glTexCoord2f(2.0f, 0.0f);
    glVertex3f(3.0f, pathY, -20.0f);

    glTexCoord2f(2.0f, 5.0f);
    glVertex3f(3.0f, pathY, -34.0f);

    glTexCoord2f(0.0f, 5.0f);
    glVertex3f(-3.0f, pathY, -34.0f);

    glEnd();


    // Other objects still use normal colours.
    glDisable(GL_TEXTURE_2D);
}


// -----------------------------------------------------------------------------
// Night sky
// -----------------------------------------------------------------------------

void drawNightSky()
{
    // Increase skySize if the sky walls become visible while moving around.
    const float skySize = 45.0f;

    // Controls how high the night sky extends above the carnival.
    const float skyHeight = 30.0f;

    // Keep the sky centered around the camera while the player moves.
    float cx = camera.x;
    float cz = camera.z;

    glColor3f(0.01f, 0.015f, 0.055f);

    glBegin(GL_QUADS);

    // Back sky wall.
    glVertex3f(cx - skySize, 0.0f, cz - skySize);
    glVertex3f(cx + skySize, 0.0f, cz - skySize);
    glVertex3f(cx + skySize, skyHeight, cz - skySize);
    glVertex3f(cx - skySize, skyHeight, cz - skySize);


    // Front sky wall.
    glVertex3f(cx + skySize, 0.0f, cz + skySize);
    glVertex3f(cx - skySize, 0.0f, cz + skySize);
    glVertex3f(cx - skySize, skyHeight, cz + skySize);
    glVertex3f(cx + skySize, skyHeight, cz + skySize);


    // Left sky wall.
    glVertex3f(cx - skySize, 0.0f, cz + skySize);
    glVertex3f(cx - skySize, 0.0f, cz - skySize);
    glVertex3f(cx - skySize, skyHeight, cz - skySize);
    glVertex3f(cx - skySize, skyHeight, cz + skySize);


    // Right sky wall.
    glVertex3f(cx + skySize, 0.0f, cz - skySize);
    glVertex3f(cx + skySize, 0.0f, cz + skySize);
    glVertex3f(cx + skySize, skyHeight, cz + skySize);
    glVertex3f(cx + skySize, skyHeight, cz - skySize);


    // Top sky surface makes the night sky visible when looking upward.
    glVertex3f(cx - skySize, skyHeight, cz - skySize);
    glVertex3f(cx + skySize, skyHeight, cz - skySize);
    glVertex3f(cx + skySize, skyHeight, cz + skySize);
    glVertex3f(cx - skySize, skyHeight, cz + skySize);

    glEnd();


    // -------------------------------------------------------------------------
    // Stars
    // -------------------------------------------------------------------------

    // Increase point size if the stars need to appear brighter or larger.
    glPointSize(2.0f);

    glColor3f(0.82f, 0.84f, 0.95f);

    glBegin(GL_POINTS);


    // Stars directly above the carnival.
    // Changing these X/Z offsets changes the star pattern.
    glVertex3f(cx - 36.0f, skyHeight - 0.1f, cz - 34.0f);
    glVertex3f(cx - 29.0f, skyHeight - 0.1f, cz - 18.0f);
    glVertex3f(cx - 31.0f, skyHeight - 0.1f, cz + 4.0f);
    glVertex3f(cx - 35.0f, skyHeight - 0.1f, cz + 24.0f);

    glVertex3f(cx - 23.0f, skyHeight - 0.1f, cz - 28.0f);
    glVertex3f(cx - 20.0f, skyHeight - 0.1f, cz - 8.0f);
    glVertex3f(cx - 24.0f, skyHeight - 0.1f, cz + 14.0f);
    glVertex3f(cx - 19.0f, skyHeight - 0.1f, cz + 32.0f);

    glVertex3f(cx - 12.0f, skyHeight - 0.1f, cz - 37.0f);
    glVertex3f(cx - 9.0f, skyHeight - 0.1f, cz - 20.0f);
    glVertex3f(cx - 14.0f, skyHeight - 0.1f, cz - 2.0f);
    glVertex3f(cx - 8.0f, skyHeight - 0.1f, cz + 19.0f);
    glVertex3f(cx - 13.0f, skyHeight - 0.1f, cz + 37.0f);

    glVertex3f(cx - 2.0f, skyHeight - 0.1f, cz - 30.0f);
    glVertex3f(cx + 1.0f, skyHeight - 0.1f, cz - 13.0f);
    glVertex3f(cx - 3.0f, skyHeight - 0.1f, cz + 7.0f);
    glVertex3f(cx + 3.0f, skyHeight - 0.1f, cz + 27.0f);

    glVertex3f(cx + 10.0f, skyHeight - 0.1f, cz - 38.0f);
    glVertex3f(cx + 13.0f, skyHeight - 0.1f, cz - 22.0f);
    glVertex3f(cx + 8.0f, skyHeight - 0.1f, cz - 5.0f);
    glVertex3f(cx + 14.0f, skyHeight - 0.1f, cz + 13.0f);
    glVertex3f(cx + 9.0f, skyHeight - 0.1f, cz + 34.0f);

    glVertex3f(cx + 21.0f, skyHeight - 0.1f, cz - 31.0f);
    glVertex3f(cx + 25.0f, skyHeight - 0.1f, cz - 13.0f);
    glVertex3f(cx + 20.0f, skyHeight - 0.1f, cz + 4.0f);
    glVertex3f(cx + 24.0f, skyHeight - 0.1f, cz + 23.0f);

    glVertex3f(cx + 33.0f, skyHeight - 0.1f, cz - 35.0f);
    glVertex3f(cx + 30.0f, skyHeight - 0.1f, cz - 18.0f);
    glVertex3f(cx + 35.0f, skyHeight - 0.1f, cz + 2.0f);
    glVertex3f(cx + 31.0f, skyHeight - 0.1f, cz + 31.0f);


    // Stars on the back horizon.
    glVertex3f(cx - 35.0f, 12.0f, cz - skySize + 0.1f);
    glVertex3f(cx - 29.0f, 21.0f, cz - skySize + 0.1f);
    glVertex3f(cx - 22.0f, 16.0f, cz - skySize + 0.1f);
    glVertex3f(cx - 15.0f, 25.0f, cz - skySize + 0.1f);
    glVertex3f(cx - 7.0f, 18.0f, cz - skySize + 0.1f);
    glVertex3f(cx + 1.0f, 23.0f, cz - skySize + 0.1f);
    glVertex3f(cx + 9.0f, 14.0f, cz - skySize + 0.1f);
    glVertex3f(cx + 16.0f, 27.0f, cz - skySize + 0.1f);
    glVertex3f(cx + 24.0f, 19.0f, cz - skySize + 0.1f);
    glVertex3f(cx + 33.0f, 24.0f, cz - skySize + 0.1f);


    // Stars on the front horizon.
    glVertex3f(cx - 32.0f, 17.0f, cz + skySize - 0.1f);
    glVertex3f(cx - 24.0f, 26.0f, cz + skySize - 0.1f);
    glVertex3f(cx - 16.0f, 14.0f, cz + skySize - 0.1f);
    glVertex3f(cx - 8.0f, 22.0f, cz + skySize - 0.1f);
    glVertex3f(cx + 4.0f, 18.0f, cz + skySize - 0.1f);
    glVertex3f(cx + 13.0f, 27.0f, cz + skySize - 0.1f);
    glVertex3f(cx + 21.0f, 15.0f, cz + skySize - 0.1f);
    glVertex3f(cx + 30.0f, 23.0f, cz + skySize - 0.1f);


    // Stars on the left side of the sky.
    glVertex3f(cx - skySize + 0.1f, 15.0f, cz - 32.0f);
    glVertex3f(cx - skySize + 0.1f, 24.0f, cz - 21.0f);
    glVertex3f(cx - skySize + 0.1f, 18.0f, cz - 8.0f);
    glVertex3f(cx - skySize + 0.1f, 27.0f, cz + 5.0f);
    glVertex3f(cx - skySize + 0.1f, 14.0f, cz + 18.0f);
    glVertex3f(cx - skySize + 0.1f, 22.0f, cz + 31.0f);


    // Stars on the right side of the sky.
    glVertex3f(cx + skySize - 0.1f, 21.0f, cz - 35.0f);
    glVertex3f(cx + skySize - 0.1f, 14.0f, cz - 23.0f);
    glVertex3f(cx + skySize - 0.1f, 26.0f, cz - 10.0f);
    glVertex3f(cx + skySize - 0.1f, 17.0f, cz + 4.0f);
    glVertex3f(cx + skySize - 0.1f, 24.0f, cz + 19.0f);
    glVertex3f(cx + skySize - 0.1f, 16.0f, cz + 34.0f);

    glEnd();
}


// -----------------------------------------------------------------------------
// Rotten wood surface
// -----------------------------------------------------------------------------

void drawRottenWoodCube()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, TextureManager::woodTexture);

    // Darken the wood slightly.
    glColor3f(0.62f, 0.56f, 0.50f);

    Primitives::drawTexturedCube(1.0f);

    glDisable(GL_TEXTURE_2D);
}


// -----------------------------------------------------------------------------
// Old stone surface
// -----------------------------------------------------------------------------

void drawOldStoneCube()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, TextureManager::stoneTexture);

    glColor3f(0.72f, 0.72f, 0.68f);

    Primitives::drawTexturedCube(1.0f);

    glDisable(GL_TEXTURE_2D);
}


// -----------------------------------------------------------------------------
// Haunted carnival sign
// -----------------------------------------------------------------------------

void drawCarnivalSign()
{
    // Whole sign position near the entrance.
    glPushMatrix();
    glTranslatef(-5.0f, 0.0f, 10.0f);
    glRotatef(8.0f, 0.0f, 1.0f, 0.0f);


    // Uneven stone base.
    glPushMatrix();
    glTranslatef(0.0f, 0.18f, 0.0f);
    glRotatef(-3.0f, 0.0f, 0.0f, 1.0f);
    glScalef(1.5f, 0.35f, 1.0f);

    drawOldStoneCube();

    glPopMatrix();


    // Main wooden post.
    glPushMatrix();
    glTranslatef(0.0f, 0.35f, 0.0f);
    glRotatef(-4.0f, 0.0f, 0.0f, 1.0f);

    glColor3f(0.18f, 0.07f, 0.03f);
    Primitives::drawCylinder(0.14f, 3.2f, 12);


    // Main sign board.
    glPushMatrix();
    glTranslatef(0.0f, 2.45f, 0.0f);
    glRotatef(-8.0f, 0.0f, 0.0f, 1.0f);
    glScalef(2.9f, 0.75f, 0.22f);

    drawRottenWoodCube();

    glPopMatrix();


    // Broken upper plank.
    glPushMatrix();
    glTranslatef(-0.25f, 2.95f, 0.0f);
    glRotatef(12.0f, 0.0f, 0.0f, 1.0f);
    glScalef(1.8f, 0.30f, 0.18f);

    drawRottenWoodCube();

    glPopMatrix();


    // Small broken side piece.
    glPushMatrix();
    glTranslatef(1.35f, 2.25f, 0.0f);
    glRotatef(-25.0f, 0.0f, 0.0f, 1.0f);
    glScalef(0.7f, 0.22f, 0.16f);

    drawRottenWoodCube();

    glPopMatrix();


    // Pointed ornament on top.
    glPushMatrix();
    glTranslatef(0.0f, 3.18f, 0.0f);

    drawRottenWoodCube();

    glPopMatrix();


    // Hanging cross piece.
    glPushMatrix();
    glTranslatef(-1.1f, 2.15f, 0.0f);
    glRotatef(6.0f, 0.0f, 0.0f, 1.0f);
    glScalef(0.12f, 0.9f, 0.12f);

    drawRottenWoodCube();

    glPopMatrix();


    glPopMatrix();

    glPopMatrix();
}


// -----------------------------------------------------------------------------
// Front fence
// -----------------------------------------------------------------------------

void drawFenceSection(float startX, float endX, float z)
{
    const float postSpacing = 2.0f;

    // Fence posts.
    for (float x = startX; x <= endX; x += postSpacing)
    {
        glPushMatrix();
        glTranslatef(x, 0.0f, z);

        glColor3f(0.14f, 0.06f, 0.03f);
        Primitives::drawCylinder(0.10f, 1.7f, 10);

        // Pointed top.
        glPushMatrix();
        glTranslatef(0.0f, 1.7f, 0.0f);

        glColor3f(0.20f, 0.07f, 0.04f);
        Primitives::drawCone(0.15f, 0.35f, 10);

        glPopMatrix();

        glPopMatrix();
    }


    float fenceLength = endX - startX;
    float centreX = (startX + endX) / 2.0f;

    // Lower horizontal rail.
    glPushMatrix();
    glTranslatef(centreX, 0.55f, z);
    glScalef(fenceLength, 0.12f, 0.12f);

    drawRottenWoodCube();

    glPopMatrix();


    // Upper horizontal rail.
    glPushMatrix();
    glTranslatef(centreX, 1.25f, z);
    glScalef(fenceLength, 0.12f, 0.12f);

    drawRottenWoodCube();

    glPopMatrix();
}


// -----------------------------------------------------------------------------
// Haunted carnival entrance gate
// -----------------------------------------------------------------------------

void drawEntranceGate()
{
    // Gate position across the main entrance path.
    const float gateZ = 5.0f;

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, gateZ);


    // Left gate post.
    glPushMatrix();
    glTranslatef(-3.2f, 0.0f, 0.0f);

    glColor3f(0.16f, 0.06f, 0.035f);
    Primitives::drawCylinder(0.28f, 4.2f, 12);

    // Pointed top.
    glPushMatrix();
    glTranslatef(0.0f, 4.2f, 0.0f);

    glColor3f(0.32f, 0.08f, 0.05f);
    Primitives::drawCone(0.38f, 0.8f, 12);

    glPopMatrix();

    glPopMatrix();


    // Right gate post.
    glPushMatrix();
    glTranslatef(3.2f, 0.0f, 0.0f);

    glColor3f(0.16f, 0.06f, 0.035f);
    Primitives::drawCylinder(0.28f, 4.2f, 12);

    glPushMatrix();
    glTranslatef(0.0f, 4.2f, 0.0f);

    glColor3f(0.32f, 0.08f, 0.05f);
    Primitives::drawCone(0.38f, 0.8f, 12);

    glPopMatrix();

    glPopMatrix();


    // Main beam above the entrance.
    glPushMatrix();
    glTranslatef(0.0f, 3.65f, 0.0f);
    glRotatef(-2.0f, 0.0f, 0.0f, 1.0f);
    glScalef(6.8f, 0.35f, 0.35f);

    drawRottenWoodCube();

    glPopMatrix();


    // Upper crooked beam.
    glPushMatrix();
    glTranslatef(0.0f, 4.25f, 0.0f);
    glRotatef(3.0f, 0.0f, 0.0f, 1.0f);
    glScalef(5.3f, 0.22f, 0.28f);

    drawRottenWoodCube();

    glPopMatrix();


    // Centre decoration.
    glPushMatrix();
    glTranslatef(0.0f, 4.2f, 0.0f);

    glColor3f(0.40f, 0.08f, 0.06f);
    Primitives::drawSphere(0.32f, 14, 14);

    glPopMatrix();


    // Three spikes above the gate.
    for (int i = -1; i <= 1; i++)
    {
        glPushMatrix();
        glTranslatef(i * 1.4f, 4.35f, 0.0f);

        glColor3f(0.28f, 0.07f, 0.05f);
        Primitives::drawCone(0.18f, 0.65f, 10);

        glPopMatrix();
    }


    // Hanging broken plank on the left side.
    glPushMatrix();
    glTranslatef(-1.7f, 3.35f, 0.0f);
    glRotatef(12.0f, 0.0f, 0.0f, 1.0f);
    glScalef(1.5f, 0.18f, 0.18f);

    drawRottenWoodCube();

    glPopMatrix();


    // Hanging broken plank on the right side.
    glPushMatrix();
    glTranslatef(1.6f, 3.30f, 0.0f);
    glRotatef(-10.0f, 0.0f, 0.0f, 1.0f);
    glScalef(1.3f, 0.18f, 0.18f);

    glColor3f(0.17f, 0.05f, 0.025f);
    Primitives::drawCube(1.0f);

    glPopMatrix();


    glPopMatrix();
}


// -----------------------------------------------------------------------------
// Carnival boundary
// -----------------------------------------------------------------------------

void drawCarnivalFence()
{
    // Leave the middle open for the entrance gate.
    drawFenceSection(-20.0f, -3.5f, 5.0f);
    drawFenceSection(3.5f, 20.0f, 5.0f);
}


// -----------------------------------------------------------------------------
// Tent ropes and stakes
// -----------------------------------------------------------------------------

void drawTentRope(float startX, float startY, float startZ,
    float endX, float endZ)
{
    glColor3f(0.17f, 0.15f, 0.12f);
    glLineWidth(1.5f);

    glBegin(GL_LINES);
    glVertex3f(startX, startY, startZ);
    glVertex3f(endX, 0.15f, endZ);
    glEnd();

    // Ground stake.
    glPushMatrix();
    glTranslatef(endX, 0.0f, endZ);

    glColor3f(0.12f, 0.05f, 0.025f);
    Primitives::drawCylinder(0.07f, 0.6f, 8);

    glPopMatrix();
}


// -----------------------------------------------------------------------------
// Red and gold horror tent
// -----------------------------------------------------------------------------

void drawRedHorrorTent()
{
    const float pi = 3.14159265f;

    const float radius = 6.0f;
    const float wallHeight = 4.2f;
    const float roofPeak = 9.5f;
    const int segments = 20;

    glPushMatrix();

    // Main tent position.
    glTranslatef(-25.0f, 0.0f, -13.0f);


    // Interior floor.
    glPushMatrix();
    glTranslatef(0.0f, 0.04f, 0.0f);
    glScalef(radius * 1.8f, 0.08f, radius * 1.8f);

    glColor3f(0.10f, 0.065f, 0.045f);
    Primitives::drawCube(1.0f);

    glPopMatrix();


    // -----------------------------------------------------------------------------
    // Textured tent walls
    // -----------------------------------------------------------------------------

    glEnable(GL_TEXTURE_2D);

    for (int i = 0; i < segments; i++)
    {
        // Keep the +X side open as the entrance.
        if (i == 0 || i == segments - 1)
            continue;

        float angle1 = 2.0f * pi * i / segments;
        float angle2 = 2.0f * pi * (i + 1) / segments;

        float x1 = radius * cosf(angle1);
        float z1 = radius * sinf(angle1);
        float x2 = radius * cosf(angle2);
        float z2 = radius * sinf(angle2);

        if (i % 2 == 0)
        {
            glBindTexture(GL_TEXTURE_2D, TextureManager::redClothTexture);
            glColor3f(0.60f, 0.60f, 0.60f);
        }
        else
        {
            glBindTexture(GL_TEXTURE_2D, TextureManager::dirtyClothTexture);
            glColor3f(0.65f, 0.62f, 0.55f);
        }

        glBegin(GL_QUADS);

        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(x1, 0.0f, z1);

        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(x2, 0.0f, z2);

        glTexCoord2f(1.0f, 2.5f);
        glVertex3f(x2, wallHeight, z2);

        glTexCoord2f(0.0f, 2.5f);
        glVertex3f(x1, wallHeight, z1);

        glEnd();
    }


    // -----------------------------------------------------------------------------
    // Textured tent roof
    // -----------------------------------------------------------------------------

    for (int i = 0; i < segments; i++)
    {
        float angle1 = 2.0f * pi * i / segments;
        float angle2 = 2.0f * pi * (i + 1) / segments;

        float x1 = radius * cosf(angle1);
        float z1 = radius * sinf(angle1);
        float x2 = radius * cosf(angle2);
        float z2 = radius * sinf(angle2);

        if (i % 2 == 0)
        {
            glBindTexture(GL_TEXTURE_2D, TextureManager::redClothTexture);
            glColor3f(0.55f, 0.55f, 0.55f);
        }
        else
        {
            glBindTexture(GL_TEXTURE_2D, TextureManager::dirtyClothTexture);
            glColor3f(0.60f, 0.57f, 0.50f);
        }

        glBegin(GL_TRIANGLES);

        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(x1, wallHeight, z1);

        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(x2, wallHeight, z2);

        glTexCoord2f(0.5f, 2.5f);
        glVertex3f(0.0f, roofPeak, 0.0f);

        glEnd();
    }

    glDisable(GL_TEXTURE_2D);


    // Tall front entrance.
    glPushMatrix();
    glTranslatef(5.8f, 3.2f, 0.0f);
    glScalef(0.35f, 6.4f, 4.2f);

    glColor3f(0.42f, 0.045f, 0.03f);
    Primitives::drawCube(1.0f);

    glPopMatrix();


    // Cut-out style entrance opening placed in front.
    glPushMatrix();
    glTranslatef(6.02f, 1.65f, 0.0f);
    glScalef(0.20f, 3.3f, 2.2f);

    glColor3f(0.008f, 0.006f, 0.006f);
    Primitives::drawCube(1.0f);

    glPopMatrix();


    // Entrance roof.
    glPushMatrix();
    glTranslatef(5.9f, 6.55f, 0.0f);
    glScalef(0.55f, 0.35f, 4.5f);

    glColor3f(0.22f, 0.025f, 0.02f);
    Primitives::drawCube(1.0f);

    glPopMatrix();


    // Centre mast.
    glPushMatrix();
    glTranslatef(0.0f, roofPeak, 0.0f);

    glColor3f(0.12f, 0.045f, 0.025f);
    Primitives::drawCylinder(0.11f, 1.5f, 10);

    glPopMatrix();


    // Torn top flag.
    glColor3f(0.48f, 0.035f, 0.025f);

    glBegin(GL_TRIANGLES);
    glVertex3f(0.05f, roofPeak + 1.35f, 0.0f);
    glVertex3f(1.7f, roofPeak + 1.05f, 0.0f);
    glVertex3f(0.05f, roofPeak + 0.75f, 0.0f);
    glEnd();


    // Ropes.
    drawTentRope(-4.0f, wallHeight, -4.0f, -8.0f, -8.0f);
    drawTentRope(-4.0f, wallHeight, 4.0f, -8.0f, 8.0f);
    drawTentRope(4.0f, wallHeight, -4.0f, 8.0f, -8.0f);
    drawTentRope(4.0f, wallHeight, 4.0f, 8.0f, 8.0f);

    glPopMatrix();
}


// -----------------------------------------------------------------------------
// Blue star horror tent
// -----------------------------------------------------------------------------

void drawBlueStarTent()
{
    const float pi = 3.14159265f;

    const float radius = 5.5f;
    const float wallHeight = 3.8f;
    const float roofPeak = 8.2f;
    const int segments = 18;

    glPushMatrix();

    // Rear-left tent.
    glTranslatef(-21.0f, 0.0f, -29.0f);


    // Interior floor.
    glPushMatrix();
    glTranslatef(0.0f, 0.04f, 0.0f);
    glScalef(radius * 1.8f, 0.08f, radius * 1.8f);

    glColor3f(0.065f, 0.06f, 0.07f);
    Primitives::drawCube(1.0f);

    glPopMatrix();


    // Multicolour lower cloth.
    for (int i = 0; i < segments; i++)
    {
        if (i == 0 || i == segments - 1)
            continue;

        float angle1 = 2.0f * pi * i / segments;
        float angle2 = 2.0f * pi * (i + 1) / segments;

        float x1 = radius * cosf(angle1);
        float z1 = radius * sinf(angle1);
        float x2 = radius * cosf(angle2);
        float z2 = radius * sinf(angle2);

        if (i % 3 == 0)
            glColor3f(0.12f, 0.30f, 0.24f);
        else if (i % 3 == 1)
            glColor3f(0.28f, 0.13f, 0.27f);
        else
            glColor3f(0.34f, 0.27f, 0.13f);

        glBegin(GL_QUADS);

        glVertex3f(x1, 0.0f, z1);
        glVertex3f(x2, 0.0f, z2);
        glVertex3f(x2, wallHeight, z2);
        glVertex3f(x1, wallHeight, z1);

        glEnd();
    }


    // Dark blue roof.
    for (int i = 0; i < segments; i++)
    {
        float angle1 = 2.0f * pi * i / segments;
        float angle2 = 2.0f * pi * (i + 1) / segments;

        float x1 = radius * cosf(angle1);
        float z1 = radius * sinf(angle1);
        float x2 = radius * cosf(angle2);
        float z2 = radius * sinf(angle2);

        if (i % 2 == 0)
            glColor3f(0.055f, 0.12f, 0.25f);
        else
            glColor3f(0.08f, 0.16f, 0.30f);

        glBegin(GL_TRIANGLES);

        glVertex3f(x1, wallHeight, z1);
        glVertex3f(x2, wallHeight, z2);
        glVertex3f(0.0f, roofPeak, 0.0f);

        glEnd();
    }


    // Entrance curtains.
    glPushMatrix();
    glTranslatef(5.15f, 1.8f, -1.25f);
    glRotatef(-8.0f, 1.0f, 0.0f, 0.0f);
    glScalef(0.22f, 3.6f, 1.8f);

    glColor3f(0.18f, 0.08f, 0.18f);
    Primitives::drawCube(1.0f);

    glPopMatrix();


    glPushMatrix();
    glTranslatef(5.15f, 1.8f, 1.25f);
    glRotatef(8.0f, 1.0f, 0.0f, 0.0f);
    glScalef(0.22f, 3.6f, 1.8f);

    glColor3f(0.12f, 0.20f, 0.18f);
    Primitives::drawCube(1.0f);

    glPopMatrix();


    // Top ornament.
    glPushMatrix();
    glTranslatef(0.0f, roofPeak, 0.0f);

    glColor3f(0.66f, 0.49f, 0.12f);
    Primitives::drawSphere(0.22f, 12, 10);

    glPopMatrix();


    drawTentRope(-3.8f, wallHeight, -3.8f, -7.5f, -7.5f);
    drawTentRope(-3.8f, wallHeight, 3.8f, -7.5f, 7.5f);
    drawTentRope(3.8f, wallHeight, -3.8f, 7.5f, -7.5f);
    drawTentRope(3.8f, wallHeight, 3.8f, 7.5f, 7.5f);

    glPopMatrix();
}


// -----------------------------------------------------------------------------
// Twin peak horror tent
// -----------------------------------------------------------------------------

void drawTwinPeakTent()
{
    const float pi = 3.14159265f;

    const float radius = 7.0f;
    const float wallHeight = 4.0f;
    const int segments = 20;

    glPushMatrix();

    // Rear carnival area.
    glTranslatef(-2.0f, 0.0f, -31.0f);


    // Interior floor.
    glPushMatrix();
    glTranslatef(0.0f, 0.04f, 0.0f);
    glScalef(radius * 1.8f, 0.08f, radius * 1.6f);

    glColor3f(0.085f, 0.065f, 0.06f);
    Primitives::drawCube(1.0f);

    glPopMatrix();


    // Red and cream side walls.
    for (int i = 0; i < segments; i++)
    {
        if (i == 0 || i == segments - 1)
            continue;

        float angle1 = 2.0f * pi * i / segments;
        float angle2 = 2.0f * pi * (i + 1) / segments;

        float x1 = radius * cosf(angle1);
        float z1 = 5.6f * sinf(angle1);
        float x2 = radius * cosf(angle2);
        float z2 = 5.6f * sinf(angle2);

        if (i % 2 == 0)
            glColor3f(0.60f, 0.075f, 0.055f);
        else
            glColor3f(0.62f, 0.56f, 0.43f);

        glBegin(GL_QUADS);

        glVertex3f(x1, 0.0f, z1);
        glVertex3f(x2, 0.0f, z2);
        glVertex3f(x2, wallHeight, z2);
        glVertex3f(x1, wallHeight, z1);

        glEnd();
    }


    // Left roof peak.
    for (int i = 0; i < segments; i++)
    {
        float angle1 = 2.0f * pi * i / segments;
        float angle2 = 2.0f * pi * (i + 1) / segments;

        float x1 = radius * cosf(angle1);
        float z1 = 5.6f * sinf(angle1);
        float x2 = radius * cosf(angle2);
        float z2 = 5.6f * sinf(angle2);

        if (i % 2 == 0)
            glColor3f(0.67f, 0.075f, 0.055f);
        else
            glColor3f(0.68f, 0.62f, 0.48f);

        glBegin(GL_TRIANGLES);

        glVertex3f(x1, wallHeight, z1);
        glVertex3f(x2, wallHeight, z2);
        glVertex3f(-2.1f, 9.7f, 0.0f);

        glEnd();
    }


    // Second higher peak overlay.
    for (int i = 0; i < segments; i += 2)
    {
        float angle1 = 2.0f * pi * i / segments;
        float angle2 = 2.0f * pi * (i + 2) / segments;

        float x1 = radius * cosf(angle1);
        float z1 = 5.6f * sinf(angle1);
        float x2 = radius * cosf(angle2);
        float z2 = 5.6f * sinf(angle2);

        glColor3f(0.50f, 0.055f, 0.045f);

        glBegin(GL_TRIANGLES);

        glVertex3f(x1, wallHeight, z1);
        glVertex3f(x2, wallHeight, z2);
        glVertex3f(2.3f, 10.5f, 0.0f);

        glEnd();
    }


    // Left peak cap.
    glPushMatrix();
    glTranslatef(-2.1f, 9.7f, 0.0f);

    glColor3f(0.48f, 0.045f, 0.035f);
    Primitives::drawCone(0.75f, 1.6f, 14);

    glPopMatrix();


    // Right peak cap.
    glPushMatrix();
    glTranslatef(2.3f, 10.5f, 0.0f);

    glColor3f(0.52f, 0.05f, 0.04f);
    Primitives::drawCone(0.75f, 1.6f, 14);

    glPopMatrix();


    // Rope between peaks.
    glColor3f(0.14f, 0.12f, 0.10f);
    glLineWidth(2.0f);

    glBegin(GL_LINES);
    glVertex3f(-2.1f, 11.1f, 0.0f);
    glVertex3f(2.3f, 11.9f, 0.0f);
    glEnd();


    // Entrance canopy.
    glPushMatrix();
    glTranslatef(6.6f, 2.6f, 0.0f);
    glScalef(0.35f, 5.2f, 3.5f);

    glColor3f(0.44f, 0.05f, 0.04f);
    Primitives::drawCube(1.0f);

    glPopMatrix();


    // Dark entrance.
    glPushMatrix();
    glTranslatef(6.82f, 1.5f, 0.0f);
    glScalef(0.18f, 3.0f, 2.0f);

    glColor3f(0.008f, 0.006f, 0.008f);
    Primitives::drawCube(1.0f);

    glPopMatrix();


    drawTentRope(-5.0f, wallHeight, -4.0f, -9.0f, -8.0f);
    drawTentRope(-5.0f, wallHeight, 4.0f, -9.0f, 8.0f);
    drawTentRope(5.0f, wallHeight, -4.0f, 9.0f, -8.0f);
    drawTentRope(5.0f, wallHeight, 4.0f, 9.0f, 8.0f);

    glPopMatrix();
}


// -----------------------------------------------------------------------------
// Horror tent area
// -----------------------------------------------------------------------------

void drawHorrorTents()
{
    drawRedHorrorTent();
    drawBlueStarTent();
    drawTwinPeakTent();
}


// -----------------------------------------------------------------------------
// Funhouse spiral decoration
// -----------------------------------------------------------------------------

void drawSpiralDisc(float radius)
{
    const float pi = 3.14159265f;
    const int segments = 48;

    // Faded carnival disc.
    glColor3f(0.68f, 0.57f, 0.28f);

    glBegin(GL_TRIANGLE_FAN);

    glVertex3f(0.0f, 0.0f, 0.0f);

    for (int i = 0; i <= segments; i++)
    {
        float angle = 2.0f * pi * i / segments;

        glVertex3f(radius * cosf(angle),
            radius * sinf(angle),
            0.0f);
    }

    glEnd();


    // Dark spiral over the disc.
    glLineWidth(5.0f);
    glColor3f(0.08f, 0.055f, 0.045f);

    glBegin(GL_LINE_STRIP);

    const int spiralPoints = 70;

    for (int i = 0; i < spiralPoints; i++)
    {
        float t = static_cast<float>(i) / (spiralPoints - 1);

        // About two full turns.
        float angle = t * 4.0f * pi;
        float spiralRadius = radius * 0.08f + radius * 0.78f * t;

        glVertex3f(spiralRadius * cosf(angle),
            spiralRadius * sinf(angle),
            0.03f);
    }

    glEnd();

    glLineWidth(1.0f);
}


// -----------------------------------------------------------------------------
// Funhouse bulb
// -----------------------------------------------------------------------------

void drawFunHouseBulb(float x, float y, float z)
{
    glPushMatrix();
    glTranslatef(x, y, z);

    glColor3f(0.82f, 0.68f, 0.30f);
    Primitives::drawSphere(0.10f, 10, 10);

    glPopMatrix();
}


// -----------------------------------------------------------------------------
// Haunted funhouse
// -----------------------------------------------------------------------------

void drawHauntedFunHouse()
{
    // Building size.
    const float houseWidth = 12.0f;
    const float houseDepth = 14.0f;
    const float wallHeight = 6.0f;

    // Right side of the carnival.
    glPushMatrix();
    glTranslatef(26.0f, 0.0f, -12.5f);

    // Front faces the side path.
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);


    // -------------------------------------------------------------------------
    // Interior floor
    // -------------------------------------------------------------------------

    glPushMatrix();
    glTranslatef(0.0f, 0.04f, 0.0f);
    glScalef(houseWidth, 0.08f, houseDepth);

    glColor3f(0.10f, 0.075f, 0.055f);
    Primitives::drawCube(1.0f);

    glPopMatrix();


    // -------------------------------------------------------------------------
    // Side walls
    // -------------------------------------------------------------------------

    glPushMatrix();
    glTranslatef(-houseWidth / 2.0f, wallHeight / 2.0f, 0.0f);
    glScalef(0.25f, wallHeight, houseDepth);

    glColor3f(0.085f, 0.075f, 0.075f);
    Primitives::drawCube(1.0f);

    glPopMatrix();


    glPushMatrix();
    glTranslatef(houseWidth / 2.0f, wallHeight / 2.0f, 0.0f);
    glScalef(0.25f, wallHeight, houseDepth);

    glColor3f(0.085f, 0.075f, 0.075f);
    Primitives::drawCube(1.0f);

    glPopMatrix();


    // -------------------------------------------------------------------------
    // Back wall
    // -------------------------------------------------------------------------

    glPushMatrix();
    glTranslatef(0.0f, wallHeight / 2.0f, -houseDepth / 2.0f);
    glScalef(houseWidth, wallHeight, 0.25f);

    glColor3f(0.075f, 0.065f, 0.07f);
    Primitives::drawCube(1.0f);

    glPopMatrix();


    // -------------------------------------------------------------------------
    // Front wall around the entrance
    // -------------------------------------------------------------------------

    // Left side of doorway.
    glPushMatrix();
    glTranslatef(-4.0f, wallHeight / 2.0f, houseDepth / 2.0f);
    glScalef(4.0f, wallHeight, 0.28f);

    glColor3f(0.10f, 0.08f, 0.075f);
    Primitives::drawCube(1.0f);

    glPopMatrix();


    // Right side of doorway.
    glPushMatrix();
    glTranslatef(4.0f, wallHeight / 2.0f, houseDepth / 2.0f);
    glScalef(4.0f, wallHeight, 0.28f);

    glColor3f(0.10f, 0.08f, 0.075f);
    Primitives::drawCube(1.0f);

    glPopMatrix();


    // Wall above doorway.
    glPushMatrix();
    glTranslatef(0.0f, 5.0f, houseDepth / 2.0f);
    glScalef(4.0f, 2.0f, 0.28f);

    glColor3f(0.095f, 0.075f, 0.07f);
    Primitives::drawCube(1.0f);

    glPopMatrix();


    // -------------------------------------------------------------------------
    // Roof
    // -------------------------------------------------------------------------

    glPushMatrix();
    glTranslatef(-3.0f, 6.7f, 0.0f);
    glRotatef(-14.0f, 0.0f, 0.0f, 1.0f);
    glScalef(6.8f, 0.30f, 14.6f);

    glColor3f(0.07f, 0.035f, 0.035f);
    Primitives::drawCube(1.0f);

    glPopMatrix();


    glPushMatrix();
    glTranslatef(3.0f, 6.7f, 0.0f);
    glRotatef(14.0f, 0.0f, 0.0f, 1.0f);
    glScalef(6.8f, 0.30f, 14.6f);

    glColor3f(0.065f, 0.03f, 0.03f);
    Primitives::drawCube(1.0f);

    glPopMatrix();


    // -------------------------------------------------------------------------
    // Interior partitions
    // -------------------------------------------------------------------------

    // Partial wall leaves space to walk around both sides.
    glPushMatrix();
    glTranslatef(-3.0f, 1.6f, -1.3f);
    glScalef(0.22f, 3.2f, 5.0f);

    glColor3f(0.11f, 0.085f, 0.075f);
    Primitives::drawCube(1.0f);

    glPopMatrix();


    // Second hiding area deeper inside.
    glPushMatrix();
    glTranslatef(2.8f, 1.6f, -3.8f);
    glScalef(0.22f, 3.2f, 4.0f);

    glColor3f(0.10f, 0.075f, 0.07f);
    Primitives::drawCube(1.0f);

    glPopMatrix();


    // -------------------------------------------------------------------------
    // Gold side panels
    // -------------------------------------------------------------------------

    glColor3f(0.45f, 0.28f, 0.08f);

    // Left wing.
    glBegin(GL_QUADS);

    glVertex3f(-8.0f, 0.5f, 7.30f);
    glVertex3f(-2.5f, 0.5f, 7.30f);
    glVertex3f(-2.8f, 5.1f, 7.30f);
    glVertex3f(-7.2f, 4.2f, 7.30f);

    glEnd();


    // Right wing.
    glBegin(GL_QUADS);

    glVertex3f(2.5f, 0.5f, 7.30f);
    glVertex3f(8.0f, 0.5f, 7.30f);
    glVertex3f(7.2f, 4.2f, 7.30f);
    glVertex3f(2.8f, 5.1f, 7.30f);

    glEnd();


    // -------------------------------------------------------------------------
    // Clown cheeks
    // -------------------------------------------------------------------------

    glPushMatrix();
    glTranslatef(-2.45f, 2.25f, 7.55f);
    glRotatef(-5.0f, 0.0f, 0.0f, 1.0f);
    glScalef(1.35f, 4.2f, 0.45f);

    glColor3f(0.39f, 0.30f, 0.22f);
    Primitives::drawCube(1.0f);

    glPopMatrix();


    glPushMatrix();
    glTranslatef(2.45f, 2.25f, 7.55f);
    glRotatef(5.0f, 0.0f, 0.0f, 1.0f);
    glScalef(1.35f, 4.2f, 0.45f);

    glColor3f(0.39f, 0.30f, 0.22f);
    Primitives::drawCube(1.0f);

    glPopMatrix();


    // -------------------------------------------------------------------------
    // Clown head
    // -------------------------------------------------------------------------

    glPushMatrix();
    glTranslatef(0.0f, 6.0f, 7.45f);
    glScalef(3.4f, 2.5f, 0.65f);

    glColor3f(0.43f, 0.39f, 0.33f);
    Primitives::drawSphere(1.0f, 24, 20);

    glPopMatrix();


    // -------------------------------------------------------------------------
    // Spiral decorations
    // -------------------------------------------------------------------------

    glPushMatrix();
    glTranslatef(-4.5f, 6.5f, 7.55f);
    glRotatef(-8.0f, 0.0f, 0.0f, 1.0f);

    drawSpiralDisc(1.65f);

    glPopMatrix();


    glPushMatrix();
    glTranslatef(4.5f, 6.5f, 7.55f);
    glRotatef(8.0f, 0.0f, 0.0f, 1.0f);

    drawSpiralDisc(1.65f);

    glPopMatrix();


    // -------------------------------------------------------------------------
    // Eye sockets
    // -------------------------------------------------------------------------

    glPushMatrix();
    glTranslatef(-1.25f, 6.15f, 8.05f);
    glRotatef(-12.0f, 0.0f, 0.0f, 1.0f);
    glScalef(0.85f, 0.55f, 0.25f);

    glColor3f(0.015f, 0.01f, 0.012f);
    Primitives::drawSphere(1.0f, 18, 14);

    glPopMatrix();


    glPushMatrix();
    glTranslatef(1.25f, 6.15f, 8.05f);
    glRotatef(12.0f, 0.0f, 0.0f, 1.0f);
    glScalef(0.85f, 0.55f, 0.25f);

    glColor3f(0.015f, 0.01f, 0.012f);
    Primitives::drawSphere(1.0f, 18, 14);

    glPopMatrix();


    // Red eyes.
    glPushMatrix();
    glTranslatef(-1.15f, 6.05f, 8.28f);
    glScalef(0.30f, 0.18f, 0.12f);

    glColor3f(0.65f, 0.02f, 0.015f);
    Primitives::drawSphere(1.0f, 12, 10);

    glPopMatrix();


    glPushMatrix();
    glTranslatef(1.15f, 6.05f, 8.28f);
    glScalef(0.30f, 0.18f, 0.12f);

    glColor3f(0.65f, 0.02f, 0.015f);
    Primitives::drawSphere(1.0f, 12, 10);

    glPopMatrix();


    // -------------------------------------------------------------------------
    // Red clown nose
    // -------------------------------------------------------------------------

    glPushMatrix();
    glTranslatef(0.0f, 5.25f, 8.35f);

    glColor3f(0.68f, 0.035f, 0.025f);
    Primitives::drawSphere(0.62f, 18, 16);

    glPopMatrix();


    // Small lower nose pieces.
    glPushMatrix();
    glTranslatef(-0.38f, 4.95f, 8.25f);

    glColor3f(0.50f, 0.025f, 0.02f);
    Primitives::drawSphere(0.25f, 12, 10);

    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.38f, 4.95f, 8.25f);

    glColor3f(0.50f, 0.025f, 0.02f);
    Primitives::drawSphere(0.25f, 12, 10);

    glPopMatrix();


    // -------------------------------------------------------------------------
    // Mouth entrance
    // -------------------------------------------------------------------------

    // Upper lip.
    glPushMatrix();
    glTranslatef(0.0f, 4.15f, 7.85f);
    glRotatef(-2.0f, 0.0f, 0.0f, 1.0f);
    glScalef(4.1f, 0.35f, 0.40f);

    glColor3f(0.16f, 0.06f, 0.045f);
    Primitives::drawCube(1.0f);

    glPopMatrix();


    // Mouth side frames.
    glPushMatrix();
    glTranslatef(-2.0f, 2.0f, 7.85f);
    glRotatef(-5.0f, 0.0f, 0.0f, 1.0f);
    glScalef(0.38f, 4.0f, 0.42f);

    glColor3f(0.19f, 0.07f, 0.05f);
    Primitives::drawCube(1.0f);

    glPopMatrix();


    glPushMatrix();
    glTranslatef(2.0f, 2.0f, 7.85f);
    glRotatef(5.0f, 0.0f, 0.0f, 1.0f);
    glScalef(0.38f, 4.0f, 0.42f);

    glColor3f(0.19f, 0.07f, 0.05f);
    Primitives::drawCube(1.0f);

    glPopMatrix();


    // -------------------------------------------------------------------------
    // Upper teeth
    // -------------------------------------------------------------------------

    for (int i = -2; i <= 2; i++)
    {
        glPushMatrix();
        glTranslatef(i * 0.65f, 3.95f, 8.08f);

        // Teeth point downward.
        glRotatef(180.0f, 1.0f, 0.0f, 0.0f);

        glColor3f(0.70f, 0.65f, 0.50f);
        Primitives::drawCone(0.16f, 0.55f, 8);

        glPopMatrix();
    }


    // -------------------------------------------------------------------------
    // Lower teeth
    // -------------------------------------------------------------------------

    for (int i = -2; i <= 2; i++)
    {
        glPushMatrix();
        glTranslatef(i * 0.65f, 0.12f, 8.08f);

        glColor3f(0.62f, 0.57f, 0.45f);
        Primitives::drawCone(0.14f, 0.45f, 8);

        glPopMatrix();
    }


    // -------------------------------------------------------------------------
    // Carnival bulbs
    // -------------------------------------------------------------------------

    for (int i = 0; i < 7; i++)
    {
        float x = -7.1f + i * 0.70f;
        float y = 1.0f + i * 0.42f;

        drawFunHouseBulb(x, y, 7.50f);
    }


    for (int i = 0; i < 7; i++)
    {
        float x = 7.1f - i * 0.70f;
        float y = 1.0f + i * 0.42f;

        drawFunHouseBulb(x, y, 7.50f);
    }


    // Bulbs around the mouth.
    for (int i = -2; i <= 2; i++)
        drawFunHouseBulb(i * 0.75f, 4.45f, 8.10f);


    // -------------------------------------------------------------------------
    // Funhouse sign
    // -------------------------------------------------------------------------

    glPushMatrix();
    glTranslatef(0.0f, 8.45f, 7.55f);
    glRotatef(-2.0f, 0.0f, 0.0f, 1.0f);
    glScalef(4.2f, 0.75f, 0.30f);

    glColor3f(0.22f, 0.07f, 0.045f);
    Primitives::drawCube(1.0f);

    glPopMatrix();


    // Sign supports.
    for (int i = -1; i <= 1; i++)
    {
        glPushMatrix();
        glTranslatef(i * 1.3f, 7.55f, 7.40f);
        glScalef(0.13f, 1.8f, 0.13f);

        glColor3f(0.13f, 0.055f, 0.03f);
        Primitives::drawCube(1.0f);

        glPopMatrix();
    }


    glPopMatrix();
}


// -----------------------------------------------------------------------------
// Old carnival bench
// -----------------------------------------------------------------------------

void drawBench()
{
    // Seat planks.
    for (int i = -1; i <= 1; i++)
    {
        glPushMatrix();
        glTranslatef(0.0f, 0.78f, i * 0.25f);
        glScalef(3.2f, 0.13f, 0.20f);

        glColor3f(0.18f + i * 0.01f, 0.065f, 0.025f);
        Primitives::drawCube(1.0f);

        glPopMatrix();
    }


    // Back planks.
    for (int i = 0; i < 3; i++)
    {
        glPushMatrix();

        glTranslatef(0.0f, 1.15f + i * 0.30f, -0.42f);
        glRotatef(-8.0f, 1.0f, 0.0f, 0.0f);
        glScalef(3.2f, 0.16f, 0.12f);

        glColor3f(0.16f, 0.055f, 0.022f);
        Primitives::drawCube(1.0f);

        glPopMatrix();
    }


    // Metal legs.
    for (int i = -1; i <= 1; i += 2)
    {
        glPushMatrix();
        glTranslatef(i * 1.15f, 0.0f, -0.25f);

        glColor3f(0.07f, 0.065f, 0.06f);
        Primitives::drawCylinder(0.09f, 0.76f, 8);

        glPopMatrix();


        glPushMatrix();
        glTranslatef(i * 1.15f, 0.0f, 0.25f);

        glColor3f(0.07f, 0.065f, 0.06f);
        Primitives::drawCylinder(0.09f, 0.76f, 8);

        glPopMatrix();
    }


    // Broken arm rests.
    glPushMatrix();
    glTranslatef(-1.55f, 1.0f, 0.0f);
    glRotatef(-8.0f, 0.0f, 0.0f, 1.0f);
    glScalef(0.12f, 0.65f, 0.75f);

    glColor3f(0.10f, 0.045f, 0.02f);
    Primitives::drawCube(1.0f);

    glPopMatrix();


    glPushMatrix();
    glTranslatef(1.55f, 0.93f, 0.0f);
    glRotatef(5.0f, 0.0f, 0.0f, 1.0f);
    glScalef(0.12f, 0.52f, 0.75f);

    glColor3f(0.10f, 0.045f, 0.02f);
    Primitives::drawCube(1.0f);

    glPopMatrix();
}


// -----------------------------------------------------------------------------
// Haunted lamp post
// -----------------------------------------------------------------------------

void drawLampPost()
{
    // Heavy base.
    glPushMatrix();
    glTranslatef(0.0f, 0.15f, 0.0f);
    glScalef(0.75f, 0.30f, 0.75f);

    glColor3f(0.065f, 0.06f, 0.055f);
    Primitives::drawCube(1.0f);

    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.0f, 0.3f, 0.0f);

    glColor3f(0.08f, 0.075f, 0.07f);
    Primitives::drawCylinder(0.22f, 0.55f, 12);

    glPopMatrix();


    // Main pole.
    glPushMatrix();
    glTranslatef(0.0f, 0.65f, 0.0f);

    glColor3f(0.065f, 0.06f, 0.058f);
    Primitives::drawCylinder(0.10f, 3.7f, 12);

    glPopMatrix();


    // Decorative ring.
    glPushMatrix();
    glTranslatef(0.0f, 3.85f, 0.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);

    glColor3f(0.10f, 0.085f, 0.07f);
    glutSolidTorus(0.05f, 0.18f, 8, 16);

    glPopMatrix();


    // Crooked arm.
    glPushMatrix();
    glTranslatef(0.45f, 4.15f, 0.0f);
    glRotatef(-10.0f, 0.0f, 0.0f, 1.0f);
    glScalef(1.15f, 0.10f, 0.10f);

    glColor3f(0.065f, 0.06f, 0.055f);
    Primitives::drawCube(1.0f);

    glPopMatrix();


    // Lantern bottom.
    glPushMatrix();
    glTranslatef(1.0f, 3.72f, 0.0f);
    glScalef(0.65f, 0.10f, 0.65f);

    glColor3f(0.075f, 0.065f, 0.055f);
    Primitives::drawCube(1.0f);

    glPopMatrix();


    // Lantern frame.
    const float lanternX[4] = { -0.25f, 0.25f, -0.25f, 0.25f };
    const float lanternZ[4] = { -0.25f, -0.25f, 0.25f, 0.25f };

    for (int i = 0; i < 4; i++)
    {
        glPushMatrix();

        glTranslatef(1.0f + lanternX[i], 3.75f, lanternZ[i]);

        glColor3f(0.08f, 0.07f, 0.06f);
        Primitives::drawCylinder(0.025f, 0.75f, 6);

        glPopMatrix();
    }


    // Warm bulb.
    glPushMatrix();
    glTranslatef(1.0f, 4.05f, 0.0f);

    glColor3f(0.90f, 0.48f, 0.10f);
    Primitives::drawSphere(0.22f, 12, 10);

    glPopMatrix();


    // Lantern roof.
    glPushMatrix();
    glTranslatef(1.0f, 4.50f, 0.0f);

    glColor3f(0.07f, 0.06f, 0.055f);
    Primitives::drawCone(0.48f, 0.5f, 4);

    glPopMatrix();
}


// -----------------------------------------------------------------------------
// Old gravestone
// -----------------------------------------------------------------------------

void drawGravestone()
{
    glPushMatrix();
    glTranslatef(0.0f, 0.12f, 0.0f);
    glScalef(1.10f, 0.24f, 0.65f);

    glColor3f(0.19f, 0.19f, 0.19f);
    Primitives::drawCube(1.0f);

    glPopMatrix();


    // Main stone.
    glPushMatrix();
    glTranslatef(0.0f, 0.95f, 0.0f);
    glRotatef(-5.0f, 0.0f, 0.0f, 1.0f);
    glScalef(0.85f, 1.55f, 0.32f);

    glColor3f(0.23f, 0.23f, 0.22f);
    Primitives::drawCube(1.0f);

    glPopMatrix();


    // Rounded top.
    glPushMatrix();
    glTranslatef(-0.06f, 1.72f, 0.0f);
    glScalef(0.46f, 0.44f, 0.21f);

    glColor3f(0.23f, 0.23f, 0.22f);
    Primitives::drawSphere(1.0f, 14, 10);

    glPopMatrix();


    // Small engraved cross.
    glPushMatrix();
    glTranslatef(-0.06f, 1.12f, 0.18f);
    glScalef(0.09f, 0.55f, 0.05f);

    glColor3f(0.12f, 0.12f, 0.11f);
    Primitives::drawCube(1.0f);

    glPopMatrix();


    glPushMatrix();
    glTranslatef(-0.06f, 1.22f, 0.18f);
    glScalef(0.40f, 0.08f, 0.05f);

    glColor3f(0.12f, 0.12f, 0.11f);
    Primitives::drawCube(1.0f);

    glPopMatrix();
}




// -----------------------------------------------------------------------------
// Cross gravestone
// -----------------------------------------------------------------------------

void drawCrossGravestone()
{
    glPushMatrix();
    glTranslatef(0.0f, 0.15f, 0.0f);
    glScalef(1.2f, 0.30f, 0.7f);

    drawOldStoneCube();

    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.0f, 1.15f, 0.0f);
    glScalef(0.38f, 2.0f, 0.32f);

    drawOldStoneCube();

    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.0f, 1.55f, 0.0f);
    glScalef(1.3f, 0.34f, 0.32f);

    drawOldStoneCube();

    glPopMatrix();
}


// -----------------------------------------------------------------------------
// Pumpkin
// -----------------------------------------------------------------------------

void drawPumpkin()
{
    // Overlapping sections make the pumpkin less spherical.
    for (int i = 0; i < 6; i++)
    {
        float angle = i * 60.0f;

        glPushMatrix();

        glTranslatef(0.0f, 0.45f, 0.0f);
        glRotatef(angle, 0.0f, 1.0f, 0.0f);
        glScalef(0.68f, 0.52f, 0.48f);

        glColor3f(0.53f, 0.16f, 0.018f);
        Primitives::drawSphere(1.0f, 12, 10);

        glPopMatrix();
    }


    // Stem.
    glPushMatrix();
    glTranslatef(0.0f, 0.91f, 0.0f);
    glRotatef(-12.0f, 0.0f, 0.0f, 1.0f);

    glColor3f(0.09f, 0.12f, 0.035f);
    Primitives::drawCylinder(0.07f, 0.32f, 7);

    glPopMatrix();


    // Dark carved eyes.
    glColor3f(0.03f, 0.012f, 0.005f);

    glBegin(GL_TRIANGLES);

    glVertex3f(-0.35f, 0.58f, 0.53f);
    glVertex3f(-0.08f, 0.60f, 0.53f);
    glVertex3f(-0.20f, 0.36f, 0.54f);

    glVertex3f(0.08f, 0.60f, 0.53f);
    glVertex3f(0.35f, 0.58f, 0.53f);
    glVertex3f(0.20f, 0.36f, 0.54f);

    glEnd();
}


// -----------------------------------------------------------------------------
// Skull
// -----------------------------------------------------------------------------

void drawSkull()
{
    // Cranium.
    glPushMatrix();
    glTranslatef(0.0f, 0.65f, 0.0f);
    glScalef(0.55f, 0.65f, 0.50f);

    glColor3f(0.63f, 0.60f, 0.49f);
    Primitives::drawSphere(1.0f, 18, 14);

    glPopMatrix();


    // Jaw.
    glPushMatrix();
    glTranslatef(0.0f, 0.24f, 0.08f);
    glScalef(0.65f, 0.32f, 0.46f);

    glColor3f(0.56f, 0.53f, 0.44f);
    Primitives::drawCube(1.0f);

    glPopMatrix();


    // Eye sockets.
    for (int i = -1; i <= 1; i += 2)
    {
        glPushMatrix();

        glTranslatef(i * 0.22f, 0.68f, 0.44f);
        glScalef(0.17f, 0.22f, 0.10f);

        glColor3f(0.018f, 0.012f, 0.008f);
        Primitives::drawSphere(1.0f, 10, 8);

        glPopMatrix();
    }


    // Nose hole.
    glPushMatrix();
    glTranslatef(0.0f, 0.49f, 0.48f);
    glScalef(0.10f, 0.13f, 0.06f);

    glColor3f(0.02f, 0.012f, 0.008f);
    Primitives::drawSphere(1.0f, 8, 6);

    glPopMatrix();


    // Teeth.
    for (int i = -2; i <= 2; i++)
    {
        glPushMatrix();

        glTranslatef(i * 0.10f, 0.30f, 0.33f);
        glScalef(0.07f, 0.17f, 0.05f);

        glColor3f(0.68f, 0.65f, 0.53f);
        Primitives::drawCube(1.0f);

        glPopMatrix();
    }
}


// -----------------------------------------------------------------------------
// Bone
// -----------------------------------------------------------------------------

void drawBone()
{
    glPushMatrix();
    glRotatef(90.0f, 0.0f, 0.0f, 1.0f);

    glColor3f(0.58f, 0.55f, 0.46f);
    Primitives::drawCylinder(0.07f, 0.9f, 8);

    glPopMatrix();


    for (int i = -1; i <= 1; i += 2)
    {
        glPushMatrix();
        glTranslatef(i * 0.45f, 0.0f, 0.0f);

        glColor3f(0.60f, 0.57f, 0.48f);
        Primitives::drawSphere(0.13f, 8, 6);

        glPopMatrix();
    }
}


// -----------------------------------------------------------------------------
// Dirty wooden crate
// -----------------------------------------------------------------------------

void drawCrate()
{
    // Main box.
    glPushMatrix();
    glTranslatef(0.0f, 0.65f, 0.0f);
    glScalef(1.3f, 1.3f, 1.3f);

    glColor3f(0.17f, 0.075f, 0.025f);
    Primitives::drawCube(1.0f);

    glPopMatrix();


    // Front slats.
    for (int i = -1; i <= 1; i++)
    {
        glPushMatrix();
        glTranslatef(i * 0.43f, 0.65f, 0.67f);
        glScalef(0.10f, 1.20f, 0.08f);

        glColor3f(0.27f, 0.12f, 0.035f);
        Primitives::drawCube(1.0f);

        glPopMatrix();
    }


    // Crossed boards.
    glPushMatrix();
    glTranslatef(0.0f, 0.65f, 0.72f);
    glRotatef(42.0f, 0.0f, 0.0f, 1.0f);
    glScalef(0.10f, 1.55f, 0.08f);

    glColor3f(0.24f, 0.10f, 0.03f);
    Primitives::drawCube(1.0f);

    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.0f, 0.65f, 0.73f);
    glRotatef(-42.0f, 0.0f, 0.0f, 1.0f);
    glScalef(0.10f, 1.55f, 0.08f);

    glColor3f(0.22f, 0.09f, 0.028f);
    Primitives::drawCube(1.0f);

    glPopMatrix();


    // Loose broken lid.
    glPushMatrix();
    glTranslatef(0.25f, 1.45f, -0.05f);
    glRotatef(-15.0f, 0.0f, 0.0f, 1.0f);
    glRotatef(12.0f, 1.0f, 0.0f, 0.0f);
    glScalef(1.1f, 0.10f, 1.2f);

    glColor3f(0.20f, 0.08f, 0.025f);
    Primitives::drawCube(1.0f);

    glPopMatrix();
}


// -----------------------------------------------------------------------------
// Old barrel
// -----------------------------------------------------------------------------

void drawBarrel()
{
    // Wooden body.
    glPushMatrix();

    glColor3f(0.20f, 0.085f, 0.028f);
    Primitives::drawCylinder(0.55f, 1.35f, 14);

    glPopMatrix();


    // Metal rings.
    const float ringHeights[3] = { 0.18f, 0.67f, 1.16f };

    for (int i = 0; i < 3; i++)
    {
        glPushMatrix();

        glTranslatef(0.0f, ringHeights[i], 0.0f);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);

        glColor3f(0.075f, 0.07f, 0.065f);
        glutSolidTorus(0.045f, 0.55f, 8, 16);

        glPopMatrix();
    }
}


// -----------------------------------------------------------------------------
// Grass clump
// -----------------------------------------------------------------------------

void drawGrassClump()
{
    glColor3f(0.08f, 0.12f, 0.055f);

    glBegin(GL_TRIANGLES);

    glVertex3f(-0.25f, 0.0f, 0.0f);
    glVertex3f(-0.05f, 0.0f, 0.0f);
    glVertex3f(-0.13f, 0.85f, 0.0f);

    glVertex3f(0.0f, 0.0f, 0.05f);
    glVertex3f(0.18f, 0.0f, 0.05f);
    glVertex3f(0.08f, 0.65f, 0.05f);

    glVertex3f(-0.08f, 0.0f, -0.15f);
    glVertex3f(0.08f, 0.0f, -0.15f);
    glVertex3f(0.02f, 0.72f, -0.15f);

    glEnd();
}


// -----------------------------------------------------------------------------
// Blood stain
// -----------------------------------------------------------------------------

void drawBloodStain(float size)
{
    // Slightly above the ground.
    glColor3f(0.20f, 0.008f, 0.006f);

    glBegin(GL_POLYGON);

    glVertex3f(-1.0f * size, 0.025f, -0.25f * size);
    glVertex3f(-0.55f * size, 0.025f, -0.80f * size);
    glVertex3f(0.10f * size, 0.025f, -0.65f * size);
    glVertex3f(0.75f * size, 0.025f, -0.90f * size);
    glVertex3f(1.05f * size, 0.025f, -0.20f * size);
    glVertex3f(0.65f * size, 0.025f, 0.50f * size);
    glVertex3f(0.05f * size, 0.025f, 0.80f * size);
    glVertex3f(-0.70f * size, 0.025f, 0.45f * size);

    glEnd();


    // Small drops beside the main stain.
    glPointSize(5.0f);

    glBegin(GL_POINTS);

    glVertex3f(1.3f * size, 0.027f, 0.15f * size);
    glVertex3f(1.55f * size, 0.027f, 0.35f * size);
    glVertex3f(-1.25f * size, 0.027f, -0.65f * size);

    glEnd();

    glPointSize(1.0f);
}


// -----------------------------------------------------------------------------
// Water puddle
// -----------------------------------------------------------------------------

void drawWaterPuddle(float size)
{
    glColor3f(0.035f, 0.055f, 0.065f);

    glBegin(GL_POLYGON);

    glVertex3f(-1.2f * size, 0.02f, -0.3f * size);
    glVertex3f(-0.8f * size, 0.02f, -0.8f * size);
    glVertex3f(-0.1f * size, 0.02f, -0.65f * size);
    glVertex3f(0.8f * size, 0.02f, -0.9f * size);
    glVertex3f(1.25f * size, 0.02f, -0.2f * size);
    glVertex3f(0.7f * size, 0.02f, 0.55f * size);
    glVertex3f(-0.25f * size, 0.02f, 0.75f * size);
    glVertex3f(-0.9f * size, 0.02f, 0.45f * size);

    glEnd();
}


// -----------------------------------------------------------------------------
// Broken wooden plank
// -----------------------------------------------------------------------------

void drawBrokenPlank()
{
    glPushMatrix();
    glScalef(1.8f, 0.12f, 0.32f);

    glColor3f(0.14f, 0.055f, 0.018f);
    Primitives::drawCube(1.0f);

    glPopMatrix();
}


// -----------------------------------------------------------------------------
// Environment props
// -----------------------------------------------------------------------------

void drawEnvironmentProps()
{
    // -------------------------------------------------------------------------
    // Dead trees
    // -------------------------------------------------------------------------

    const float treePositions[10][3] =
    {
        {-9.0f, 0.0f,  2.0f},
        {10.0f, 0.0f,  1.5f},
        {-14.0f, 0.0f, -21.0f},
        {14.0f, 0.0f, -21.5f},
        {-34.0f, 0.0f, -21.0f},
        {-33.0f, 0.0f, -33.0f},
        {18.0f, 0.0f, -28.0f},
        {21.0f, 0.0f, -2.0f},
        {-17.0f, 0.0f, 2.0f},
        {31.0f, 0.0f, -25.0f}
    };

    for (int i = 0; i < 10; i++)
    {
        glPushMatrix();

        glTranslatef(treePositions[i][0], 0.0f, treePositions[i][2]);
        glRotatef(i * 31.0f, 0.0f, 1.0f, 0.0f);

        float scale = 0.85f + (i % 3) * 0.15f;
        glScalef(scale, scale, scale);

        HauntedTree::draw(static_cast<float>(i));

        glPopMatrix();
    }


    // -------------------------------------------------------------------------
    // Benches
    // -------------------------------------------------------------------------

    glPushMatrix();
    glTranslatef(-9.0f, 0.0f, -6.7f);
    glRotatef(18.0f, 0.0f, 1.0f, 0.0f);
    drawBench();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(9.0f, 0.0f, -18.2f);
    glRotatef(195.0f, 0.0f, 1.0f, 0.0f);
    drawBench();
    glPopMatrix();


    // -------------------------------------------------------------------------
    // Lamp posts
    // -------------------------------------------------------------------------

    const float lampPositions[8][3] =
    {
        {-4.5f, 0.0f,  1.0f},
        { 4.5f, 0.0f,  1.0f},
        {-8.5f, 0.0f, -7.0f},
        { 8.5f, 0.0f, -7.0f},
        {-8.5f, 0.0f, -18.0f},
        { 8.5f, 0.0f, -18.0f},
        {-5.0f, 0.0f, -25.0f},
        { 5.0f, 0.0f, -25.0f}
    };

    for (int i = 0; i < 8; i++)
    {
        glPushMatrix();

        glTranslatef(lampPositions[i][0], 0.0f, lampPositions[i][2]);

        if (i % 2 == 1)
            glRotatef(180.0f, 0.0f, 1.0f, 0.0f);

        drawLampPost();

        glPopMatrix();
    }


    // -------------------------------------------------------------------------
    // Graveyard corner
    // -------------------------------------------------------------------------

    const float gravePositions[7][3] =
    {
        {14.5f, 0.0f, -3.0f},
        {16.5f, 0.0f, -5.0f},
        {18.5f, 0.0f, -3.8f},
        {14.3f, 0.0f, -7.0f},
        {17.2f, 0.0f, -8.0f},
        {20.0f, 0.0f, -7.2f},
        {20.5f, 0.0f, -4.5f}
    };

    for (int i = 0; i < 7; i++)
    {
        glPushMatrix();

        glTranslatef(gravePositions[i][0], 0.0f, gravePositions[i][2]);
        glRotatef((i - 3) * 6.0f, 0.0f, 0.0f, 1.0f);

        if (i == 1 || i == 5)
            drawCrossGravestone();
        else
            drawGravestone();

        glPopMatrix();
    }


    // -------------------------------------------------------------------------
    // Crates
    // -------------------------------------------------------------------------

    const float cratePositions[5][3] =
    {
        {-12.5f, 0.0f, -3.0f},
        {-30.5f, 0.0f, -8.0f},
        {12.8f, 0.0f, -22.0f},
        {29.0f, 0.0f, -5.0f},
        {-9.5f, 0.0f, -22.0f}
    };

    for (int i = 0; i < 5; i++)
    {
        glPushMatrix();

        glTranslatef(cratePositions[i][0], 0.0f, cratePositions[i][2]);
        glRotatef(i * 19.0f, 0.0f, 1.0f, 0.0f);

        drawCrate();

        glPopMatrix();
    }


    // -------------------------------------------------------------------------
    // Barrels
    // -------------------------------------------------------------------------

    const float barrelPositions[4][3] =
    {
        {-13.8f, 0.0f, -2.5f},
        {-29.5f, 0.0f, -7.0f},
        {13.8f, 0.0f, -23.2f},
        {30.0f, 0.0f, -6.2f}
    };

    for (int i = 0; i < 4; i++)
    {
        glPushMatrix();

        glTranslatef(barrelPositions[i][0], 0.0f, barrelPositions[i][2]);

        drawBarrel();

        glPopMatrix();
    }


    // -------------------------------------------------------------------------
    // Pumpkins
    // -------------------------------------------------------------------------

    const float pumpkinPositions[8][3] =
    {
        {-5.7f, 0.0f, 3.8f},
        { 5.4f, 0.0f, 3.7f},
        {13.3f, 0.0f, -3.8f},
        {18.0f, 0.0f, -8.5f},
        {-12.0f, 0.0f, -18.5f},
        {-31.0f, 0.0f, -17.0f},
        {11.7f, 0.0f, -19.0f},
        {21.5f, 0.0f, -9.0f}
    };

    for (int i = 0; i < 8; i++)
    {
        glPushMatrix();

        glTranslatef(pumpkinPositions[i][0], 0.0f, pumpkinPositions[i][2]);

        float scale = 0.75f + (i % 3) * 0.12f;
        glScalef(scale, scale, scale);

        drawPumpkin();

        glPopMatrix();
    }


    // -------------------------------------------------------------------------
    // Skulls and bones
    // -------------------------------------------------------------------------

    glPushMatrix();
    glTranslatef(15.8f, 0.0f, -6.0f);
    glRotatef(-18.0f, 0.0f, 1.0f, 0.0f);
    drawSkull();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-11.0f, 0.0f, -19.0f);
    glRotatef(24.0f, 0.0f, 1.0f, 0.0f);
    drawSkull();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(17.0f, 0.12f, -6.2f);
    glRotatef(25.0f, 0.0f, 1.0f, 0.0f);
    drawBone();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(17.5f, 0.12f, -6.6f);
    glRotatef(-32.0f, 0.0f, 1.0f, 0.0f);
    drawBone();
    glPopMatrix();


    // -------------------------------------------------------------------------
    // Blood stains
    // -------------------------------------------------------------------------

    glPushMatrix();
    glTranslatef(10.0f, 0.0f, -15.8f);
    drawBloodStain(0.85f);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(24.0f, 0.0f, -12.5f);
    drawBloodStain(0.65f);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-17.0f, 0.0f, -12.0f);
    drawBloodStain(0.50f);
    glPopMatrix();


    // -------------------------------------------------------------------------
    // Water puddles
    // -------------------------------------------------------------------------

    glPushMatrix();
    glTranslatef(-6.5f, 0.0f, -3.5f);
    drawWaterPuddle(1.1f);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(7.2f, 0.0f, -21.5f);
    drawWaterPuddle(0.8f);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-20.0f, 0.0f, -6.0f);
    drawWaterPuddle(0.9f);
    glPopMatrix();


    // -------------------------------------------------------------------------
    // Grass and weeds
    // -------------------------------------------------------------------------

    const float grassPositions[20][3] =
    {
        {-7.0f, 0.0f, 4.0f},
        {-9.0f, 0.0f, 3.5f},
        { 8.0f, 0.0f, 4.0f},
        {11.0f, 0.0f, 3.0f},
        {-13.0f, 0.0f, -3.0f},
        {13.0f, 0.0f, -2.0f},
        {-14.0f, 0.0f, -7.0f},
        {14.0f, 0.0f, -9.0f},
        {-14.0f, 0.0f, -18.0f},
        {14.0f, 0.0f, -18.0f},
        {-18.0f, 0.0f, -21.0f},
        {18.0f, 0.0f, -22.0f},
        {-25.0f, 0.0f, -4.0f},
        {-29.0f, 0.0f, -5.0f},
        {24.0f, 0.0f, -4.0f},
        {29.0f, 0.0f, -8.0f},
        {-8.0f, 0.0f, -29.0f},
        { 8.0f, 0.0f, -29.0f},
        {-12.0f, 0.0f, -31.0f},
        {12.0f, 0.0f, -31.0f}
    };

    for (int i = 0; i < 20; i++)
    {
        glPushMatrix();

        glTranslatef(grassPositions[i][0], 0.02f, grassPositions[i][2]);
        glRotatef(i * 37.0f, 0.0f, 1.0f, 0.0f);

        drawGrassClump();

        glPopMatrix();
    }


    // -------------------------------------------------------------------------
    // Broken planks and rubbish
    // -------------------------------------------------------------------------

    const float plankPositions[7][3] =
    {
        {-7.5f, 0.0f, -4.0f},
        {11.5f, 0.0f, -3.0f},
        {-14.5f, 0.0f, -17.0f},
        {15.0f, 0.0f, -20.0f},
        {-28.0f, 0.0f, -8.5f},
        {28.0f, 0.0f, -8.0f},
        {-8.0f, 0.0f, -24.0f}
    };

    for (int i = 0; i < 7; i++)
    {
        glPushMatrix();

        glTranslatef(plankPositions[i][0], 0.10f, plankPositions[i][2]);
        glRotatef(i * 29.0f, 0.0f, 1.0f, 0.0f);
        glRotatef((i % 2) * 8.0f, 0.0f, 0.0f, 1.0f);

        drawBrokenPlank();

        glPopMatrix();
    }
}


// -----------------------------------------------------------------------------
// Initialization
// -----------------------------------------------------------------------------

void initialize()
{
    // Colour visible behind the scene if no geometry covers a pixel.
    glClearColor(0.01f, 0.01f, 0.04f, 1.0f);

    // Required so nearer 3D surfaces correctly hide surfaces behind them.
    glEnable(GL_DEPTH_TEST);

    // Keep texture colours unchanged when drawing textured surfaces.
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    TextureManager::initialize();

}


// -----------------------------------------------------------------------------
// Display
// -----------------------------------------------------------------------------

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Apply the player's current position and viewing direction.
    camera.applyView();

    drawNightSky();
    drawGround();

    drawCarnivalFence();
    drawEntranceGate();
    drawCarnivalSign();
    drawHorrorTents();
    drawHauntedFunHouse();
    drawEnvironmentProps();

    // Swap the completed back buffer to the screen.
    glutSwapBuffers();
}


// -----------------------------------------------------------------------------
// Projection and window resizing
// -----------------------------------------------------------------------------

void reshape(int width, int height)
{
    // Prevent division by zero if the window becomes extremely small.
    if (height == 0)
        height = 1;

    windowWidth = width;
    windowHeight = height;

    float aspect = static_cast<float>(width) / static_cast<float>(height);

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (usePerspective)
    {
        // 60 = field of view.
        // 0.1 and 100 = near and far clipping distances.
        gluPerspective(60.0, aspect, 0.1, 100.0);
    }
    else
    {
        // Increase viewSize to show more of the carnival in orthographic mode.
        float viewSize = 8.0f;

        if (width >= height)
            glOrtho(-viewSize * aspect, viewSize * aspect, -viewSize, viewSize, 0.1, 100.0);
        else
            glOrtho(-viewSize, viewSize, -viewSize / aspect, viewSize / aspect, 0.1, 100.0);
    }

    glMatrixMode(GL_MODELVIEW);
}


// -----------------------------------------------------------------------------
// Standard keyboard input
// -----------------------------------------------------------------------------

void keyboard(unsigned char key, int x, int y)
{
    // Change the speed ofmovement.
    const float moveSpeed = 0.6f;

    if (key == 'w' || key == 'W')
        camera.moveForward(moveSpeed);

    if (key == 's' || key == 'S')
        camera.moveForward(-moveSpeed);

    if (key == 'a' || key == 'A')
        camera.moveRight(-moveSpeed);

    if (key == 'd' || key == 'D')
        camera.moveRight(moveSpeed);

    // P switches between perspective and orthographic projections.
    if (key == 'p' || key == 'P')
    {
        usePerspective = !usePerspective;
        reshape(windowWidth, windowHeight);
    }

    glutPostRedisplay();
}


// -----------------------------------------------------------------------------
// Special keyboard input
// -----------------------------------------------------------------------------

void specialKeyboard(int key, int x, int y)
{
    // Increase this value if the examiner asks the camera to turn faster.
    const float rotationSpeed = 4.0f;

    if (key == GLUT_KEY_LEFT)
        camera.rotateYaw(-rotationSpeed);

    if (key == GLUT_KEY_RIGHT)
        camera.rotateYaw(rotationSpeed);

    if (key == GLUT_KEY_UP)
        camera.rotatePitch(rotationSpeed);

    if (key == GLUT_KEY_DOWN)
        camera.rotatePitch(-rotationSpeed);

    glutPostRedisplay();
}


// -----------------------------------------------------------------------------
// Main
// -----------------------------------------------------------------------------

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    // Double buffering reduces flickering and depth buffering enables 3D depth.
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("Carnival of Shadows");

    initialize();

    // GLUT calls these functions when rendering, resizing, or receiving input.
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyboard);

    glutMainLoop();

    return 0;
}