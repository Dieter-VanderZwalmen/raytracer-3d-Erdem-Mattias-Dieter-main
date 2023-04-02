#pragma once

#include "raytracers/ray-tracer-v5.h"
#include <memory>

using namespace imaging;
using namespace math;

namespace raytracer
{
	namespace raytracers
	{
		namespace _private_
		{
			class RayTracerV6 : public RayTracerV5
			{
			public:
				TraceResult trace(const Scene& scene, const math::Ray& eye_ray) const override;
			protected:
				TraceResult trace(const Scene& scene, const Ray& eye_ray, double weight) const;
				virtual imaging::Color determine_color(const Scene& scene, const MaterialProperties& material_properties, const Ray& ray, const Hit& hit, double weight) const;
				imaging::Color compute_reflection(const Scene& scene, const MaterialProperties& material, const Ray& ray, const Hit& hit, double weight) const;
			};
		}
		RayTracer v6();
	}
}