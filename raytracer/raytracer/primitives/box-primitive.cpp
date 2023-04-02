
#include "primitives/box-primitive.h"

#include "primitives/rectangle-primitive.h"
#include "primitive.h"
#include "primitives/transformer-primitive.h"



using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;	
namespace {


	class BoxPrimitive : public raytracer::primitives::_private_::PrimitiveImplementation
	{
	
	public:
			
		BoxPrimitive(double x_size, double y_size, double z_size) : x_size(x_size), y_size(y_size), z_size(z_size)
		{
			//xy square translated
			m_rectangles.push_back(raytracer::primitives::translate(Vector3D(0, 0, z_size / 2), raytracer::primitives::xy_rectangle(x_size, y_size)));

			////xz square translated
			m_rectangles.push_back(raytracer::primitives::translate(Vector3D(0, y_size / 2, 0), raytracer::primitives::xz_rectangle(x_size, z_size)));

			////yz square translated
			m_rectangles.push_back(raytracer::primitives::translate(Vector3D(x_size / 2, 0, 0), raytracer::primitives::yz_rectangle(y_size, z_size)));

			////xy square translated
			m_rectangles.push_back(raytracer::primitives::translate(Vector3D(0, 0, -z_size / 2), raytracer::primitives::xy_rectangle(x_size, y_size)));

			////xz square translated
			m_rectangles.push_back(raytracer::primitives::translate(Vector3D(0, -y_size / 2, 0), raytracer::primitives::xz_rectangle(x_size, z_size)));

			////yz square translated
			m_rectangles.push_back(raytracer::primitives::translate(Vector3D(-x_size / 2, 0, 0), raytracer::primitives::yz_rectangle(y_size, z_size)));
			
			
		}

		//pas dit nog aan aub
		Box bounding_box() const override
		{
			auto x = interval(-x_size/2, x_size/2);
			auto y = interval(-y_size / 2, y_size / 2);
			auto z = interval(-z_size / 2, z_size / 2);

			return Box(x, y, z);
		}

		

		//virtual bool find_first_positive_hit(const math::Ray& ray, Hit* hit) const;
		bool find_first_positive_hit(const math::Ray& ray, Hit* hit) const override
		{
			auto hits = find_all_hits(ray);
			if (hits.size() > 0)
			{
				auto& found = hits.back();
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
			for (auto& rectangle : m_rectangles)
			{
				//find the hits of the rectangle
				auto rectangle_hits = rectangle->find_all_hits(ray);
				hits.insert(hits.end(), rectangle_hits.begin(), rectangle_hits.end());
			}
			return hits;
		}

		
		
	protected:
		std::vector<Primitive> m_rectangles;
		double x_size;
		double y_size;
		double z_size;

		
	};
		

};



Primitive raytracer::primitives::box(double x_size, double y_size, double z_size)
{
	return Primitive(std::make_shared<BoxPrimitive>(x_size, y_size, z_size));
}
