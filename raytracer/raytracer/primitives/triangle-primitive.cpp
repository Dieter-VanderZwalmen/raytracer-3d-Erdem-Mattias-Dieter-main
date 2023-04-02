#include "primitives/triangle-primitive.h"
#include "util/misc.h"
#include "math/coordinate-systems.h"
#include "math/quadratic_equation.h"
#include "performance/performance.h"
#include <assert.h>


using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;

//anonymous namespace
namespace
{
	//triangleImplementation class
	class TriangleImplementation : public raytracer::primitives::_private_::PrimitiveImplementation
	{
	private:
		//defineren van de 3 punten van een driehoek
		Point3D a;
		Point3D b;
		Point3D c;
		Vector3D n;
	public:
		

		
		
		//constructor with parameters a,b and c
		//direct initializeren van de paramemters gebeurt na de :
		TriangleImplementation(const Point3D& a, const Point3D& b, const Point3D& c) : a(a), b(b), c(c),n(compute_normal(a, b, c)) {}

		
		//compute normal
		//hoe zou het licht moeten reflecteren op een vlak
		Vector3D compute_normal(const Point3D& a, const Point3D& b, const Point3D& c) const
		{
		
			Vector3D ab = b - a;
			Vector3D ac = c - a;
			Vector3D n = ab.cross(ac);
			n.normalize();
			return n;
		
		}
		

		//find all hits
		//geeft een lijst van alle hits terug
		std::vector<std::shared_ptr<Hit>> find_all_hits(const Ray& ray) const override
		{
			//dit is ge copy paste van wikipedia!!!!!
			// https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm

			std::vector<std::shared_ptr<Hit>> hits;

			double EPSILON = 0.0000001;
			Vector3D vertex0 = Vector3D(a.x(), a.y(), a.z());
			Vector3D vertex1 = Vector3D(b.x(), b.y(), b.z());
			Vector3D vertex2 = Vector3D(c.x(), c.y(), c.z());;
			Vector3D edge1, edge2, h, s, q;
			double a, f, u, v;
			edge1 = vertex1 - vertex0;
			edge2 = vertex2 - vertex0;
			h = ray.direction.cross(edge2);
			a = edge1.dot(h);
			if (a < EPSILON)
			{
				return hits;
			}
			f = 1 / a;
			Vector3D rayOrigin = Vector3D(ray.origin.x(), ray.origin.y(), ray.origin.z());
			s = rayOrigin - vertex0;
			u = f * (s.dot(h));
			if (u < 0.0 || u > 1.0)
			{
				return hits;
			}
			q = s.cross(edge1);
			v = f * ray.direction.dot(q);
			if (v < 0.0 || u + v > 1.0)
			{
				return hits;
			}
			double t = f * edge2.dot(q);
			if (t > 0.0)
			{
				auto hit = std::make_shared<Hit>();
				initialize_hit(hit.get(), ray, t);
				hit->normal = -edge2.cross(edge1);
				hits.push_back(hit);

			}
			return hits;
		}
		
		//find_first_positive_hit
		//geeft de eerste positieve hit terug
		bool find_first_positive_hit(const Ray& ray, Hit* hit) const override
		{
			//vind alle hits
			auto hits = find_all_hits(ray);
			//als ge hits hebt
			if (!hits.empty())
			{
				//uit hits pakken wij de achterste
				auto first_hit = hits.back();

				//als de hit positief is en de hit kleiner is dan de hit die we hebben
				if (first_hit->t > 0 && first_hit->t < hit->t)
				{
					//zet de hit gelijk aan de eerste hit
					*hit = *first_hit;
					//geef true terug
					return true;
				}
				
			}
			return false;
		}

		//implement boundig_box to return an empty box
		
			Box bounding_box() const override
			{
				double min_x = std::min(std::min(a.x(), b.x()), c.x());
				double max_x = std::max(std::max(a.x(), b.x()), c.x());
				double min_y = std::min(std::min(a.y(), b.y()), c.y());
				double max_y = std::max(std::max(a.y(), b.y()), c.y());
				double min_z = std::min(std::min(a.z(), b.z()), c.z());
				double max_z = std::max(std::max(a.z(), b.z()), c.z());
				return Box(interval(min_x, max_x), interval(min_y, max_y), interval(min_z, max_z));
			}
		
		
		
		
		
		
		
		
	protected:
		//initialize hit
		//initialiseert de hit
		void initialize_hit(Hit* hit, const Ray& ray, double t) const 
		{
			//initialiseer de hit
			hit->t = t;
			hit->position = ray.at(t);
			hit->local_position.xyz = hit->position;
			hit->local_position.uv = Point2D(hit->position.x(), hit->position.y());
		}
	};
	
		
	
		
		
	
		
    
}


// factory function for triangle
								
Primitive raytracer::primitives::triangle(const math::Point3D& vertex1,
	const math::Point3D& vertex2,
	const math::Point3D& vertex3) {
	return Primitive(std::make_shared<TriangleImplementation>(vertex1, vertex2, vertex3));

}

