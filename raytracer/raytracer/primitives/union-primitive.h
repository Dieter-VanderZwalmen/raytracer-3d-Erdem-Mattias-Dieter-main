#pragma once

#include "primitives/primitive.h"


namespace raytracer
{
    namespace primitives
    {
        Primitive make_union(const std::vector<Primitive>&);
    }
}