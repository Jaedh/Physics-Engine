#ifndef CORE_UTIL_LOGGER_H
#define CORE_UTIL_LOGGER_H

#include <spdlog/spdlog.h>
#include <spdlog/async.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <memory>
#include <mutex>

namespace core::util {

class Logger {
    private:
        static inline std::once_flag s_initFlag;
    public:
        static void init() {
            std::call_once(s_initFlag, []() {
                // 1. Initialize thread pool (8k queue size, 1 worker thread)
                spdlog::init_thread_pool(8192, 1);

                // 2. Create single-threaded sinks (async worker thread manages writes)
                auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_st>();
                console_sink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] [%s:%#] %v");

                auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_st>("physics-lab.log", true);
                file_sink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] [%s:%#] %v");

                // 3. Construct async logger using thread pool
                auto logger = std::make_shared<spdlog::async_logger>(
                    "physics-lab",
                    spdlog::sinks_init_list{console_sink, file_sink},
                    spdlog::thread_pool(),
                    spdlog::async_overflow_policy::block
                );
                
                #ifndef NDEBUG
                            logger->set_level(spdlog::level::trace);
                            logger->flush_on(spdlog::level::trace);
                #else
                            logger->set_level(spdlog::level::info);
                            logger->flush_on(spdlog::level::warn);
                #endif

                // Register as the single source of truth default logger
                spdlog::set_default_logger(logger);
            });
        }

        static void shutdown() {spdlog::shutdown();}
};

} 

#define LOG_INTERNAL(level, ...) \
    spdlog::default_logger_raw()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, level, __VA_ARGS__)

#ifndef NDEBUG
    #define LOG_TRACE(...) LOG_INTERNAL(spdlog::level::trace, __VA_ARGS__)
    #define LOG_DEBUG(...) LOG_INTERNAL(spdlog::level::debug, __VA_ARGS__)
#else
    #define LOG_TRACE(...) ((void)0)
    #define LOG_DEBUG(...) ((void)0)
#endif

#define LOG_INFO(...)     LOG_INTERNAL(spdlog::level::info, __VA_ARGS__)
#define LOG_WARN(...)     LOG_INTERNAL(spdlog::level::warn, __VA_ARGS__)
#define LOG_ERROR(...)    LOG_INTERNAL(spdlog::level::err, __VA_ARGS__)
#define LOG_CRITICAL(...) LOG_INTERNAL(spdlog::level::critical, __VA_ARGS__)

#endif 