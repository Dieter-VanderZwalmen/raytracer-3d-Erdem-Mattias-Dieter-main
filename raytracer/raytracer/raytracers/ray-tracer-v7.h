#pragma once

#include "raytracers/ray-tracer-v6.h"
#include <memory>

namespace raytracer
{
	namespace raytracers
	{
		namespace _private_
		{
			class RayTracerV7 : public RayTracerV6
			{
			public:

			protected:
				imaging::Color compute_translucency(const Scene&, const MaterialProperties&, const math::Ray&, const Hit&, double) const;
				imaging::Color determine_color(const Scene& scene, const MaterialProperties& material_properties, const Ray& ray, const Hit& hit, double weight) const override;

			};
		}
		RayTracer v7();
	}
}