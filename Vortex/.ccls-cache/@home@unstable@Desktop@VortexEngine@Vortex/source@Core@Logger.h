#pragma once
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Vortex
{
	class VORTEX_API Logger
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return m_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetApplicationLogger() { return m_AppLogger; }

	private:
		static std::shared_ptr<spdlog::logger> m_CoreLogger;
		static std::shared_ptr<spdlog::logger> m_AppLogger;
	};
}


//Core Logger Macros
#define VORTEX_CORE_CRITICAL(...) ::Vortex::Logger::GetCoreLogger()->critical(__VA_ARGS__)
#define VORTEX_CORE_ERROR(...) ::Vortex::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define VORTEX_CORE_WARNING(...) ::Vortex::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define VORTEX_CORE_INFO(...) ::Vortex::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define VORTEX_CORE_TRACE(...) ::Vortex::Logger::GetCoreLogger()->trace(__VA_ARGS__)

//App Logger Macros
#define VORTEX_APP_CRITICAL(...) ::Vortex::Logger::GetApplicationLogger()->critical(__VA_ARGS__)
#define VORTEX_APP_ERROR(...) ::Vortex::Logger::GetApplicationLogger()->error(__VA_ARGS__)
#define VORTEX_APP_WARNING(...) ::Vortex::Logger::GetApplicationLogger()->warn(__VA_ARGS__)
#define VORTEX_APP_INFO(...) ::Vortex::Logger::GetApplicationLogger()->info(__VA_ARGS__)
#define VORTEX_APP_TRACE(...) ::Vortex::Logger::GetApplicationLogger()->trace(__VA_ARGS__)