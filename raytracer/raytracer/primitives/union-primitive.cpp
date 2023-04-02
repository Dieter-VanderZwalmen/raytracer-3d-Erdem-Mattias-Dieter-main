#include "primitives/union-primitive.h"
#include "easylogging++.h"
#include <vector>

using namespace math;
using namespace raytracer;
using namespace raytracer::primitives;


namespace
{
    class UnionImplementation : public raytracer::primitives::_private_::PrimitiveImplementation
    {
    public:
        UnionImplementation(const std::vector<Primitive>& children)
            : m_children(children)
        {
            // NOP
        }

        bool find_first_positive_hit(const Ray& ray, Hit* hit) const override
        {
            bool found_hit = false;

            for (const auto& child : this->m_children)
            {
                found_hit = child->find_first_positive_hit(ray, hit) || found_hit;
            }

            return found_hit;
        }

        std::vector<std::shared_ptr<Hit>> find_all_hits(const math::Ray& ray) const override
        {
            std::vector<std::shared_ptr<Hit>> hits;

            for (const auto& child : this->m_children)
            {
                for (auto hit : child->find_all_hits(ray))
                {
                    hits.push_back(hit);
                }
            }

            std::sort(hits.begin(), hits.end(), [](const std::shared_ptr<Hit>& h1, const std::shared_ptr<Hit>& h2)
            {
                return h1->t < h2->t;
            });

            return hits;
        }

        math::Box bounding_box() const override
        {
            Box result = Box::empty();

            for (auto child : this->m_children)
            {
                Box child_box = child->bounding_box();
                result = result.merge(child_box);
            }

            return result;
        }

    private:
        std::vector<Primitive> m_children;
    };
}

Primitive raytracer::primitives::make_union(const std::vector<Primitive>& children)
{
    return Primitive(std::make_shared<UnionImplementation>(children));
}
