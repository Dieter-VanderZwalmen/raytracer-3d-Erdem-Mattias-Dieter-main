#pragma once

#include "primitives/primitive.h"

namespace raytracer
{
	namespace primitives
	{
		Primitive xy_rectangle(double x_size, double  y_size);
		Primitive xz_rectangle(double x_size, double z_size);
		Primitive yz_rectangle(double y_size, double z_size);
		
	}
}
