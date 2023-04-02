#pragma once

#include "raytracers/ray-tracer-v7.h"
#include <memory>

namespace raytracer
{
	namespace raytracers
	{
		namespace _private_
		{
			class RayTracerV8 : public RayTracerV7
			{
			public:

			protected:
				imaging::Color compute_refraction(const Scene&, const MaterialProperties&, const math::Ray&, const Hit&, double) const;
				math::Ray compute_refracted_ray(const Scene& scene, const math::Ray& ray, const Hit& hit, double n1, double n2) const;
				imaging::Color determine_color(const Scene& scene, const MaterialProperties& material_properties, const Ray& ray, const Hit& hit, double weight) const override;

			};
		}
		RayTracer v8();
	}
}