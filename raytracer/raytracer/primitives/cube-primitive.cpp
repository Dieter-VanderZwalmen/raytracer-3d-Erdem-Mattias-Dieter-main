
#include "primitive.h"
#include "primitives/cube-primitive.h"
#include "primitives/square-primitive.h"
#include "primitives/transformer-primitive.h"

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;


namespace {
	class CubePrimitive : public raytracer::primitives::_private_::PrimitiveImplementation
	{
		//create a cube primitive
		//that is made out of 6 squares
		//the cube centered around (0,0,0)
		//the cube is always of size (1,1,1)

	public:
		std::vector<Primitive> m_squares;

		CubePrimitive()
		{

		
			
			//xy square translated
			m_squares.push_back(raytracer::primitives::translate(Vector3D(0, 0, 0.5), raytracer::primitives::xy_square(1)));

			//xz square translated
			m_squares.push_back(raytracer::primitives::translate(Vector3D(0, 0.5, 0), raytracer::primitives::xz_square(1)));
			
			//yz square translated
			m_squares.push_back(raytracer::primitives::translate(Vector3D(0.5, 0, 0), raytracer::primitives::yz_square(1)));

			//xy square translated
			m_squares.push_back(raytracer::primitives::translate(Vector3D(0, 0, -0.5), raytracer::primitives::xy_square(1)));

			//xz square translated
			m_squares.push_back(raytracer::primitives::translate(Vector3D(0, -0.5, 0), raytracer::primitives::xz_square(1)));

			//yz square translated
			m_squares.push_back(raytracer::primitives::translate(Vector3D(-0.5, 0, 0), raytracer::primitives::yz_square(1)));
			



		}


		//bounding box
		Box bounding_box() const override
		{
			auto x = interval(-0.5, 0.5);
			auto y = interval(-0.5, 0.5);
			auto z = interval(-0.5, 0.5);

			return Box(x, y, z);
		}

		//find first positive hit
		virtual bool find_first_positive_hit(const math::Ray& ray, Hit* hit) const override
		{
			//loop through all squares
			//and find the first positive hit
			for (auto& square : m_squares)
			{
				if (square->find_first_positive_hit(ray, hit))
				{
					return true;
				}
			}
			return false;
		}


		//find all hits
		std::vector<std::shared_ptr<Hit>> find_all_hits(const math::Ray& ray) const override
		{
			std::vector<std::shared_ptr<Hit>> hits;
			//loop through all squares
			//and find all hits
			for (auto& square : m_squares)
			{
				auto temp = square->find_all_hits(ray);
				hits.insert(hits.end(), temp.begin(), temp.end());
			}
			return hits;

		}
	};
};



Primitive raytracer::primitives::cube()
{
	return Primitive(std::make_shared<CubePrimitive>());
}
