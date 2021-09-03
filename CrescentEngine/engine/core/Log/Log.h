//
// Created by manan on 24/07/2021.
//

#ifndef CRESCENTENGINE_LOGGER_H
#define CRESCENTENGINE_LOGGER_H

#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

class Log
{
public:
    Log();
    ~Log();
public:
    static void Init();

    inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
    inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
private:
    static std::shared_ptr<spdlog::logger> s_CoreLogger;
    static std::shared_ptr<spdlog::logger> s_ClientLogger;
};


// Core Log Macros
#define CRESCENT_CORE_ERROR(...)	::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CRESCENT_CORE_WARN(...)	::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CRESCENT_CORE_INFO(...)	::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CRESCENT_CORE_TRACE(...)	::Log::GetCoreLogger()->trace(__VA_ARGS__)

// Client Log Macros
#define CRESCENT_ERROR(...)	::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CRESCENT_WARN(...)	::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CRESCENT_INFO(...)	::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CRESCENT_TRACE(...)	::Log::GetCoreLogger()->trace(__VA_ARGS__)

#endif //CRESCENTENGINE_LOGGER_H
