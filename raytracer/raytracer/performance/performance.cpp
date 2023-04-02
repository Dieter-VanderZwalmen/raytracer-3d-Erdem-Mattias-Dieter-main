#include "performance/performance.h"
#include <atomic>
#include <vector>
#include "easylogging++.h"

using namespace performance;


namespace performance
{
    namespace _private_
    {
        class CounterImplementation
        {
        public:
            CounterImplementation(const std::string& name)
                : m_name(name), m_value(0)
            {
                // NOP
            }

            void increment()
            {
                ++m_value;
            }

            std::string name() const
            {
                return m_name;
            }

            uint64_t value() const
            {
                return m_value;
            }

        private:
            std::string m_name;
            std::atomic<uint64_t> m_value;
        };
    }
}

namespace
{
    std::vector<performance::_private_::CounterImplementation*> counters;
}

Counter& performance::Counter::operator++()
{
    m_impl->increment();

    return *this;
}

Counter performance::create_counter(const std::string& name)
{
    performance::_private_::CounterImplementation* p = new performance::_private_::CounterImplementation(name);

    counters.push_back(p);

    return Counter(p);
}

void performance::print_statistics()
{
    if (counters.empty())
    {
        LOG(INFO) << "Performance statistics: no counters";
    }
    else
    {
        LOG(INFO) << "Performance statistics";

        for (auto p : counters)
        {
            LOG(INFO) << p->name() << " " << p->value();
        }
    }
}

void performance::cleanup()
{
    for (auto p : counters)
    {
        delete p;
    }

    counters.clear();
}