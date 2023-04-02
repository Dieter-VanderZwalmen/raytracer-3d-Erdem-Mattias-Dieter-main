#include "raytracers/ray-tracers.h"
#include "ray-tracer-v8.h"

using namespace imaging;
using namespace math;
using namespace raytracer;

imaging::Color raytracer::raytracers::_private_::RayTracerV8::compute_refraction(const Scene& scene, const MaterialProperties& props, const math::Ray& ray, const Hit& hit, double weight) const
{
	if (props.transparency > 0)
	{
		Ray refracted_ray = compute_refracted_ray(scene, ray, hit, 1.0, props.refractive_index);
		if (refracted_ray == ray)
		{
			return colors::black();
		}
		Hit exit_hit;

		if (scene.root->find_first_positive_hit(refracted_ray, &exit_hit))
		{
			Ray exit_ray = compute_refracted_ray(scene, refracted_ray, exit_hit, props.refractive_index, 1.0);
			return trace(scene, exit_ray, weight * props.transparency).color * props.transparency;
		}
	}
	return colors::black();
}

math::Ray raytracer::raytracers::_private_::RayTracerV8::compute_refracted_ray(const Scene& scene, const math::Ray& ray, const Hit& hit, double n1, double n2) const
{
	Vector3D direction_incoming = (hit.position - ray.origin).normalized();
	Vector3D outgoing_x = (n1 / n2) * (direction_incoming - (direction_incoming.dot(hit.normal)) * hit.normal);
	if ((1 - outgoing_x.norm_sqr()) < 0)
	{
		return ray;
	}

	Vector3D outgoing_y = (0 - sqrt(1 - outgoing_x.norm_sqr())) * hit.normal;
	Vector3D direction_outgoing = outgoing_x + outgoing_y;
	Point3D outgoing_origin = ray.at(hit.t) + (0.00000001 * direction_outgoing);
	Ray refracted_ray = Ray(outgoing_origin, direction_outgoing);

	return refracted_ray;
}

imaging::Color raytracer::raytracers::_private_::RayTracerV8::determine_color(const Scene& scene, const MaterialProperties& material_properties, const Ray& ray, const Hit& hit, double weight) const
{
	Color result = colors::black();
	result += RayTracerV7::determine_color(scene, material_properties, ray, hit, weight);
	result += compute_refraction(scene, material_properties, ray, hit, weight);
	return result;
}

RayTracer raytracer::raytracers::v8()
{
	return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV8>());
}

