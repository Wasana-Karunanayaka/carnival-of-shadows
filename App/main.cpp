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
 * - configuring the camera/projection
 * - handling the application render loop
 * - using reusable objects from Lib
 *
 * Project-specific carnival systems will be added here
 * gradually as development progresses.
 */

#include <GL/glut.h>

#include "../Lib/Mesh.h"
#include "../Lib/MeshRenderer.h"


 // -----------------------------------------------------------------------------
 // Application objects
 // -----------------------------------------------------------------------------

Mesh testCube;
MeshRenderer meshRenderer;


// -----------------------------------------------------------------------------
// Initialization
// -----------------------------------------------------------------------------

void initialize()
{
    // Dark background suitable for the haunted carnival scene.
    glClearColor(
        0.05f,
        0.05f,
        0.10f,
        1.0f
    );

    // Required so nearer surfaces hide surfaces behind them.
    glEnable(GL_DEPTH_TEST);

    // Temporary geometry used to verify the reusable mesh system.
    testCube = Mesh::createCube(2.0f);
}


// -----------------------------------------------------------------------------
// Display callback
// -----------------------------------------------------------------------------

void display()
{
    glClear(
        GL_COLOR_BUFFER_BIT |
        GL_DEPTH_BUFFER_BIT
    );

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Temporary camera.
    // A dedicated camera system will be added later.
    gluLookAt(
        0.0, 2.0, 6.0,   // camera position
        0.0, 0.0, 0.0,   // point being viewed
        0.0, 1.0, 0.0    // upward direction
    );

    glColor3f(
        0.7f,
        0.7f,
        0.8f
    );

    meshRenderer.renderWireframe(testCube);

    glutSwapBuffers();
}


// -----------------------------------------------------------------------------
// Window resize / projection
// -----------------------------------------------------------------------------

void reshape(int width, int height)
{
    if (height == 0)
    {
        height = 1;
    }

    float aspect =
        static_cast<float>(width) /
        static_cast<float>(height);

    glViewport(
        0,
        0,
        width,
        height
    );

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Perspective projection gives the scene normal 3D depth.
    gluPerspective(
        60.0,
        aspect,
        0.1,
        100.0
    );

    glMatrixMode(GL_MODELVIEW);
}


// -----------------------------------------------------------------------------
// Main
// -----------------------------------------------------------------------------

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(
        GLUT_DOUBLE |
        GLUT_RGB |
        GLUT_DEPTH
    );

    glutInitWindowSize(
        800,
        600
    );

    glutInitWindowPosition(
        100,
        100
    );

    glutCreateWindow(
        "Carnival of Shadows"
    );

    initialize();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}