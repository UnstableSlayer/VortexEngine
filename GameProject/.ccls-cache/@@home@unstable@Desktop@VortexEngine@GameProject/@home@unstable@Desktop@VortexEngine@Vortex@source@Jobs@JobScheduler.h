#pragma once
#include "Jobs/JobData.h"
#include <queue>

namespace Vortex
{
	enum class JobPriority
	{
		Low, Normal, High
	};

	class JobScheduler
	{
	public:
		static void Init();
		static void Destroy();

		static int ThreadJob(JobPriority priority, bool frontJobs);

	public:
		template<typename T>
		static void PushJob(JobData<T> job, JobPriority priority = JobPriority::Normal)
		{
			JobEntry entry = job.GetJobEntry();

			switch (priority)
			{
			case JobPriority::Low:
				m_LowJobs.push_back(entry);
				break;
			case JobPriority::Normal:
				m_NormalJobs.push_back(entry);
				break;
			case JobPriority::High:
				m_HighJobs.push_back(entry);
				break;
			}
		}

		static JobEntry GetNextJob(JobPriority priority, bool frontJobs)
		{
			bool isNotEmpty = priority == JobPriority::Low && m_LowJobs.size() ||
							  priority == JobPriority::Normal && m_NormalJobs.size() ||
				              priority == JobPriority::High && m_HighJobs.size();
						 
			if (!isNotEmpty)
				return JobEntry(nullptr);

			JobEntry job;
			switch (priority)
			{
			case JobPriority::Low:
				job = frontJobs ? m_LowJobs.front() : m_LowJobs.back();
				frontJobs ? m_LowJobs.pop_front() : m_LowJobs.pop_back();
				break;
			case JobPriority::Normal:
				job = frontJobs ? m_NormalJobs.front() : m_NormalJobs.back();
				frontJobs ? m_NormalJobs.pop_front() : m_NormalJobs.pop_back();
				break;
			case JobPriority::High:
				job = frontJobs ? m_HighJobs.front() : m_HighJobs.back();
				frontJobs ? m_HighJobs.pop_front() : m_HighJobs.pop_back();
				break;
			}

			return job;
		}

	private:
		static inline std::deque<JobEntry> m_LowJobs;
		static inline std::deque<JobEntry> m_NormalJobs;
		static inline std::deque<JobEntry> m_HighJobs;
		static inline std::vector<std::thread*> m_ThreadPool;
		static inline bool m_RunThreads = true;
	};
}
