#pragma once
#include <string>


class HFLog
{
public:
    enum Vebosities
    {
        HF_INFO = 0,
        HF_FILE_ONLY = 8,
        HF_WARNING = -1,
        HF_ERROR = -2
    };

public:
    static HFLog& GetInstance() {
        static HFLog instance;

        return instance;
    }

    void Init(int argc, char* argv[]);

    void Log(int verbosity, std::string message, const char* file, unsigned int line);

    void LogIf(bool condition, int verbosity, std::string message, const char* file, unsigned int line);

    void DLog(int verbosity, std::string message, const char* file, unsigned int line);

    void DLogIf(bool condition, int verbosity, std::string message, const char* file, unsigned int line);

private:
    HFLog() {} ;

    bool initialized = false;

public:
    HFLog(HFLog const&) = delete;
    void operator=(HFLog const&) = delete;
};