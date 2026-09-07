/*
 * File: MeshRenderer.cpp
 * Project: Carnival of Shadows
 * Course: CSC3081 - Computer Graphics Programming
 *
 * Purpose:
 * Implements OpenGL rendering for reusable Mesh objects.
 */

#include "pch.h"
#include "MeshRenderer.h"

#include <GL/glut.h>


void MeshRenderer::renderWireframe(const Mesh& mesh) const
{
    glBegin(GL_LINES);

    for (const Edge& edge : mesh.edges)
    {
        const Vertex& start = mesh.vertices[edge.startIndex];
        const Vertex& end = mesh.vertices[edge.endIndex];

        glVertex3f(start.x, start.y, start.z);
        glVertex3f(end.x, end.y, end.z);
    }

    glEnd();
}


void MeshRenderer::renderSolid(const Mesh& mesh) const
{
    for (size_t faceIndex = 0;
        faceIndex < mesh.faces.size();
        ++faceIndex)
    {
        const Face& face = mesh.faces[faceIndex];

        glBegin(GL_POLYGON);

        // Apply the normal belonging to this face.
        if (faceIndex < mesh.normals.size())
        {
            const Normal& normal = mesh.normals[faceIndex];

            glNormal3f(
                normal.x,
                normal.y,
                normal.z
            );
        }

        for (int vertexIndex : face.vertexIndices)
        {
            const Vertex& vertex = mesh.vertices[vertexIndex];

            glVertex3f(
                vertex.x,
                vertex.y,
                vertex.z
            );
        }

        glEnd();
    }
}