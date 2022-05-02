#include "hflog.h"
#include "loguru.hpp"
#include <stdio.h>

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

    loguru::g_stderr_verbosity = 1;

    initialized = false;
}


void HFLog::Log(int verbosity, std::string message)
{
    if (verbosity == 0)
    {
        LOG_F(INFO, message.c_str());
    }
    else if (verbosity == 5)
    {
        LOG_F(WARNING, message.c_str());
    }
    else if (verbosity == 9)
    {
        LOG_F(ERROR, message.c_str());
    }
}


void HFLog::LogIf(bool condition, int verbosity, std::string message)
{
    if (verbosity == 0)
    {
        LOG_IF_F(INFO, condition, message.c_str());
    }
    else if (verbosity == 5)
    {
        LOG_IF_F(WARNING, condition, message.c_str());
    }
    else if (verbosity == 9)
    {
        LOG_IF_F(ERROR, condition, message.c_str());
    }
}


void HFLog::DLog(int verbosity, std::string message)
{
    if (verbosity == 0)
    {
        DLOG_F(INFO, message.c_str());
    }
    else if (verbosity == 5)
    {
        DLOG_F(WARNING, message.c_str());
    }
    else if (verbosity == 9)
    {
        DLOG_F(ERROR, message.c_str());
    }
}


void HFLog::DLogIf(bool condition, int verbosity, std::string message)
{
    if (verbosity == 0)
    {
        DLOG_IF_F(INFO, condition, message.c_str());
    }
    else if (verbosity == 5)
    {
        DLOG_IF_F(WARNING, condition, message.c_str());
    }
    else if (verbosity == 9)
    {
        DLOG_IF_F(ERROR, condition, message.c_str());
    }
}