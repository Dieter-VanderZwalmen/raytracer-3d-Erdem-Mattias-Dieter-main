#include "primitives/mesh/mesh-text-reader.h"
#include <fstream>
#include "easylogging++.h"


using namespace raytracer;


namespace
{
    void read_vertices(std::istream& input_stream, raytracer::primitives::MeshReceiver& receiver, unsigned n_vertices)
    {
        LOG(INFO) << "Reading " << n_vertices << " vertices";

        for (unsigned i = 0; i != n_vertices; ++i)
        {
            double x, y, z;
            input_stream >> x >> y >> z;

            receiver.vertex(x, y, z);
        }
    }

    void read_normals(std::istream& input_stream, raytracer::primitives::MeshReceiver& receiver, unsigned n_normals)
    {
        LOG(INFO) << "Reading " << n_normals << " normals";

        for (unsigned i = 0; i != n_normals; ++i)
        {
            double x, y, z;
            input_stream >> x >> y >> z;

            receiver.normal(x, y, z);
        }
    }

    void read_hierarchy(std::istream& input_stream, raytracer::primitives::MeshReceiver& receiver)
    {
        LOG(INFO) << "Reading hierarchy";

        while (true)
        {
            std::string tag;
			
            input_stream >> tag;

            if (tag == "t")
            {
                unsigned i, j, k;
                input_stream >> i >> j >> k;

                receiver.triangle(i, j, k);
            }
            else if (tag == "b")
            {
                unsigned n;
                input_stream >> n;

                receiver.box(n);
            }
            else if (tag == "end")
            {
                break;
            }
            else
            {
               LOG(ERROR) << "Unrecognized tag \"" << tag << "\"" << std::endl;
               abort();
            }
        }
    }
}

void raytracer::primitives::read_text_mesh(std::istream& input_stream, raytracer::primitives::MeshReceiver& receiver)
{
    TIMED_FUNC(timerObj);
    LOG(INFO) << "Loading text mesh...";

    unsigned n_vertices, n_normals;
    input_stream >> n_vertices >> n_normals;

    read_vertices(input_stream, receiver, n_vertices);
    read_normals(input_stream, receiver, n_normals);
    read_hierarchy(input_stream, receiver);
}