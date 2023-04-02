#include "raytracers/ray-tracer-v3.h"

using namespace imaging;
using namespace math;
using namespace raytracer;

Color raytracer::raytracers::_private_::RayTracerV3::process_light_ray(const Scene& scene, const MaterialProperties& props, const Hit& hit, const math::Ray& ray, const LightRay& lightray) const
{
	Color result = colors::black();
	result += RayTracerV2::process_light_ray(scene, props, hit, ray, lightray);
	result += compute_specular(props, hit, ray, lightray);

	return result;
}

Color raytracer::raytracers::_private_::RayTracerV3::compute_specular(const MaterialProperties& props, const Hit& hit, const math::Ray& ray, const LightRay& lightray) const
{
	Color result = colors::black();
	Vector3D direction_Incoming = (hit.position - lightray.ray.origin).normalized();
	Vector3D direction_Reflected = direction_Incoming.reflect_by(hit.normal);
	Vector3D unit_Vector = (ray.origin - hit.position).normalized();
	double cos_Alpha = unit_Vector.dot(direction_Reflected);

	if (cos_Alpha > 0)
	{
		result += (lightray.color * props.specular * pow(cos_Alpha, props.specular_exponent));
	}

	return result;
}

raytracer::RayTracer raytracer::raytracers::v3()
{
    return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV3>());
}