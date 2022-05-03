#include "hflog.h"
#include "loguru.hpp"
#include <stdio.h>


// loguru::Verbosity GetVerb(int verbosity)
// {
//     if (verbosity == 1)
//     {
//         return 1;
//     }
// }


void HFLog::Init(int argc, char* argv[])
{
    if (initialized)
    {
        printf("Tried to initialize the logger, but it is already initialized!");
        return;
    }

    loguru::init(argc, argv);

    loguru::add_file("logs/master.log", loguru::Append, loguru::Verbosity_MAX);
    loguru::add_file("logs/latest_readable.log", loguru::Truncate, loguru::Verbosity_INFO);
    loguru::add_file("logs/file_log.log", loguru::Truncate, loguru::Verbosity_8);

    loguru::g_stderr_verbosity = 1;

    initialized = false;
}


void HFLog::Log(int verbosity, std::string message, const char* file, unsigned int line)
{
    loguru::Verbosity logVerb = verbosity;
    // VLOG_F(logVerb, message.c_str());
    loguru::log(logVerb, file, line, message.c_str());
}

void HFLog::LogIf(bool condition, int verbosity, std::string message, const char* file, unsigned int line)
{
    loguru::Verbosity logVerb = verbosity;
    // VLOG_IF_F(logVerb, condition, message.c_str());
    if (condition)
    {
        loguru::log(logVerb, file, line, message.c_str());
    }
}

void HFLog::DLog(int verbosity, std::string message, const char* file, unsigned int line)
{
    // DVLOG_F(logVerb, message.c_str());
    #if LOGURU_DEBUG_LOGGING
        loguru::Verbosity logVerb = verbosity;
        loguru::log(logVerb, file, line, message.c_str());
    #endif
}

void HFLog::DLogIf(bool condition, int verbosity, std::string message, const char* file, unsigned int line)
{
    // DVLOG_IF_F(logVerb, condition, message.c_str());
    #if LOGURU_DEBUG_LOGGING
        loguru::Verbosity logVerb = verbosity;
        if (condition)
        {
            loguru::log(logVerb, file, line, message.c_str());
        }
    #endif
}