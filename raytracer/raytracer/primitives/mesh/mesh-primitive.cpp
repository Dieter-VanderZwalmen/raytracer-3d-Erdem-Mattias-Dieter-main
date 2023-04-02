#include "primitives/mesh/mesh-primitive.h"
#include "util/misc.h"
#include <assert.h>
#include <fstream>
#include <sstream>
#include "logging.h"
//include easylogging
#include "easylogging++.h"


#include "primitives/mesh/mesh-text-reader.h"
#include "mesh-receiver.cpp"

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;





Primitive raytracer::primitives::mesh(const std::string& path) 
{
	//lees file
	std::ifstream obj(path);

	//if file not found throw exception
	if (!obj.is_open())
	{
		//log Failed to open file at <path>
		LOG(ERROR) << "Failed to open file at " << path;
		//return an empty list of primitives
		return Primitive();
	}

	//instantie van mesh-receiver
	RawTextReceiver receiver;
	
	//die meegeven aan mesh-text-reader (file, reciever)
	read_text_mesh(obj, receiver);
	
	//get the m_stack from reciever and pop it to get the mesh and return in
	return receiver.m_stack.top();

}


