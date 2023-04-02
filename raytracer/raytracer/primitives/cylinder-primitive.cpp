#include "primitives/cylinder-primitive.h"
#include "util/misc.h"
#include "math/coordinate-systems.h"
#include "math/quadratic_equation.h"
#include "performance/performance.h"
#include <assert.h>

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;


namespace
{
    class CylinderAlongXImplementation : public raytracer::primitives::_private_::PrimitiveImplementation
    {
    public:
        std::vector<std::shared_ptr<Hit>> find_all_hits(const Ray& ray) const override
        {
            Point2D o = Point2D(ray.origin.y(), ray.origin.z());
            Vector2D d = Vector2D(ray.direction.y(), ray.direction.z());

            auto a = d.dot(d);
            auto b = 2 * d.dot(o - Point2D(0, 0));
            auto c = (o - Point2D(0, 0)).norm_sqr() - 1;

            QuadraticEquation qeq(a, b, c);

            if (qeq.has_solutions())
            {
                auto t1 = qeq.x1();
                auto t2 = qeq.x2();

                std::vector<std::shared_ptr<Hit>> hits;

                auto hit1 = std::make_shared<Hit>();
                auto hit2 = std::make_shared<Hit>();


                initialize_hit(hit1.get(), ray, t1);
                initialize_hit(hit2.get(), ray, t2);

                hits.push_back(hit1);
                hits.push_back(hit2);

                return hits;
            }
            else
            {
                // No intersections to be found
                return std::vector<std::shared_ptr<Hit>>();
            }
        }

        math::Box bounding_box() const override
        {
            // Create a [-infinity, infinity] x [-1, 1] x [-1, 1] box.
            auto range = interval(-1.0, 1.0);
            auto inf = interval(-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity());

            return Box(inf, range, range);
        }

    private:
        Point2D compute_uv_from_xyz(const Point3D& p) const
        {
            Cartesian3D cartesian{ p.x(), p.y(), p.z() };
            Spherical spherical = convert_coordinates<Spherical>(cartesian);

            double u = fmod(Interval<Angle>(-180_degrees, 180_degrees).to_relative(spherical.azimuth) + 0.5, 1.0);
            double v = Interval<Angle>(90_degrees, -90_degrees).to_relative(spherical.elevation);

            assert(0 <= u);
            assert(u <= 1);
            assert(0 <= v);
            assert(v <= 1);

            return Point2D(u, v);
        }

        void initialize_hit(Hit* hit, const Ray& ray, double t) const
        {
            // Update Hit object
            hit->t = t;
            hit->position = ray.at(t);
            hit->local_position.xyz = hit->position;
            hit->local_position.uv = compute_uv_from_xyz(hit->position);
            hit->normal = compute_normal_at(ray, hit->position);

            assert(is_on_sphere(hit->position));
        }

        Vector3D compute_normal_at(const Ray& ray, const Point3D& position) const
        {
            assert(is_on_sphere(position));

            Vector3D outward_normal = Vector3D(0, position.y(), position.z());

            Vector3D normal = ray.direction.dot(outward_normal) < 0 ? outward_normal : -outward_normal;

            return normal;
        }

        bool is_on_sphere(const Point3D& p) const
        {
            return distance(Point3D(0, 0, 0), p) == approx(1.0);
        }
    };
	
    class CylinderAlongYImplementation : public raytracer::primitives::_private_::PrimitiveImplementation
    {
    public:
        std::vector<std::shared_ptr<Hit>> find_all_hits(const Ray& ray) const override
        {
            Point2D o = Point2D(ray.origin.x(), ray.origin.z());
            Vector2D d = Vector2D(ray.direction.x(), ray.direction.z());

            auto a = d.dot(d);
            auto b = 2 * d.dot(o - Point2D(0, 0));
            auto c = (o - Point2D(0, 0)).norm_sqr() - 1;

            QuadraticEquation qeq(a, b, c);

            if (qeq.has_solutions())
            {
                auto t1 = qeq.x1();
                auto t2 = qeq.x2();

                std::vector<std::shared_ptr<Hit>> hits;

                auto hit1 = std::make_shared<Hit>();
                auto hit2 = std::make_shared<Hit>();


                initialize_hit(hit1.get(), ray, t1);
                initialize_hit(hit2.get(), ray, t2);

                hits.push_back(hit1);
                hits.push_back(hit2);

                return hits;
            }
            else
            {
                // No intersections to be found
                return std::vector<std::shared_ptr<Hit>>();
            }
        }

        math::Box bounding_box() const override
        {
            // Create a [-1, 1] x [-infinity, infinity] x [-1, 1] box.
            auto range = interval(-1.0, 1.0);
            auto inf = interval(-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity());

            return Box(range, inf, range);
        }

    private:
        Point2D compute_uv_from_xyz(const Point3D& p) const
        {
            Cartesian3D cartesian{ p.x(), p.y(), p.z() };
            Spherical spherical = convert_coordinates<Spherical>(cartesian);

            double u = fmod(Interval<Angle>(-180_degrees, 180_degrees).to_relative(spherical.azimuth) + 0.5, 1.0);
            double v = Interval<Angle>(90_degrees, -90_degrees).to_relative(spherical.elevation);

            assert(0 <= u);
            assert(u <= 1);
            assert(0 <= v);
            assert(v <= 1);

            return Point2D(u, v);
        }

        void initialize_hit(Hit* hit, const Ray& ray, double t) const
        {
            // Update Hit object
            hit->t = t;
            hit->position = ray.at(t);
            hit->local_position.xyz = hit->position;
            hit->local_position.uv = compute_uv_from_xyz(hit->position);
            hit->normal = compute_normal_at(ray, hit->position);

            assert(is_on_sphere(hit->position));
        }

        Vector3D compute_normal_at(const Ray& ray, const Point3D& position) const
        {
            assert(is_on_sphere(position));

            Vector3D outward_normal = Vector3D(position.x(), 0, position.z());

            Vector3D normal = ray.direction.dot(outward_normal) < 0 ? outward_normal : -outward_normal;

            return normal;
        }

        bool is_on_sphere(const Point3D& p) const
        {
            return distance(Point3D(0, 0, 0), p) == approx(1.0);
        }
    };
	
    class CylinderAlongZImplementation : public raytracer::primitives::_private_::PrimitiveImplementation
    {
    public:
        std::vector<std::shared_ptr<Hit>> find_all_hits(const Ray& ray) const override
        {
			Point2D o = Point2D(ray.origin.x(), ray.origin.y());
			Vector2D d = Vector2D(ray.direction.x(), ray.direction.y());
			
			auto a = d.dot(d);
			auto b = 2 * d.dot(o - Point2D(0, 0));
			auto c = (o - Point2D(0, 0)).norm_sqr() - 1;
			
			QuadraticEquation qeq(a, b, c);
			
            if (qeq.has_solutions())
            {
                auto t1 = qeq.x1();
                auto t2 = qeq.x2();
				
				std::vector<std::shared_ptr<Hit>> hits;
				
                auto hit1 = std::make_shared<Hit>();
                auto hit2 = std::make_shared<Hit>();


                initialize_hit(hit1.get(), ray, t1);
                initialize_hit(hit2.get(), ray, t2);

                hits.push_back(hit1);
                hits.push_back(hit2);

                return hits;
            }
            else
            {
                // No intersections to be found
                return std::vector<std::shared_ptr<Hit>>();
            }
        }

        math::Box bounding_box() const override
        {
            // Create a [-1, 1] x [-1, 1] x [-infinity, infinity] box.
            auto range = interval(-1.0, 1.0);
            auto inf = interval(-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity());

            return Box(range, range, inf);
        }

    private:
        Point2D compute_uv_from_xyz(const Point3D& p) const
        {
            Cartesian3D cartesian{ p.x(), p.y(), p.z() };
            Spherical spherical = convert_coordinates<Spherical>(cartesian);

            double u = fmod(Interval<Angle>(-180_degrees, 180_degrees).to_relative(spherical.azimuth) + 0.5, 1.0);
            double v = Interval<Angle>(90_degrees, -90_degrees).to_relative(spherical.elevation);

            assert(0 <= u);
            assert(u <= 1);
            assert(0 <= v);
            assert(v <= 1);

            return Point2D(u, v);
        }

        void initialize_hit(Hit* hit, const Ray& ray, double t) const
        {
            // Update Hit object
            hit->t = t;
            hit->position = ray.at(t);
            hit->local_position.xyz = hit->position;
            hit->local_position.uv = compute_uv_from_xyz(hit->position);
            hit->normal = compute_normal_at(ray, hit->position);

            assert(is_on_sphere(hit->position));
        }

        Vector3D compute_normal_at(const Ray& ray, const Point3D& position) const
        {
            assert(is_on_sphere(position));

			Vector3D outward_normal = Vector3D(position.x(), position.y(), 0);

			Vector3D normal = ray.direction.dot(outward_normal) < 0 ? outward_normal : -outward_normal;

            return normal;
        }

        bool is_on_sphere(const Point3D& p) const
        {
            return distance(Point3D(0, 0, 0), p) == approx(1.0);
        }
    };
}

Primitive raytracer::primitives::cylinder_along_x()
{
    return Primitive(std::make_shared<CylinderAlongXImplementation>());
}

Primitive raytracer::primitives::cylinder_along_y()
{
    return Primitive(std::make_shared<CylinderAlongYImplementation>());
}

Primitive raytracer::primitives::cylinder_along_z()
{
    return Primitive(std::make_shared<CylinderAlongZImplementation>());
}