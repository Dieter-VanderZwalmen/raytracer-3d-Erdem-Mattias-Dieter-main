#include "raytracers/ray-tracer-v5.h"

#include <iostream>

using namespace imaging;
using namespace math;
using namespace raytracer;
using namespace std;

Color raytracer::raytracers::_private_::RayTracerV5::process_light_ray(const Scene& scene, const MaterialProperties& props, 
																						const Hit& hit, const math::Ray& ray, const LightRay& lightray) const
{
	std::vector<std::shared_ptr<Hit>> hits = scene.root->find_all_hits(lightray.ray);
	Color color_filter = colors::white();

    for (auto& hit : hits)
    {
        if (0.001 < hit->t && hit->t < 0.999)
        {
            MaterialProperties matprops = hit->material->at(hit->local_position);
            color_filter = color_filter * matprops.light_filtering;
        }
    }
    LightRay surviving_light_ray = LightRay(lightray.ray, lightray.color * color_filter);

    return RayTracerV3::process_light_ray(scene, props, hit, ray, surviving_light_ray);
}

raytracer::RayTracer raytracer::raytracers::v5()
{
	return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV5>());
}