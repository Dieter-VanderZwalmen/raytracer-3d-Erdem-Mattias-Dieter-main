#include "raytracers/ray-tracers.h"

using namespace imaging;
using namespace math;
using namespace raytracer;

TraceResult raytracer::raytracers::_private_::RayTracerV6::trace(const Scene& scene, const Ray& ray) const
{
	return trace(scene, ray, 1.0);
}

TraceResult raytracer::raytracers::_private_::RayTracerV6::trace(const Scene& scene, const Ray& ray, double weight) const
{
	TraceResult hit = TraceResult::no_hit(ray);
	if (weight > 0.01)
	{
		Hit reflect;
		if (scene.root->find_first_positive_hit(ray, &reflect))
		{
			double t = reflect.t;
			MaterialProperties props = reflect.material->at(reflect.local_position);
			Color color = determine_color(scene, props, ray, reflect, weight); 
			unsigned group_id = reflect.group_id;
			return TraceResult(color, group_id, ray, t);
		}
	}
	return hit;
}

imaging::Color raytracer::raytracers::_private_::RayTracerV6::determine_color(const Scene& scene, const MaterialProperties& material_properties, const Ray& ray, const Hit& hit, double weight) const
{
	Color result = colors::black();
	result += RayTracerV2::determine_color(scene, material_properties, hit, ray);
	result += compute_reflection(scene, material_properties, ray, hit, weight);

	return result;
}

imaging::Color raytracer::raytracers::_private_::RayTracerV6::compute_reflection(const Scene& scene, const MaterialProperties& material, const Ray& ray, const Hit& hit, double weight) const
{
	Color result = colors::black();
	if (material.reflectivity > 0)
	{
		Vector3D direction_Incoming = (hit.position - ray.origin).normalized();
		Vector3D direction_Reflected = direction_Incoming.reflect_by(hit.normal);
		Point3D new_Origin = ray.at(hit.t) + 0.00000001 * direction_Reflected;
		Ray reflection = Ray(new_Origin, direction_Reflected);
		Color reflection_color = trace(scene, reflection, material.reflectivity * weight).color;
		result += (material.reflectivity * reflection_color);
	}
	return result;
}

RayTracer raytracer::raytracers::v6()
{
	return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV6>());
}