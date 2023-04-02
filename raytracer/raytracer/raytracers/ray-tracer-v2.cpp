#include "raytracers/ray-tracer-v2.h"

using namespace imaging;
using namespace math;
using namespace raytracer;


imaging::Color raytracer::raytracers::_private_::RayTracerV2::determine_color(const Scene& scene, const MaterialProperties& materialProperties, const Hit& hit, const math::Ray& eye_ray) const
{
    Color result = imaging::colors::black();

    //Call old version of determine_color;
    result += RayTracerV1::determine_color(scene, materialProperties, hit, eye_ray);

    //Process all lights in the scene;
    result += process_lights(scene, materialProperties, hit, eye_ray);

    return result;
}

imaging::Color raytracer::raytracers::_private_::RayTracerV2::process_lights(const Scene& scene, const MaterialProperties& materialProperties, const Hit& hit, const math::Ray& eye_ray) const
{
    Color result = imaging::colors::black();

    for each (LightSource light_source in scene.light_sources)
    {
        result += process_light_source(scene, materialProperties, hit, eye_ray, light_source);
    }

    return result;
}

imaging::Color raytracer::raytracers::_private_::RayTracerV2::process_light_source(const Scene& scene, const MaterialProperties& materialProperties, const Hit& hit, const math::Ray& eye_ray, const LightSource& light_source) const
{
    Color result = imaging::colors::black();

    for each (LightRay light_ray in light_source->lightrays_to(hit.position))
    {
        result += process_light_ray(scene, materialProperties, hit, eye_ray, light_ray);
    }

    return result;
}

imaging::Color raytracer::raytracers::_private_::RayTracerV2::process_light_ray(const Scene& scene, const MaterialProperties& materialProperties, const Hit& hit, const math::Ray& eye_ray, const LightRay& light_ray) const
{
    Color result = imaging::colors::black();

    result += compute_diffuse(materialProperties, hit, eye_ray, light_ray);

    return result;
}

imaging::Color raytracer::raytracers::_private_::RayTracerV2::compute_diffuse(const MaterialProperties& materialProperties, const Hit& hit, const math::Ray& eye_ray, const LightRay& light_ray) const
{
    //First extract all information from arguments
    math::Vector3D n = hit.normal;
    math::Point3D L = light_ray.ray.origin;
    math::Point3D P = hit.position;
    math::Vector3D LP_normalized = (L - P).normalized();
    Color CL = light_ray.color;
    Color CS = materialProperties.diffuse;

    double cos = cos_of_angle_between(n, LP_normalized);

    if (cos > 0)
    {
        return cos * CL * CS;
    }
    else 
    {
        return imaging::colors::black();
    }
}

raytracer::RayTracer raytracer::raytracers::v2()
{
    return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV2>());
}