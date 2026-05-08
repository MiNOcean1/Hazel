#include "hzpch.h"
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"
namespace Hazel {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init() {

		spdlog::set_pattern("%^[%T] %n: %v%$");//设置输出格式模板。
		s_CoreLogger = spdlog::stdout_color_mt("Hazel");//创建一个名叫 "Hazel" 的多线程彩色控制台 logger。
		s_CoreLogger->set_level(spdlog::level::trace);//把最详细级别打开（trace/debug/info/warn/error/critical… 都能打）。

		s_ClientLogger = spdlog::stdout_color_mt("App");

		s_ClientLogger->set_level(spdlog::level::trace);

	}


}