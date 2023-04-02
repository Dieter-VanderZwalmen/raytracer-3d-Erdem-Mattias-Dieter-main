#include "samplers/random-sampler.h"
#include <random>

using namespace math;
using namespace raytracer;


namespace
{
    class RandomSampler : public raytracer::samplers::_private_::SamplerImplementation
    {
    public:
        int sample_count;
		mutable std::default_random_engine generator;
		mutable std::uniform_real_distribution<double> distribution;
		
		RandomSampler(const int sample_count) : sample_count(sample_count), generator(0), distribution(0, 1) {}
		
        void sample(const math::Rectangle2D& rectangle, std::function<void(const math::Point2D&)> function) const override
        {
			for (int i = 0; i < sample_count; i++)
			{
				auto x = distribution(generator);
				auto y = distribution(generator);
                Point2D sample = rectangle.from_relative(Point2D(x,y));

				function(sample);
			}
        }
    };
}

Sampler raytracer::samplers::random(const int sample_count)
{
    return Sampler(std::make_shared<RandomSampler>(sample_count));
}