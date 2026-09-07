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
 * - handling the application render loop
 * - handling application-level input
 * - using reusable objects from Lib
 */

#include <GL/glut.h>

#include "../Lib/Mesh.h"
#include "../Lib/MeshRenderer.h"
#include "Camera.h"


 // -----------------------------------------------------------------------------
 // Application state
 // -----------------------------------------------------------------------------

Mesh testCube;
MeshRenderer meshRenderer;
Camera camera;

// Determines which projection is currently used.
bool usePerspective = true;

// Stored so the projection can be recalculated when P is pressed.
int windowWidth = 800;
int windowHeight = 600;


// -----------------------------------------------------------------------------
// Initialization
// -----------------------------------------------------------------------------

void initialize()
{
    // Dark blue-black background for the night carnival atmosphere.
    glClearColor(0.05f, 0.05f, 0.10f, 1.0f);

    // Makes nearer surfaces hide surfaces behind them.
    glEnable(GL_DEPTH_TEST);

    // Temporary object used to test the reusable mesh system.
    testCube = Mesh::createCube(2.0f);
}


// -----------------------------------------------------------------------------
// Display
// -----------------------------------------------------------------------------

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Positions and aims the viewer inside the 3D scene.
    camera.applyView();

    // Temporary colour until materials and lighting are introduced.
    glColor3f(0.7f, 0.7f, 0.8f);

    meshRenderer.renderWireframe(testCube);

    // Display the completed back buffer on screen.
    glutSwapBuffers();
}


// -----------------------------------------------------------------------------
// Projection and window resizing
// -----------------------------------------------------------------------------

void reshape(int width, int height)
{
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
        // FOV controls how wide the camera view appears.
        // Near/far values define the visible depth range.
        gluPerspective(60.0, aspect, 0.1, 100.0);
    }
    else
    {
        // Larger values show more of the scene in orthographic mode.
        float viewSize = 5.0f;

        if (width >= height)
            glOrtho(-viewSize * aspect, viewSize * aspect, -viewSize, viewSize, 0.1, 100.0);
        else
            glOrtho(-viewSize, viewSize, -viewSize / aspect, viewSize / aspect, 0.1, 100.0);
    }

    glMatrixMode(GL_MODELVIEW);
}


// -----------------------------------------------------------------------------
// Keyboard input
// -----------------------------------------------------------------------------

void keyboard(unsigned char key, int x, int y)
{
    // Movement speed can be adjusted later if navigation feels too fast or slow.
    const float moveSpeed = 0.4f;

    if (key == 'w' || key == 'W')
        camera.moveForward(moveSpeed);

    if (key == 's' || key == 'S')
        camera.moveForward(-moveSpeed);

    if (key == 'a' || key == 'A')
        camera.moveRight(-moveSpeed);

    if (key == 'd' || key == 'D')
        camera.moveRight(moveSpeed);

    // P switches between perspective and orthographic projection.
    if (key == 'p' || key == 'P')
    {
        usePerspective = !usePerspective;
        reshape(windowWidth, windowHeight);
    }

    glutPostRedisplay();
}


void specialKeyboard(int key, int x, int y)
{
    // Rotation speed controls how quickly the camera turns.
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

    // Double buffering prevents visible flickering while rendering.
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("Carnival of Shadows");

    initialize();

    // Register GLUT callback functions.
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyboard);

    glutMainLoop();

    return 0;
}