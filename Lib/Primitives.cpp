/*
 * File: Primitives.cpp
 * Project: Carnival of Shadows
 * Course: CSC3081 - Computer Graphics Programming
 *
 * Purpose:
 * Implements reusable GLUT and GLU primitive shapes.
 */

#include "pch.h"
#include "Primitives.h"

#include <GL/glut.h>


void Primitives::drawCube(float size)
{
    glutSolidCube(size);
}


void Primitives::drawSphere(float radius, int slices, int stacks)
{
    glutSolidSphere(radius, slices, stacks);
}


void Primitives::drawCylinder(float radius, float height, int slices)
{
    GLUquadric* quadric = gluNewQuadric();

    // GLU cylinders point along Z, rotate it so carnival objects stand on Y.
    glPushMatrix();
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

    gluCylinder(quadric, radius, radius, height, slices, 1);

    // Bottom cap.
    glPushMatrix();
    glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
    gluDisk(quadric, 0.0f, radius, slices, 1);
    glPopMatrix();

    // Top cap.
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, height);
    gluDisk(quadric, 0.0f, radius, slices, 1);
    glPopMatrix();

    glPopMatrix();

    gluDeleteQuadric(quadric);
}


void Primitives::drawCone(float radius, float height, int slices)
{
    GLUquadric* quadric = gluNewQuadric();

    // Keep cone direction consistent with the cylinder helper.
    glPushMatrix();
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

    gluCylinder(quadric, radius, 0.0f, height, slices, 1);

    // Close the bottom of the cone.
    glPushMatrix();
    glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
    gluDisk(quadric, 0.0f, radius, slices, 1);
    glPopMatrix();

    glPopMatrix();

    gluDeleteQuadric(quadric);
}