#pragma once
#include <iostream>

class HFLog
{
    public:
        static void Log(const char* message)
        {
            std::cout << message << std::endl;
        }
};