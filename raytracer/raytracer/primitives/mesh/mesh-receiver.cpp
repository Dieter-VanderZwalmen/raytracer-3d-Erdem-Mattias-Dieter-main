#pragma once

#include <iostream>
#include "primitives/mesh/mesh-receiver.h"
#include <stack>
#include "primitives/triangle-primitive.h"
#include "primitives/union-primitive.h"
#include "primitives/bbacc.h"


using namespace raytracer;
using namespace raytracer::primitives;
using namespace std;
using namespace math;



//subclass of MeshReciever that is used to create a mesh from a file
class RawTextReceiver : public raytracer::primitives::MeshReceiver
{
public:
	RawTextReceiver()   {}

	//called for each vertex in the mesh
	virtual void vertex(double x, double y, double z) override
	{
		//cout << "vertex: " << x << " " << y << " " << z << endl;
		m_vertices.push_back(Point3D(x, y, z));
	}

	//called for each normal in the mesh
	virtual void normal(double x, double y, double z) override
	{
		//hoeft niet!!
	}
	//called for each triangle in the mesh
	virtual void triangle(unsigned vertex1, unsigned vertex2, unsigned vertex3) override
	{
		//put triangle on stack
		m_stack.push(raytracer::primitives::triangle(m_vertices[vertex1], m_vertices[vertex2], m_vertices[vertex3]));
	}

	//called for each box in the mesh
	virtual void box(unsigned n_children) override
	{
		//get the last n_childern from the m_stack
		//and put them in a union
		//then put the union on the stack
		vector<Primitive> primitives;
		for (unsigned i = 0; i < n_children; i++)
		{
			primitives.push_back(m_stack.top());
			m_stack.pop();
		}
		m_stack.push(raytracer::primitives::bounding_box_accelerator(raytracer::primitives::make_union(primitives)));
		
		
	}

	
	
		//create a std::stack
		stack<Primitive> m_stack;
		vector<Point3D> m_vertices;
		
	
};

	