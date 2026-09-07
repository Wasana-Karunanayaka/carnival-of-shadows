/*
 * File: MeshRenderer.h
 * Project: Carnival of Shadows
 * Course: CSC3081 - Computer Graphics Programming
 *
 * Purpose:
 * Declares the renderer responsible for converting Mesh data
 * into OpenGL drawing commands.
 */

#pragma once

#include "Mesh.h"


class MeshRenderer
{
public:

    /*
     * Draws only the edges of a mesh.
     */
    void renderWireframe(const Mesh& mesh) const;


    /*
     * Draws the polygonal faces of a mesh.
     *
     * Face normals are passed to OpenGL so lighting can
     * shade the surfaces correctly.
     */
    void renderSolid(const Mesh& mesh) const;
};