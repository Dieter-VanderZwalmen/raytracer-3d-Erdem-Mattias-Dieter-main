#include "raytracers/ray-tracers.h"

using namespace imaging;
using namespace math;
using namespace raytracer;

imaging::Color raytracer::raytracers::_private_::RayTracerV7::compute_translucency(const Scene& scene, const MaterialProperties& material, const math::Ray& ray, const Hit& hit, double weight) const
{
	Color result = colors::black();
	double translucency = material.translucency;
	if (translucency > 0)
	{
		Vector3D new_direction = (hit.position - ray.origin).normalized();
		Point3D new_origin = ray.at(hit.t) + 0.00000001 * new_direction;
		Ray new_ray = Ray(new_origin, new_direction);
		Color new_color = RayTracerV6::trace(scene, new_ray, translucency * weight).color;
		result += (translucency * new_color);
	}
	return result;
}

imaging::Color raytracer::raytracers::_private_::RayTracerV7::determine_color(const Scene& scene, const MaterialProperties& material_properties, const Ray& ray, const Hit& hit, double weight) const
{
	Color result = colors::black();
	result += RayTracerV6::determine_color(scene, material_properties, ray, hit, weight);
	result += compute_translucency(scene, material_properties, ray, hit, material_properties.translucency);
	return result;
}

RayTracer raytracer::raytracers::v7()
{
	return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV7>());
}