#include "vpch.h"
#include "JobScheduler.h"

#include "SDL2/SDL.h"
#include "Core/Time.h"

namespace Vortex
{
	static std::mutex mtx;

	void JobScheduler::Init()
	{
		std::thread* th0 = new std::thread(JobScheduler::ThreadJob, JobPriority::Low, false);
		std::thread* th1 = new std::thread(JobScheduler::ThreadJob, JobPriority::Low, true);
		std::thread* th2 = new std::thread(JobScheduler::ThreadJob, JobPriority::Normal, false);
		std::thread* th3 = new std::thread(JobScheduler::ThreadJob, JobPriority::Normal, true);
		std::thread* th4 = new std::thread(JobScheduler::ThreadJob, JobPriority::High, false);
		std::thread* th5 = new std::thread(JobScheduler::ThreadJob, JobPriority::High, true);

		m_ThreadPool.push_back(th0);
		m_ThreadPool.push_back(th1);
		m_ThreadPool.push_back(th2);
		m_ThreadPool.push_back(th3);
		m_ThreadPool.push_back(th4);
		m_ThreadPool.push_back(th5);
	}

	void JobScheduler::Destroy()
	{
		m_RunThreads = false;

		bool res = false;
		do
		{
			if (mtx.try_lock())
			{
				mtx.unlock();
				res = true;
			}
		} while (!res);
	}

	int JobScheduler::ThreadJob(JobPriority priority, bool frontJobs)
	{
		bool runThread = true;

		while(runThread)
		{
			if (mtx.try_lock())
			{
				JobEntry jobEntry = JobScheduler::GetNextJob(priority, frontJobs);
				runThread = JobScheduler::m_RunThreads;
				mtx.unlock();
				
				if (!jobEntry.addr)
				{
					std::this_thread::yield();
					continue;
				}

				JobData<unsigned> job = JobData<unsigned>();
				job.SetJobEntry(jobEntry);
 				while (job)
				{
					job();
				}
				job.Destroy();
			}
		}

		return 0;
	}
}
