#pragma once

#include "raytracers/ray-tracer.h"
#include <memory>


namespace raytracer
{
    namespace raytracers
    {
        namespace _private_
        {
            class RayTracerV1 : public RayTracerImplementation
            {
            public:
                /// <summary>
                /// Traces the given ray.
                /// </summary>
                /// <param name="scene">
                /// Scene to be rendered.
                /// </param>
                /// <param name="eye_ray">
                /// Ray originating in the camera's eye and travelling through the scene.
                /// </param>
                /// <returns>
                /// Information about how to render the point where the eye_ray intersects the scene.
                /// </returns>
                TraceResult trace(const Scene& scene, const math::Ray& eye_ray) const override;
            protected:
                imaging::Color compute_ambient(const MaterialProperties& materialProperties) const;
                virtual imaging::Color RayTracerV1::determine_color(const Scene& scene, const MaterialProperties& materialProperties, const Hit& hit, const math::Ray& ray) const;

            };
        }

        /// <summary>
        /// Creates simplest ray tracer.
        /// </summary>
        RayTracer v1();
    }
}