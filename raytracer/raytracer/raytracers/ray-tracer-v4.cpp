#include "raytracers/ray-tracer-v4.h"


#include <iostream>


using namespace imaging;
using namespace math;
using namespace raytracer;
using namespace std;

//overschrijven van gevraagde methode 
Color raytracer::raytracers::_private_::RayTracerV4::process_light_ray(const Scene& scene, const MaterialProperties& props, const Hit& hit, const math::Ray& ray, const LightRay& lightray) const
{
	//black omdat een schaduw zwart is
	Color result = colors::black();
	Hit rayhit;

	if (scene.root->find_first_positive_hit(lightray.ray, &rayhit))
	{
	
		double t = rayhit.t;

		//Note that if there’s no shadow, the ray will hit the scene at t=1. However, your CPU is not capable of performing arbitrarily precise arithmetic and it might be that instead of t=1, you get t=0.99999999978 or 1.0000000096
		if ((0.00 <= t) && (t <= 0.99))
		{
			//return black
			return result;
		}
	}
	//gewoon toevoegen aan wat raytracer 3 zou doen
	result += RayTracerV3::process_light_ray(scene, props, hit, ray, lightray);
	return result;
}

//zoals gewoonlijk de factory function
raytracer::RayTracer raytracer::raytracers::v4()
{
	return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV4>());
}