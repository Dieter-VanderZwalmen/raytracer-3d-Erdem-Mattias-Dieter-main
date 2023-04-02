#include "tasks/naive-parallel-task-scheduler.h"
#include <thread>

using namespace tasks;


namespace
{
    class NaiveParallelTaskScheduler : public tasks::schedulers::_private_::TaskSchedulerImplementation
    {
    public:
        void perform(std::vector<std::shared_ptr<Task>> tasks) const
        {
			std::vector<std::thread> threads;
			
			for (auto task : tasks)
			{
				threads.push_back(std::move(std::thread([task]() { task->perform(); })));
			}

			for (auto& thread : threads)
			{
				thread.join();
			}
        }
    };
}

TaskScheduler tasks::schedulers::naive_parallel()
{
    return TaskScheduler(std::make_shared<NaiveParallelTaskScheduler>());
}
