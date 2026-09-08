/*
 * File: HauntedTree.cpp
 * Project: Carnival of Shadows
 * Course: CSC3081 - Computer Graphics Programming
 *
 * Purpose:
 * Builds twisted dead trees from recursively connected branches.
 */

#include "pch.h"
#include "HauntedTree.h"
#include "Primitives.h"

#include <GL/glut.h>
#include <cmath>


 // -----------------------------------------------------------------------------
 // Tree roots
 // -----------------------------------------------------------------------------

void HauntedTree::drawRoots(float variation)
{
    const int rootCount = 6;

    for (int i = 0; i < rootCount; i++)
    {
        float angle = i * 60.0f + variation * 7.0f;

        glPushMatrix();

        glRotatef(angle, 0.0f, 1.0f, 0.0f);
        glTranslatef(0.0f, 0.08f, 0.72f);

        // Flatten the roots into the ground.
        glRotatef(12.0f + (i % 2) * 6.0f, 1.0f, 0.0f, 0.0f);
        glScalef(0.20f, 0.13f, 1.55f);

        glColor3f(0.075f, 0.030f, 0.012f);
        Primitives::drawCube(1.0f);

        glPopMatrix();
    }
}


// -----------------------------------------------------------------------------
// Recursive tree branch
// -----------------------------------------------------------------------------

void HauntedTree::drawBranch(int depth, float length, float radius, float variation)
{
    if (depth <= 0)
        return;


    // Branch gets thinner toward its end.
    glColor3f(0.09f, 0.037f, 0.014f);
    Primitives::drawCylinder(radius, length, 9);


    // Move to the end of this branch before drawing child branches.
    glTranslatef(0.0f, length, 0.0f);


    // Small broken point at some branch ends.
    if (depth == 1)
    {
        glPushMatrix();

        glRotatef(variation * 4.0f, 0.0f, 0.0f, 1.0f);

        glColor3f(0.07f, 0.025f, 0.010f);
        Primitives::drawCone(radius * 0.9f, length * 0.22f, 7);

        glPopMatrix();

        return;
    }


    float nextLength = length * 0.72f;
    float nextRadius = radius * 0.67f;


    // Left branch.
    glPushMatrix();

    glRotatef(30.0f + variation * 2.0f, 0.0f, 0.0f, 1.0f);
    glRotatef(35.0f + variation * 8.0f, 0.0f, 1.0f, 0.0f);

    drawBranch(depth - 1, nextLength, nextRadius, variation + 0.7f);

    glPopMatrix();


    // Right branch.
    glPushMatrix();

    glRotatef(-36.0f - variation * 2.0f, 0.0f, 0.0f, 1.0f);
    glRotatef(-48.0f + variation * 5.0f, 0.0f, 1.0f, 0.0f);

    drawBranch(depth - 1, nextLength * 0.92f, nextRadius, variation + 1.3f);

    glPopMatrix();


    // Extra branch on the larger sections.
    if (depth >= 3)
    {
        glPushMatrix();

        glRotatef(18.0f + variation, 0.0f, 0.0f, 1.0f);
        glRotatef(145.0f + variation * 6.0f, 0.0f, 1.0f, 0.0f);

        drawBranch(depth - 1, nextLength * 0.78f, nextRadius * 0.85f, variation + 2.1f);

        glPopMatrix();
    }
}


// -----------------------------------------------------------------------------
// Haunted tree
// -----------------------------------------------------------------------------

void HauntedTree::draw(float variation)
{
    drawRoots(variation);


    glPushMatrix();

    // Slight lean makes each tree less symmetrical.
    glRotatef(-5.0f + variation * 1.5f, 0.0f, 0.0f, 1.0f);
    glRotatef(variation * 9.0f, 0.0f, 1.0f, 0.0f);

    // Main trunk.
    glColor3f(0.11f, 0.045f, 0.016f);
    Primitives::drawCylinder(0.38f, 2.7f, 10);

    glTranslatef(0.0f, 2.7f, 0.0f);


    // Upper trunk continues into the recursive branch structure.
    glPushMatrix();

    glRotatef(8.0f + variation, 0.0f, 0.0f, 1.0f);

    drawBranch(4, 2.1f, 0.27f, variation);

    glPopMatrix();


    // Low broken branch.
    glPushMatrix();

    glRotatef(-58.0f, 0.0f, 0.0f, 1.0f);
    glRotatef(30.0f + variation * 6.0f, 0.0f, 1.0f, 0.0f);

    drawBranch(2, 1.5f, 0.16f, variation + 3.0f);

    glPopMatrix();


    glPopMatrix();
}