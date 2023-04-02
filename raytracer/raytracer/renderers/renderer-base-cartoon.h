#pragma once

#include "renderers/renderer.h"
#include "imaging/bitmap.h"
#include "raytracers/scene.h"
#include "samplers/sampler.h"
#include "raytracers/ray-tracer.h"
#include "math/rasterizer.h"
#include "math/point.h"
#include "tasks/task-scheduler.h"

namespace raytracer
{
    namespace renderers
    {
        namespace _private_
        {
            class RendererBaseCartoonImplementation : public RendererImplementation
            {
            public:
                virtual std::shared_ptr<imaging::Bitmap> render(const Scene& scene) const = 0;

            protected:
                RendererBaseCartoonImplementation(unsigned, unsigned, unsigned, raytracer::Sampler, RayTracer, tasks::TaskScheduler);

                unsigned m_horizontal_size, m_vertical_size, m_shade_count;
                raytracer::Sampler m_sampler;
                RayTracer m_ray_tracer;

                /// <summary>
                /// Calls given function <paramref name="callback" /> for each pixel.
                /// </summary>
                void for_each_pixel(std::function<void(Position2D)> callback) const;

            private:
                tasks::TaskScheduler m_scheduler;
            };
        }
    }
}