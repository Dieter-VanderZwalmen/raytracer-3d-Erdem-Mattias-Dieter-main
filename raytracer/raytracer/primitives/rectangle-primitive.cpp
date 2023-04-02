#include "primitives/rectangle-primitive.h"
#include "math/interval.h"

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;

namespace
{
	class rectangleYZImplementation : public raytracer::primitives::_private_::PrimitiveImplementation
	{
	protected:
		const Vector3D m_normal;
		const double m_width;
		const double m_height;

		
	public:
		//constructor  gets the rectangle's width and height as x_size and y_size
		rectangleYZImplementation(double x_size, double y_size)
			: m_width(x_size), m_height(y_size) {}

		
	
		math::Box bounding_box() const override
		{
			return Box(interval(-0.01, 0.01), interval(-m_width / 2, m_width / 2), interval(-m_height / 2, m_height / 2));
			
		}

		//virtual bool find_first_positive_hit(const math::Ray& ray, Hit* hit) const;
		bool find_first_positive_hit(const Ray& ray, Hit* hit) const override
		{

			auto hits = find_all_hits(ray);
			if (hits.size() > 0)
			{
				auto found = hits.back();
				if (found->t > 0 && found->t < hit->t)
				{
					*hit = *found;
					return true;
				}
			}
			return false;
		}
		//virtual std::vector<std::shared_ptr<Hit>> find_all_hits(const math::Ray& ray) const = 0;
		std::vector<std::shared_ptr<Hit>> find_all_hits(const math::Ray& ray) const override
		{
			std::vector<std::shared_ptr<Hit>> hits;
			double t = -ray.origin.x() / ray.direction.x();
			if (t > 0)
			{
				double y = ray.origin.y() + t * ray.direction.y();
				double z = ray.origin.z() + t * ray.direction.z();
				if (y >= -m_width / 2 && y <= m_width / 2 && z >= -m_height / 2 && z <= m_height / 2)
				{
					std::shared_ptr<Hit> hit = std::make_shared<Hit>();
					hit->t = t;
					hit->position = ray.at(hit->t);
					hit->local_position.xyz = hit->position;
					hit->local_position.uv = Point2D(hit->position.y(), hit->position.z());
					hit->normal = ray.origin.x() > 0 ? m_normal : -m_normal;
					hits.push_back(hit);
				}
			}
			return hits;
		}
		

		
	};
	class rectangleXZImplementation : public raytracer::primitives::_private_::PrimitiveImplementation
		{
		protected:
			const Vector3D m_normal;
			const double m_width;
			const double m_height;
			
		public:
			//constructor  gets the rectangle's width and height as x_size and y_size
			rectangleXZImplementation(double x_size, double y_size)
				: m_width(x_size), m_height(y_size) {}

			//virtual bool find_first_positive_hit(const math::Ray& ray, Hit* hit) const;
			bool find_first_positive_hit(const Ray& ray, Hit* hit) const override
			{

				auto hits = find_all_hits(ray);
				if (hits.size() > 0)
				{
					auto found = hits.back();
					if (found->t > 0 && found->t < hit->t)
					{
						*hit = *found;
						return true;
					}
				}
				return false;
			}
			//virtual std::vector<std::shared_ptr<Hit>> find_all_hits(const math::Ray& ray) const = 0;
			std::vector<std::shared_ptr<Hit>> find_all_hits(const math::Ray& ray) const override
			{
				std::vector<std::shared_ptr<Hit>> hits;
				double t = -ray.origin.y() / ray.direction.y();
				if (t > 0)
				{
					double x = ray.origin.x() + t * ray.direction.x();
					double z = ray.origin.z() + t * ray.direction.z();
					if (x >= -m_width / 2 && x <= m_width / 2 && z >= -m_height / 2 && z <= m_height / 2)
					{
						std::shared_ptr<Hit> hit = std::make_shared<Hit>();
						hit->t = t;
						hit->position = ray.at(hit->t);
						hit->local_position.xyz = hit->position;
						hit->local_position.uv = Point2D(hit->position.x(), hit->position.z());
						hit->normal = ray.origin.y() > 0 ? m_normal : -m_normal;
						hits.push_back(hit);
					}
				}
				return hits;
			}
			Box bounding_box() const override
			{
				return Box(interval(-1.0, 1.0), interval(-0.01, 0.01), interval(-1.0, 1.0));
			}
			
		};
	class rectangleXYImplementation : public raytracer::primitives::_private_::PrimitiveImplementation
	{
	protected:
		const Vector3D m_normal;
		const double m_width;
		const double m_height;
	public:

		//constructor  gets the rectangle's width and height as x_size and y_size
		rectangleXYImplementation(double x_size, double y_size)
			: m_width(x_size), m_height(y_size) {}


		//find all hits en bounding box zijn verplicht!
		
		//find all hits
		std::vector<std::shared_ptr<Hit>> find_all_hits(const math::Ray& ray) const override
		{
			std::vector<std::shared_ptr<Hit>> hits;
			double t = -ray.origin.z() / ray.direction.z();
			if (t > 0)
			{
				double x = ray.origin.x() + t * ray.direction.x();
				double y = ray.origin.y() + t * ray.direction.y();
				if (x >= -m_width / 2 && x <= m_width / 2 && y >= -m_height / 2 && y <= m_height / 2)
				{
					std::shared_ptr<Hit> hit = std::make_shared<Hit>();
					hit->t = t;
					hit->position = ray.at(hit->t);
					hit->local_position.xyz = hit->position;
					hit->local_position.uv = Point2D(hit->position.x(),
						hit->position.y());
					hit->normal = ray.origin.z() > 0 ? m_normal : -m_normal;
					hits.push_back(hit);
				}
			}
			return hits;
		}
		

		//bounding box
		Box bounding_box() const override
		{
			return  Box(interval(-1.0, 1.0), interval(-1.0, 1.0), interval(-0.01, 0.01));
		}


		//find first positive hit
		bool find_first_positive_hit(const Ray& ray, Hit* hit) const override
		{

			auto hits = find_all_hits(ray);
			if (hits.size() > 0)
			{
				auto found = hits.back();
				if (found->t > 0 && found->t < hit->t)
				{
					*hit = *found;
					return true;
				}
			}
			return false;
		}
	};
			

};


Primitive raytracer::primitives::xy_rectangle(double x_size, double y_size)
{
	return Primitive(std::make_shared<rectangleXYImplementation>(x_size, y_size));
}
//XZ
Primitive raytracer::primitives::xz_rectangle(double x_size, double z_size)
{
	return Primitive(std::make_shared<rectangleXZImplementation>(x_size, z_size));
}
//YZ
Primitive raytracer::primitives::yz_rectangle(double y_size, double z_size)
{
	return Primitive(std::make_shared<rectangleYZImplementation>(y_size, z_size));
}

	
	