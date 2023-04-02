#include "primitives/bbacc.h"

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;

namespace
{
    class BoundingBoxAcceleratorImplementation : public raytracer::primitives::_private_::PrimitiveImplementation
    {
	public:
        Primitive primitive;

		Box box;

		BoundingBoxAcceleratorImplementation(const Primitive primitive) : primitive(primitive), box(primitive->bounding_box()){}
			
		Box bounding_box() const override {
			return box;
		}

		std::vector<std::shared_ptr<Hit>> find_all_hits(const Ray& ray) const override
		{
			if (box.is_hit_positively_by(ray))
			{
				return primitive->find_all_hits(ray);
			}
			return std::vector<std::shared_ptr<Hit>>();
		}
    };
}

Primitive raytracer::primitives::bounding_box_accelerator(const Primitive primitive)
{
	return Primitive(std::make_shared<BoundingBoxAcceleratorImplementation>(primitive));
}
