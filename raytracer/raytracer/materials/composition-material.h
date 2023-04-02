#pragma once

#include "materials/material.h"
#include <functional>


namespace raytracer
{
    namespace materials
    {
        Material composite(std::function<Material(const math::Point2D&)> function);
        Material composite(std::function<Material(const math::Point3D&)> function);

        Material composite(math::Function<Material(const math::Point2D&)> function);
        Material composite(math::Function<Material(const math::Point3D&)> function);
    }
}