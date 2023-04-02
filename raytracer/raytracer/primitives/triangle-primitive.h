#pragma once

#include "primitives/primitive.h"




//ik ben gaan kijken naar sphere-primitive om op dit te komen
namespace raytracer
{
    
    namespace primitives
    {
        //primitive triangle() with 3 points
	    Primitive triangle(const math::Point3D& a, const math::Point3D& b, const math::Point3D& c);
    }
}