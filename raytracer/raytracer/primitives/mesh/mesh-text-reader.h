#pragma once

#include "primitives/primitive.h"
#include "primitives/mesh/mesh-receiver.h"
#include <iostream>


namespace raytracer
{
    namespace primitives
    {
        void read_text_mesh(std::istream& input_stream, MeshReceiver& receiver);
    }
}