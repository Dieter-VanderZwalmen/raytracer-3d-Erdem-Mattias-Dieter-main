#pragma once

#include "primitives/primitive.h"
#include <iostream>


namespace raytracer
{
    namespace primitives
    {
        class MeshReceiver
        {
        public:
            /// <summary>
            /// Called for each vertex in the mesh.
            /// </summary>
            /// <param name="x">X-coordinate</param>
            /// <param name="y">Y-coordinate</param>
            /// <param name="z">Z-coordinate</param>
            virtual void vertex(double x, double y, double z) = 0;

            /// <summary>
            /// Called for each normal in the mesh.
            /// </summary>
            /// <param name="x">X-coordinate</param>
            /// <param name="y">Y-coordinate</param>
            /// <param name="z">Z-coordinate</param>
            virtual void normal(double x, double y, double z) = 0;

            /// <summary>
            /// Called for each triangle in the mesh.
            /// </summary>
            /// <param name="vertex1">Index of first vertex</param>
            /// <param name="vertex2">Index of second vertex</param>
            /// <param name="vertex3">Index of third vertex</param>
            virtual void triangle(unsigned vertex1, unsigned vertex2, unsigned vertex3) = 0;

            /// <summary>
            /// Called for each box in the mesh.
            /// </summary>
            /// <param name="n_children">Number of children in the box</param>
            virtual void box(unsigned n_children) = 0;


			
        };
    }
}