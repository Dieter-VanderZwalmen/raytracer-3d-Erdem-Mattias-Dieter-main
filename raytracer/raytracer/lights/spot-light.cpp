#include "lights/spot-light.h"

using namespace math;
using namespace raytracer;

namespace
{
    class SpotLight : public raytracer::lights::_private_::PointLightImplementation
    {
    public:
        SpotLight(const math::Point3D& position, const math::Vector3D& direction, const math::Angle& angle, const imaging::Color& color)
            : PointLightImplementation(position), m_color(color), m_angle(angle), m_direction(direction) { }

        SpotLight(const math::Point3D& position, const math::Point3D& target, const math::Angle& angle, const imaging::Color& color)
            : PointLightImplementation(position), m_color(color), m_angle(angle), m_target(target)
        {
			m_direction = (m_target - m_position).normalized();
        }

    protected:
        LightRay cast_lightray_to(const math::Point3D& p) const override
        {
            math::Ray ray(m_position, p);
            double cosine = cos(m_angle / 2);
            Vector3D m_direction_normalized = (p - m_position).normalized();
			
			if (m_direction_normalized.dot(m_direction) >= cosine)
			{
				return LightRay(ray, m_color);
			}
			return LightRay(ray, imaging::colors::black());
        }

    private:
        Vector3D m_direction;
		Point3D m_target;
        Angle m_angle;
        imaging::Color m_color;
    };
}

LightSource raytracer::lights::spot(const math::Point3D& position, const math::Vector3D& direction, const math::Angle& angle, const imaging::Color& color)
{
    return LightSource(std::make_shared<SpotLight>(position, direction, angle, color));
}

LightSource raytracer::lights::spot(const math::Point3D& position, const math::Point3D& target, const math::Angle& angle, const imaging::Color& color)
{
    return LightSource(std::make_shared<SpotLight>(position, target, angle, color));
}
