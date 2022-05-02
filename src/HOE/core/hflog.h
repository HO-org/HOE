#pragma once
#include "loguru.hpp"
#include <string>

class HFLog
{
public:
    enum Vebosities
    {
        HF_INFO = 0,
        HF_WARNING = 5,
        HF_ERROR = 9
    };

public:
    static HFLog& GetInstance() {
        static HFLog instance;

        return instance;
    }

    void Init(int argc, char* argv[]);

    void Log(int verbosity, std::string message);

    void LogIf(bool condition, int verbosity, std::string message);

    void DLog(int verbosity, std::string message);

    void DLogIf(bool condition, int verbosity, std::string message);

private:
    HFLog() {} ;

    bool initialized = false;

public:
    HFLog(HFLog const&) = delete;
    void operator=(HFLog const&) = delete;
};