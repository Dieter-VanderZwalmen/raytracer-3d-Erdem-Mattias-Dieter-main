//implement square primitive analog to rectangle-primitive

#include "primitives/square-primitive.h"
#include "math/interval.h"

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;

namespace
{
	class squareYZImplementation : public raytracer::primitives::_private_::PrimitiveImplementation
	{

	public:
		//constructor  gets the rectangle's width and height as x_size and y_size
		squareYZImplementation(double x_size)
			: m_width(x_size) {}



		Box bounding_box() const override
		{
			auto x = interval(-1.0, 1.0);
			auto y = interval(-m_width / 2, m_width / 2);
			auto z = interval(-m_width / 2, m_width / 2);
			
			return Box(x, y, z);
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
		std::vector<std::shared_ptr<Hit>> find_all_hits(const Ray& ray) const override
		{
			std::vector<std::shared_ptr<Hit>> hits;

			double denom = ray.direction.dot(m_normal);

			if (denom != approx(0.0))
			{
				double numer = -((ray.origin - Point3D(0, 0, 0)).dot(m_normal));
				double t = numer / denom;

				if (bounding_box().contains(ray.at(t)))
				{
					auto hit = std::make_shared<Hit>();

					initialize_hit(hit.get(), ray, t);

					hits.push_back(hit);
				}
			}
			return hits;
		}


	protected:
		Vector3D m_normal = Vector3D(1, 0, 0);
		const double m_width;
		void initialize_hit(Hit* hit, const Ray& ray, double t) const
		{
			hit->t = t;
			hit->position = ray.at(hit->t);
			hit->local_position.xyz = hit->position;
			hit->local_position.uv = Point2D(hit->position.x(), hit->position.y());
			hit->normal = ray.origin.x() > 0 ? m_normal : -m_normal;
		}
	};
	class SquareXZImplementation : public raytracer::primitives::_private_::PrimitiveImplementation
{
public:
	//constructor
	SquareXZImplementation(double width)
		: m_width(width) {}

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


	std::vector<std::shared_ptr<Hit>> find_all_hits(const Ray& ray) const override
	{
		std::vector<std::shared_ptr<Hit>> hits;

		double denom = ray.direction.dot(m_normal);

		if (denom != approx(0.0))
		{
			double numer = -((ray.origin - Point3D(0, 0, 0)).dot(m_normal));
			double t = numer / denom;

			if (bounding_box().contains(ray.at(t)))
			{
				auto hit = std::make_shared<Hit>();

				initialize_hit(hit.get(), ray, t);

				hits.push_back(hit);
			}
		}
		return hits;
	}

	//XZ box
	Box bounding_box() const override
	{
		auto y = interval(-1.0, 1.0);
		auto x = interval(-m_width / 2, m_width / 2);
		auto z = interval(-m_width / 2, m_width / 2);

		return Box(x, y, z);
	}
	

protected:
	Vector3D m_normal = Vector3D(0, 1, 0);
	const double m_width;

	void initialize_hit(Hit* hit, const Ray& ray, double t) const
	{
		hit->t = t;
		hit->position = ray.at(hit->t);
		hit->local_position.xyz = hit->position;
		hit->local_position.uv = Point2D(hit->position.x(), hit->position.y());
		hit->normal = ray.origin.x() > 0 ? m_normal : -m_normal;
	}

};
	class SquareXYImplementation : public raytracer::primitives::_private_::PrimitiveImplementation
{
public:
	
	SquareXYImplementation(double width)
		: m_width(width) {}

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


	std::vector<std::shared_ptr<Hit>> find_all_hits(const Ray& ray) const override
	{
		std::vector<std::shared_ptr<Hit>> hits;

		double denom = ray.direction.dot(m_normal);

		if (denom != approx(0.0))
		{
			double numer = -((ray.origin - Point3D(0, 0, 0)).dot(m_normal));
			double t = numer / denom;

			if (bounding_box().contains(ray.at(t)))
			{
				auto hit = std::make_shared<Hit>();

				initialize_hit(hit.get(), ray, t);

				hits.push_back(hit);
			}
		}
		return hits;
	}

	Box bounding_box() const override
	{
		auto y = interval(-m_width / 2, m_width / 2);
		auto x = interval(-m_width / 2, m_width / 2);
		auto z = interval(-1.0, 1.0);

		return Box(x, y, z);
	}

protected:
	Vector3D m_normal = Vector3D(0, 0, 1);
	const double m_width;

	void initialize_hit(Hit* hit, const Ray& ray, double t) const
	{
		hit->t = t;
		hit->position = ray.at(hit->t);
		hit->local_position.xyz = hit->position;
		hit->local_position.uv = Point2D(hit->position.x(), hit->position.y());
		hit->normal = ray.origin.x() > 0 ? m_normal : -m_normal;
	}

};
};

//Primitive xy_square(double x_size);
Primitive raytracer::primitives::xy_square(double x_size)
{
	return Primitive(std::make_shared<SquareXYImplementation>(x_size));
}

//Primitive xz_square(double x_size);
Primitive raytracer::primitives::xz_square(double x_size)
{
	return Primitive(std::make_shared<SquareXZImplementation>(x_size));
}
//Primitive yz_square(double y_size);
Primitive raytracer::primitives::yz_square(double y_size)
{
	return Primitive(std::make_shared<squareYZImplementation>(y_size));
}


	
	