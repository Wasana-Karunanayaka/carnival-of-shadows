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
#include "Camera.h"



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
    // Increase this value if the carnival needs more usable land.
    const float groundSize = 40.0f;

    // Dark grass/soil colour. This can later be replaced with a ground texture.
    glColor3f(0.07f, 0.08f, 0.07f);

    glBegin(GL_QUADS);

    glVertex3f(-groundSize, 0.0f, -groundSize);
    glVertex3f(groundSize, 0.0f, -groundSize);
    glVertex3f(groundSize, 0.0f, groundSize);
    glVertex3f(-groundSize, 0.0f, groundSize);

    glEnd();


    // Slightly raised above the ground to prevent overlapping surfaces flickering.
    const float pathY = 0.01f;

    glColor3f(0.17f, 0.15f, 0.13f);

    glBegin(GL_QUADS);

    // Main entrance path.
    // Change +/-2.5 to make the path wider or narrower.
    glVertex3f(-2.5f, pathY, 12.0f);
    glVertex3f(2.5f, pathY, 12.0f);
    glVertex3f(2.5f, pathY, -5.0f);
    glVertex3f(-2.5f, pathY, -5.0f);


    // Central carnival plaza.
    // This area gives enough space for visitors to move between attractions.
    glVertex3f(-12.0f, pathY, -5.0f);
    glVertex3f(12.0f, pathY, -5.0f);
    glVertex3f(12.0f, pathY, -20.0f);
    glVertex3f(-12.0f, pathY, -20.0f);


    // Left branch leading toward the circus tent area.
    glVertex3f(-22.0f, pathY, -10.0f);
    glVertex3f(-12.0f, pathY, -10.0f);
    glVertex3f(-12.0f, pathY, -15.0f);
    glVertex3f(-22.0f, pathY, -15.0f);


    // Right branch leading toward the haunted house area.
    glVertex3f(12.0f, pathY, -10.0f);
    glVertex3f(22.0f, pathY, -10.0f);
    glVertex3f(22.0f, pathY, -15.0f);
    glVertex3f(12.0f, pathY, -15.0f);


    // Rear path leading deeper into the carnival.
    glVertex3f(-3.0f, pathY, -20.0f);
    glVertex3f(3.0f, pathY, -20.0f);
    glVertex3f(3.0f, pathY, -34.0f);
    glVertex3f(-3.0f, pathY, -34.0f);

    glEnd();
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

    glColor3f(0.18f, 0.18f, 0.20f);
    Primitives::drawCube(1.0f);

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

    glColor3f(0.30f, 0.07f, 0.05f);
    Primitives::drawCube(1.0f);

    glPopMatrix();


    // Broken upper plank.
    glPushMatrix();
    glTranslatef(-0.25f, 2.95f, 0.0f);
    glRotatef(12.0f, 0.0f, 0.0f, 1.0f);
    glScalef(1.8f, 0.30f, 0.18f);

    glColor3f(0.24f, 0.06f, 0.04f);
    Primitives::drawCube(1.0f);

    glPopMatrix();


    // Small broken side piece.
    glPushMatrix();
    glTranslatef(1.35f, 2.25f, 0.0f);
    glRotatef(-25.0f, 0.0f, 0.0f, 1.0f);
    glScalef(0.7f, 0.22f, 0.16f);

    glColor3f(0.20f, 0.05f, 0.03f);
    Primitives::drawCube(1.0f);

    glPopMatrix();


    // Pointed ornament on top.
    glPushMatrix();
    glTranslatef(0.0f, 3.18f, 0.0f);

    glColor3f(0.35f, 0.08f, 0.06f);
    Primitives::drawCone(0.22f, 0.55f, 12);

    glPopMatrix();


    // Hanging cross piece.
    glPushMatrix();
    glTranslatef(-1.1f, 2.15f, 0.0f);
    glRotatef(6.0f, 0.0f, 0.0f, 1.0f);
    glScalef(0.12f, 0.9f, 0.12f);

    glColor3f(0.12f, 0.05f, 0.03f);
    Primitives::drawCube(1.0f);

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

    glColor3f(0.12f, 0.05f, 0.025f);
    Primitives::drawCube(1.0f);

    glPopMatrix();


    // Upper horizontal rail.
    glPushMatrix();
    glTranslatef(centreX, 1.25f, z);
    glScalef(fenceLength, 0.12f, 0.12f);

    glColor3f(0.12f, 0.05f, 0.025f);
    Primitives::drawCube(1.0f);

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

    glColor3f(0.20f, 0.07f, 0.035f);
    Primitives::drawCube(1.0f);

    glPopMatrix();


    // Upper crooked beam.
    glPushMatrix();
    glTranslatef(0.0f, 4.25f, 0.0f);
    glRotatef(3.0f, 0.0f, 0.0f, 1.0f);
    glScalef(5.3f, 0.22f, 0.28f);

    glColor3f(0.25f, 0.065f, 0.04f);
    Primitives::drawCube(1.0f);

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

    glColor3f(0.17f, 0.05f, 0.025f);
    Primitives::drawCube(1.0f);

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
// Initialization
// -----------------------------------------------------------------------------

void initialize()
{
    // Colour visible behind the scene if no geometry covers a pixel.
    glClearColor(0.01f, 0.01f, 0.04f, 1.0f);

    // Required so nearer 3D surfaces correctly hide surfaces behind them.
    glEnable(GL_DEPTH_TEST);
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