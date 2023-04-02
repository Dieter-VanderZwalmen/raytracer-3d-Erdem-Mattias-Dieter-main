#pragma once

#include "raytracers/ray-tracer.h"
#include "raytracers/ray-tracer-v1.h"
#include "raytracers/ray-tracer-v2.h"
#include <memory>


namespace raytracer
{
    namespace raytracers
    {
        namespace _private_
        {
            class RayTracerV3 : public RayTracerV2
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
            protected:
                imaging::Color process_light_ray(const Scene& scene, const MaterialProperties& materialProperties, const Hit& hit, const math::Ray& eye_ray, const LightRay& light_ray) const override;
                imaging::Color compute_specular(const MaterialProperties& materialProperties, const Hit& hit, const math::Ray& eye_ray, const LightRay& light_ray) const;
            };
        }

        /// <summary>
        /// Creates simplest ray tracer.
        /// </summary>
        RayTracer v3();
    }
}