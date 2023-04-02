#pragma once
#pragma once

#include "renderers/renderer.h"
#include <functional>


namespace raytracer
{
    namespace renderers
    {
        Renderer cartoon(unsigned width, unsigned height, unsigned shade_count, raytracer::Sampler sampler, RayTracer ray_tracer, tasks::TaskScheduler scheduler);
    }
}