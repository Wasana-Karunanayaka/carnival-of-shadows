/*
 * File: FerrisWheel.cpp
 * Project: Carnival of Shadows
 * Course: CSC3081 - Computer Graphics Programming
 *
 * Purpose:
 * Builds the broken horror Ferris wheel from handmade 3D geometry.
 */

#include "pch.h"
#include "FerrisWheel.h"
#include "Primitives.h"
#include "TextureManager.h"

#include <GL/glut.h>
#include <cmath>


const float PI = 3.14159265f;


// -----------------------------------------------------------------------------
// Ferris wheel setup
// -----------------------------------------------------------------------------

FerrisWheel::FerrisWheel()
{
    // Change these values to resize the whole wheel.
    wheelRadius = 6.0f;
    wheelHeight = 9.0f;
    wheelDepth = 2.2f;

    wheelAngle = 0.0f;

	// The wheel is broken, so it rotates slowly.
    wheelSpeed = 0.25f;

    // Start the wheel rotating.
    isRotating = true;
}


// -----------------------------------------------------------------------------
// Rusty metal surface
// -----------------------------------------------------------------------------

void drawRustyMetalCube()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, TextureManager::rustyMetalTexture);

    // Darken the rust texture slightly.
    glColor3f(0.68f, 0.63f, 0.58f);

    Primitives::drawTexturedCube(1.0f);

    glDisable(GL_TEXTURE_2D);
}


// -----------------------------------------------------------------------------
// Beam between two points
// -----------------------------------------------------------------------------

void FerrisWheel::drawBeam(float x1, float y1,
    float x2, float y2,
    float z,
    float thickness,
    float depth)
{
    float dx = x2 - x1;
    float dy = y2 - y1;

    // Pythagoras gives the beam length.
    float length = sqrtf(dx * dx + dy * dy);

    // atan2 gives the angle between the two points.
    float angle = atan2f(dy, dx) * 180.0f / PI;

    // Put the cube halfway between both points.
    float middleX = (x1 + x2) / 2.0f;
    float middleY = (y1 + y2) / 2.0f;

    glPushMatrix();

    glTranslatef(middleX, middleY, z);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);

    glScalef(length, thickness, depth);

    drawRustyMetalCube();

    glPopMatrix();
}


// -----------------------------------------------------------------------------
// Broken Ferris wheel base
// -----------------------------------------------------------------------------

void FerrisWheel::drawBase()
{
    // Main concrete platform.
    glPushMatrix();

    glTranslatef(0.0f, 0.18f, 0.0f);
    glScalef(9.5f, 0.35f, 5.5f);

    // Old stone texture for the damaged platform.
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, TextureManager::stoneTexture);

    glColor3f(0.65f, 0.65f, 0.62f);
    Primitives::drawTexturedCube(1.0f);

    glDisable(GL_TEXTURE_2D);

    glPopMatrix();


    // Broken left platform section.
    glPushMatrix();

    glTranslatef(-4.1f, 0.40f, 0.15f);
    glRotatef(-5.0f, 0.0f, 0.0f, 1.0f);
    glScalef(1.5f, 0.22f, 4.7f);

    glColor3f(0.17f, 0.075f, 0.030f);
    Primitives::drawCube(1.0f);

    glPopMatrix();


    // Broken right platform section.
    glPushMatrix();

    glTranslatef(4.0f, 0.40f, -0.15f);
    glRotatef(6.0f, 0.0f, 0.0f, 1.0f);
    glScalef(1.5f, 0.20f, 4.4f);

    glColor3f(0.15f, 0.065f, 0.025f);
    Primitives::drawCube(1.0f);

    glPopMatrix();


    // Fallen wooden plank.
    glPushMatrix();

    glTranslatef(-1.8f, 0.42f, 2.45f);
    glRotatef(18.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(-7.0f, 0.0f, 0.0f, 1.0f);
    glScalef(2.8f, 0.14f, 0.42f);

    glColor3f(0.15f, 0.055f, 0.020f);
    Primitives::drawCube(1.0f);

    glPopMatrix();
}


// -----------------------------------------------------------------------------
// Ferris wheel supports
// -----------------------------------------------------------------------------

void FerrisWheel::drawSupports()
{
    float frontZ = -wheelDepth / 2.0f - 0.35f;
    float backZ = wheelDepth / 2.0f + 0.35f;

    glColor3f(0.19f, 0.17f, 0.14f);


    // -------------------------------------------------------------------------
    // Front A-frame
    // -------------------------------------------------------------------------

    drawBeam(-4.6f, 0.4f,
        0.0f, wheelHeight,
        frontZ, 0.42f, 0.38f);

    drawBeam(4.6f, 0.4f,
        0.0f, wheelHeight,
        frontZ, 0.42f, 0.38f);


    // Front cross braces.
    glColor3f(0.12f, 0.11f, 0.095f);

    drawBeam(-3.3f, 2.2f,
        3.3f, 2.2f,
        frontZ, 0.20f, 0.22f);

    drawBeam(-2.2f, 4.1f,
        2.2f, 4.1f,
        frontZ, 0.17f, 0.20f);


    // -------------------------------------------------------------------------
    // Back A-frame
    // -------------------------------------------------------------------------

    glColor3f(0.17f, 0.15f, 0.13f);

    // One side is slightly crooked.
    drawBeam(-4.4f, 0.4f,
        0.0f, wheelHeight,
        backZ, 0.42f, 0.38f);

    drawBeam(4.8f, 0.4f,
        0.0f, wheelHeight,
        backZ, 0.42f, 0.38f);


    // Back cross braces.
    glColor3f(0.11f, 0.10f, 0.085f);

    drawBeam(-3.2f, 2.2f,
        3.5f, 2.2f,
        backZ, 0.20f, 0.22f);

    drawBeam(-2.1f, 4.1f,
        2.3f, 4.1f,
        backZ, 0.17f, 0.20f);


    // -------------------------------------------------------------------------
    // Heavy support feet
    // -------------------------------------------------------------------------

    const float footX[4] =
    {
        -4.6f,
         4.6f,
        -4.4f,
         4.8f
    };

    const float footZ[4] =
    {
        frontZ,
        frontZ,
        backZ,
        backZ
    };

    for (int i = 0; i < 4; i++)
    {
        glPushMatrix();

        glTranslatef(footX[i], 0.32f, footZ[i]);
        glScalef(1.15f, 0.42f, 0.95f);

        glColor3f(0.10f, 0.09f, 0.08f);
        drawRustyMetalCube();

        glPopMatrix();
    }
}


// -----------------------------------------------------------------------------
// Centre axle and hubs
// -----------------------------------------------------------------------------

void FerrisWheel::drawAxle()
{
    // Axle starts at the front and passes through both rims.
    glPushMatrix();

    glTranslatef(
        0.0f,
        wheelHeight,
        -wheelDepth / 2.0f - 0.7f
    );

    // Our cylinder normally points upward.
    // Rotate it so it points through the wheel.
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);

    glColor3f(0.13f, 0.12f, 0.11f);

    Primitives::drawCylinder(
        0.32f,
        wheelDepth + 1.4f,
        16
    );

    glPopMatrix();


    // Front hub.
    glPushMatrix();

    glTranslatef(
        0.0f,
        wheelHeight,
        -wheelDepth / 2.0f
    );

    glColor3f(0.20f, 0.17f, 0.13f);
    Primitives::drawSphere(0.62f, 18, 14);

    glPopMatrix();


    // Back hub.
    glPushMatrix();

    glTranslatef(
        0.0f,
        wheelHeight,
        wheelDepth / 2.0f
    );

    glColor3f(0.18f, 0.15f, 0.12f);
    Primitives::drawSphere(0.62f, 18, 14);

    glPopMatrix();
}


// -----------------------------------------------------------------------------
// Outer Ferris wheel rim
// -----------------------------------------------------------------------------

void FerrisWheel::drawRim(float z)
{
    const int segments = 36;

    for (int i = 0; i < segments; i++)
    {
        // Missing pieces make the wheel look abandoned.
        if (i == 4 || i == 5 || i == 19)
            continue;

        float angle1 =
            2.0f * PI * i / segments;

        float angle2 =
            2.0f * PI * (i + 1) / segments;


        // sin and cos calculate points around the circle.
        float x1 =
            wheelRadius * cosf(angle1);

        float y1 =
            wheelRadius * sinf(angle1);

        float x2 =
            wheelRadius * cosf(angle2);

        float y2 =
            wheelRadius * sinf(angle2);


        // Slight colour changes stop the rim looking too clean.
        if (i % 4 == 0)
            glColor3f(0.22f, 0.16f, 0.11f);
        else
            glColor3f(0.16f, 0.15f, 0.13f);


        drawBeam(
            x1, y1,
            x2, y2,
            z,
            0.22f,
            0.20f
        );
    }


    // Bent broken piece hanging from one gap.
    if (z < 0.0f)
    {
        glColor3f(0.20f, 0.10f, 0.055f);

        drawBeam(
            4.3f, 4.0f,
            4.8f, 2.8f,
            z,
            0.18f,
            0.18f
        );
    }
}


// -----------------------------------------------------------------------------
// Inner Ferris wheel ring
// -----------------------------------------------------------------------------

void FerrisWheel::drawInnerRing(float z)
{
    const int segments = 24;
    const float innerRadius = 2.25f;

    glColor3f(0.13f, 0.12f, 0.105f);

    for (int i = 0; i < segments; i++)
    {
        float angle1 =
            2.0f * PI * i / segments;

        float angle2 =
            2.0f * PI * (i + 1) / segments;


        float x1 =
            innerRadius * cosf(angle1);

        float y1 =
            innerRadius * sinf(angle1);

        float x2 =
            innerRadius * cosf(angle2);

        float y2 =
            innerRadius * sinf(angle2);


        drawBeam(
            x1, y1,
            x2, y2,
            z,
            0.12f,
            0.14f
        );
    }
}


// -----------------------------------------------------------------------------
// Ferris wheel spokes
// -----------------------------------------------------------------------------

void FerrisWheel::drawSpokes(float z)
{
    const int spokeCount = 16;

    for (int i = 0; i < spokeCount; i++)
    {
        float angle =
            2.0f * PI * i / spokeCount;


        float endX =
            wheelRadius * 0.96f * cosf(angle);

        float endY =
            wheelRadius * 0.96f * sinf(angle);


        // Leave two spokes broken.
        if (i == 5 || i == 12)
            continue;


        // One bent spoke.
        if (i == 9)
        {
            endX += 0.45f;
            endY -= 0.35f;
        }


        if (i % 2 == 0)
            glColor3f(0.14f, 0.13f, 0.11f);
        else
            glColor3f(0.12f, 0.11f, 0.095f);


        drawBeam(
            0.0f, 0.0f,
            endX, endY,
            z,
            0.10f,
            0.11f
        );
    }
}


// -----------------------------------------------------------------------------
// Bars joining the front and back rims
// -----------------------------------------------------------------------------

void FerrisWheel::drawCrossBars()
{
    const int barCount = 12;

    for (int i = 0; i < barCount; i++)
    {
        // Missing bar near the damaged rim.
        if (i == 2)
            continue;

        float angle =
            2.0f * PI * i / barCount;


        float x =
            wheelRadius * cosf(angle);

        float y =
            wheelRadius * sinf(angle);


        glPushMatrix();

        glTranslatef(x, y, 0.0f);
        glScalef(
            0.18f,
            0.18f,
            wheelDepth + 0.25f
        );

        glColor3f(0.13f, 0.11f, 0.095f);
        drawRustyMetalCube();

        glPopMatrix();
    }
}


// -----------------------------------------------------------------------------
// Ferris wheel cabin
// -----------------------------------------------------------------------------

void FerrisWheel::drawCabin(bool damaged)
{
    // Cabin floor.
    glPushMatrix();

    glTranslatef(0.0f, -0.55f, 0.0f);
    glScalef(1.45f, 0.18f, 1.25f);

    // Rotten wooden cabin floor.
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, TextureManager::woodTexture);

    glColor3f(0.65f, 0.58f, 0.50f);
    Primitives::drawTexturedCube(1.0f);

    glDisable(GL_TEXTURE_2D);

    glPopMatrix();


    // Four cabin frame posts.
    const float postX[4] =
    {
        -0.60f, 0.60f,
        -0.60f, 0.60f
    };

    const float postZ[4] =
    {
        -0.48f, -0.48f,
         0.48f,  0.48f
    };


    for (int i = 0; i < 4; i++)
    {
        // A damaged cabin is missing one corner post.
        if (damaged && i == 1)
            continue;

        glPushMatrix();

        glTranslatef(
            postX[i],
            0.15f,
            postZ[i]
        );

        glScalef(
            0.10f,
            1.45f,
            0.10f
        );

        // Rotten back panel.
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, TextureManager::woodTexture);

        glColor3f(0.52f, 0.47f, 0.42f);
        drawRustyMetalCube();

        glDisable(GL_TEXTURE_2D);

        glPopMatrix();
    }


    // Cabin roof.
    glPushMatrix();

    glTranslatef(0.0f, 0.92f, 0.0f);
    glScalef(1.6f, 0.16f, 1.35f);

    // Old wooden cabin roof.
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, TextureManager::woodTexture);

    glColor3f(0.55f, 0.48f, 0.42f);
    Primitives::drawTexturedCube(1.0f);

    glDisable(GL_TEXTURE_2D);

    glPopMatrix();


    // Roof cap.
    glPushMatrix();

    glTranslatef(0.0f, 1.05f, 0.0f);
    glRotatef(45.0f, 0.0f, 1.0f, 0.0f);

    glColor3f(0.12f, 0.075f, 0.055f);
    Primitives::drawCone(0.65f, 0.35f, 4);

    glPopMatrix();


    // Rear cabin wall.
    glPushMatrix();

    glTranslatef(
        0.0f,
        0.10f,
        -0.55f
    );

    glScalef(
        1.30f,
        1.25f,
        0.08f
    );

    // Rotten back panel.
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, TextureManager::woodTexture);

    glColor3f(0.52f, 0.47f, 0.42f);
    Primitives::drawTexturedCube(1.0f);

    glDisable(GL_TEXTURE_2D);

    glPopMatrix();


    // Side safety rails.
    if (!damaged)
    {
        glPushMatrix();

        glTranslatef(
            -0.62f,
            0.12f,
            0.0f
        );

        glScalef(
            0.08f,
            0.18f,
            1.0f
        );

        // Rotten back panel.
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, TextureManager::woodTexture);

        glColor3f(0.52f, 0.47f, 0.42f);
        drawRustyMetalCube();

        glDisable(GL_TEXTURE_2D);

        glPopMatrix();


        glPushMatrix();

        glTranslatef(
            0.62f,
            0.12f,
            0.0f
        );

        glScalef(
            0.08f,
            0.18f,
            1.0f
        );

        glColor3f(0.18f, 0.13f, 0.09f);
        Primitives::drawCube(1.0f);

        glPopMatrix();
    }
}


// -----------------------------------------------------------------------------
// Ferris wheel cabins
// -----------------------------------------------------------------------------

void FerrisWheel::drawCabins()
{
    const int cabinCount = 12;

    for (int i = 0; i < cabinCount; i++)
    {
        // Leave one cabin missing to make the wheel look abandoned.
        if (i == 3)
            continue;

        float angle = 2.0f * PI * i / cabinCount;

        // Calculate the attachment point around the wheel.
        float x = wheelRadius * cosf(angle);
        float y = wheelRadius * sinf(angle);

        glPushMatrix();

        // First move to the correct point on the rotating rim.
        glTranslatef(x, y, 0.0f);

        // Cancel the wheel rotation so the cabin stays upright.
        glRotatef(-wheelAngle, 0.0f, 0.0f, 1.0f);

        // Now move downward from the rim.
        // This movement stays vertical instead of rotating with the wheel.
        glTranslatef(0.0f, -1.05f, 0.0f);


        // One damaged cabin hangs at an angle.
        bool damaged = (i == 8);

        if (damaged)
            glRotatef(17.0f, 0.0f, 0.0f, 1.0f);


        // Hanging bar from the wheel.
        glPushMatrix();

        glTranslatef(0.0f, 0.75f, 0.0f);
        glScalef(0.10f, 1.50f, 0.10f);

        drawRustyMetalCube();

        glPopMatrix();


        // Bar across the cabin roof.
        glPushMatrix();

        glTranslatef(0.0f, 0.85f, 0.0f);
        glScalef(1.6f, 0.10f, 0.10f);

        drawRustyMetalCube();

        glPopMatrix();


        drawCabin(damaged);

        glPopMatrix();
    }
}


// -----------------------------------------------------------------------------
// Rotating wheel structure
// -----------------------------------------------------------------------------

void FerrisWheel::drawWheel()
{
    glPushMatrix();


    // Move the wheel centre above the ground.
    glTranslatef(
        0.0f,
        wheelHeight,
        0.0f
    );


    // This rotation will animate the whole wheel later.
    glRotatef(
        wheelAngle,
        0.0f,
        0.0f,
        1.0f
    );


    // Front rim.
    drawRim(-wheelDepth / 2.0f);

    // Back rim.
    drawRim(wheelDepth / 2.0f);


    // Smaller rings strengthen the structure.
    drawInnerRing(-wheelDepth / 2.0f);
    drawInnerRing(wheelDepth / 2.0f);


    // Spokes on both sides.
    drawSpokes(-wheelDepth / 2.0f);
    drawSpokes(wheelDepth / 2.0f);


    // Join both sides of the wheel.
    drawCrossBars();


    // Cabins are positioned around the outside.
    drawCabins();


    glPopMatrix();
}


// -----------------------------------------------------------------------------
// Complete Ferris wheel
// -----------------------------------------------------------------------------

void FerrisWheel::draw()
{
    // These parts remain stationary.
    drawBase();
    drawSupports();
    drawAxle();

    // This part will rotate later.
    drawWheel();
}


// -----------------------------------------------------------------------------
// Ferris wheel animation
// -----------------------------------------------------------------------------

void FerrisWheel::update()
{
    if (!isRotating)
        return;

    wheelAngle += wheelSpeed;

    if (wheelAngle >= 360.0f)
        wheelAngle -= 360.0f;
}


// -----------------------------------------------------------------------------
// Start or stop rotation
// -----------------------------------------------------------------------------

void FerrisWheel::toggleRotation()
{
    isRotating = !isRotating;
}


// -----------------------------------------------------------------------------
// Increase rotation speed
// -----------------------------------------------------------------------------

void FerrisWheel::increaseSpeed()
{
    wheelSpeed += 0.05f;
}


// -----------------------------------------------------------------------------
// Decrease rotation speed
// -----------------------------------------------------------------------------

void FerrisWheel::decreaseSpeed()
{
    wheelSpeed -= 0.05f;

    if (wheelSpeed < 0.0f)
        wheelSpeed = 0.0f;
}