#pragma once
#include <chrono>

namespace Vortex
{
	class Time
	{
	public:
		Time() {}
		void Init(float delta)
		{
			UnscaledDeltaTime = delta;
		}

		const float GetDeltaTime() { return UnscaledDeltaTime * TimeScale; }
		const float GetUnscaledDeltaTime() { return UnscaledDeltaTime; }

	public:
		float TimeScale = 1.0f;

	private:
		float UnscaledDeltaTime = 0.f;
	};


	template<typename Fn>
	class Timer
	{
	public:
		Timer(const char* name, Fn&& func = [&]() {})
			: m_Name(name), m_Running(true), m_Func(func)
		{
			m_StartPoint = std::chrono::high_resolution_clock::now();
		}

		~Timer()
		{
			if (m_Running) Stop();
		}

		void Stop()
		{
			auto endPoint = std::chrono::high_resolution_clock::now();

			auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartPoint).time_since_epoch().count();
			auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endPoint).time_since_epoch().count();

			m_Running = false;
			float elapsed = (end - start);

			m_Func({ m_Name, elapsed });
		}

	private:
		const char* m_Name;
		std::chrono::time_point<std::chrono::steady_clock> m_StartPoint;
		bool m_Running;
		Fn m_Func;
	};

	struct ProfileResult
	{
		const char* Name;
		float Time;
	};
}

#define PROFILE_SCOPE(name, profileResults) Vortex::Timer timer##__LINE__(name, [&](Vortex::ProfileResult profileResult) {profileResults.push_back(profileResult);})
//#define TIMER_SCOPE(name, x) Vortex::Timer timer##__LINE__(name, [&](const char* name, float time) {std::function<void>(x);})